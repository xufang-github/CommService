// utf8文件
#include "CTcpClientHandler.h"
#include <QDataStream>

using namespace CBADataService;

CTcpClientHandler::CTcpClientHandler(qintptr socketDescriptor, QObject *parent)
    : QObject(parent), m_socket(new QTcpSocket(this))
{
    if (m_socket->setSocketDescriptor(socketDescriptor)) {
        connect(m_socket, &QTcpSocket::readyRead, this, &CTcpClientHandler::onReadyRead);
        connect(m_socket, &QTcpSocket::disconnected, this, &CTcpClientHandler::onDisconnected);
    } else {
        delete m_socket;
        m_socket = nullptr;
    }
}

CTcpClientHandler::~CTcpClientHandler()
{
    if (m_socket) {
        m_socket->disconnectFromHost();
        m_socket->deleteLater();
        m_socket->flush();
    }
}

void CTcpClientHandler::write(const QByteArray& buf)
{
	if (m_socket) {
        quint32 messageSize = buf.size();
        m_socket->write(reinterpret_cast<const char*>(&messageSize), sizeof(quint32));
        m_socket->write(buf);
	}

}

QTcpSocket* CTcpClientHandler::socket() const
{
    return m_socket;
}

void CTcpClientHandler::onReadyRead()
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
			emit messageReceived(this, message);
		}
        if (offset > 0) {
            m_buffer = m_buffer.mid(offset);
        }
    }
}

void CTcpClientHandler::onDisconnected()
{
    emit disconnected(this);
    m_socket->deleteLater();
    m_socket = nullptr;
}
