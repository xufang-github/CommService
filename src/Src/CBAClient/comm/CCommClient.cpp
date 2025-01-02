// utf8文件
#include "CCommClient.h"
#include <QDataStream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonValue>

CCommClient* CCommClient::s_instance = new CCommClient();

void CCommClient::connectToServer(const QString& ip, quint16 port) 
{
    if (m_socket) 
    {
        disconnect(m_reconnectTimer, &QTimer::timeout, this, &CCommClient::attemptReconnect);
        disconnect(m_socket, &QTcpSocket::readyRead, this, &CCommClient::onReadyRead);
        disconnect(m_socket, &QTcpSocket::disconnected, this, &CCommClient::onDisconnected);
        disconnect(m_socket, &QTcpSocket::connected, this, &CCommClient::onConnected);
        disconnect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), 
            this, SLOT(onNetError(QAbstractSocket::SocketError)));
        m_reconnectTimer->stop();
        m_state = EConnState_DisConnected;
        m_socket->disconnectFromHost();
        delete m_socket;
        
    }
    m_socket = new QTcpSocket();
    m_state = EConnState_Connecting;
    connect(m_reconnectTimer, &QTimer::timeout, this, &CCommClient::attemptReconnect);
    connect(m_socket, &QTcpSocket::readyRead, this, &CCommClient::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected, this, &CCommClient::onDisconnected);
    connect(m_socket, &QTcpSocket::connected, this, &CCommClient::onConnected);
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
        this, SLOT(onNetError(QAbstractSocket::SocketError)));
    m_reconnectTimer->setInterval(1000);
    m_reconnectTimer->start();
    m_socket->connectToHost(ip, port);
    m_ip = ip;
    m_port = port;
}

CCommClient* CCommClient::instance() 
{
    return s_instance;
}

CCommClient::CCommClient(QObject *parent)
    : QObject(parent),
    m_reconnectTimer(new QTimer(this)), 
    m_user(),
    m_state(EConnState_DisConnected),
    m_buffer(),
    m_socket(nullptr),
    m_ip(""),
    m_port(0)
{

}

CCommClient::~CCommClient()
{
    if (m_socket) {
        m_socket->disconnectFromHost();
        m_socket->deleteLater();
    }
    m_reconnectTimer->stop();
    delete m_reconnectTimer;
}

void CCommClient::write(const QByteArray& buf)
{
    if (m_socket && EConnState_Connected == m_state) {
        quint32 messageSize = buf.size();
        m_socket->write(reinterpret_cast<const char*>(&messageSize), sizeof(quint32));
        m_socket->write(buf);
    }
}

void CCommClient::login(const SUser& user) 
{
    m_user = user;
    QJsonObject obj;
    obj["type"] = "login";
	obj["userName"] = user.userName;
	obj["password"] = user.password;
	QJsonDocument doc(obj);
	QByteArray buf = doc.toJson();
	write(buf);
    // 订阅消息
    for (const QString& topic : m_subscriptions) {
        subscribe(topic);
    }
}

QTcpSocket* CCommClient::socket() const
{
    return m_socket;
}

void CCommClient::onReadyRead()
{
    while (m_socket->bytesAvailable() > 0) {
        m_buffer.append(m_socket->readAll());
        char* data = m_buffer.data();
        int offset = 0;
        while (offset < m_buffer.size()) {
            if (m_buffer.size() - offset < sizeof(quint32)) {
                break;
            }
            quint32 messageSize = *reinterpret_cast<quint32*>(data + offset);
            if (m_buffer.size() - offset < messageSize + sizeof(quint32)) {
                break;
            }
            offset += sizeof(quint32);
            QByteArray message(data + offset, messageSize);
            offset += messageSize;
            QJsonDocument doc = QJsonDocument::fromJson(message);
            if (!doc.isObject()) {
				qDebug() << "Invalid message format";
				continue;
			}
            QJsonObject obj = doc.object();
			QString type = obj["type"].toString();
            if (type == "login") {
                bool success = obj["message"].toBool();
                emit sigLogin(success);
            }
            else if (type == "message") {
                QString topic = obj["topic"].toString();
                QString message = obj["message"].toString();
                emit sigMessageReceived(topic, message);
            }
        }
        if (offset > 0) {
			m_buffer = m_buffer.mid(offset);
		}
    }
}

void CCommClient::onDisconnected()
{
    m_state = CCommClient::EConnState_DisConnected;
    emit disconnected();
    m_socket->deleteLater();
    m_socket = nullptr;
    m_reconnectTimer->start();
}

void CCommClient::attemptReconnect()
{
    if (m_state == EConnState_DisConnected) 
    {
        connectToServer(m_ip+"", m_port + 0);
    }
}

void CCommClient::sendMessage(const QString& topic, const QString& message) 
{
    QJsonObject obj;
    obj["userName"] = m_user.userName;
	obj["type"] = "message";
	obj["topic"] = topic;
	obj["message"] = message;
	QJsonDocument doc(obj);
	QByteArray buf = doc.toJson();
	write(buf);
}
// 订阅
void CCommClient::subscribe(const QString& topic) 
{
    m_subscriptions.insert(topic);
    QJsonObject obj;
    obj["userName"] = m_user.userName;
	obj["type"] = "subscribe";
	obj["topic"] = topic;
	QJsonDocument doc(obj);
	QByteArray buf = doc.toJson();
	write(buf);
}


void CCommClient::onConnected() 
{
    m_buffer.clear();
    m_state = CCommClient::EConnState_Connected;
    m_reconnectTimer->stop();
    if (m_user.userName.isEmpty() || m_user.password.isEmpty())
        return;
    // 登录优先
    login(m_user);
    // 订阅消息
    for (const QString& topic : m_subscriptions) {
		subscribe(topic);
	}
}

void CCommClient::onNetError(QAbstractSocket::SocketError socketError) 
{
	m_state = CCommClient::EConnState_DisConnected;
}
