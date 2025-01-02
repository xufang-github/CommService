// utf8文件
#include "CCommService.h"
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <CBADataService/user/IUserService.h>

using namespace CBADataService;

CCommService::CCommService(QObject *parent)
    : QTcpServer(parent)
{
}

CCommService::~CCommService()
{
    for (CTcpClientHandler* client : m_authenticatedClients) {
        client->socket()->disconnectFromHost();
        client->deleteLater();
    }
}

void CCommService::incomingConnection(qintptr socketDescriptor)
{
    CTcpClientHandler* clientHandler = new CTcpClientHandler(socketDescriptor, this);
    connect(clientHandler, &CTcpClientHandler::messageReceived, this, &CCommService::onMessageReceived);
    connect(clientHandler, &CTcpClientHandler::disconnected, this, &CCommService::onClientDisconnected);
    qDebug() << "New client connected:" << clientHandler->socket()->peerAddress().toString();
}

void CCommService::onMessageReceived(CTcpClientHandler* client, const QByteArray& message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message);
    if (!doc.isObject()) {
        qDebug() << "Invalid message format";
        return;
    }

    QJsonObject obj = doc.object();
    QString type = obj["type"].toString();
    if (type == "login") {
        QString msg = obj["message"].toString();
        if (authenticate(client, obj)) {
            m_authenticatedClients.insert(client);
            // 返回登录成功消息
            QJsonObject obj;
            obj["type"] = "login";
            obj["message"] = true;
            client->write(QJsonDocument(obj).toJson());
        }
        else {
            // 返回登录失败消息
            QJsonObject obj;
            obj["type"] = "login";
            obj["message"] = false;
            client->write(QJsonDocument(obj).toJson());
        }
        return;
    }

    if (!m_authenticatedClients.contains(client)) 
    {
		return;
    }
   if (type == "subscribe") {
        QString topic = obj["topic"].toString();
        handleSubscription(client, topic);
    } else if (type == "message") {
        handleMessage(client, obj);
    }
}

void CCommService::onClientDisconnected(CTcpClientHandler* client)
{
    m_authenticatedClients.remove(client);
    for (auto it = m_subscriptions.begin(); it != m_subscriptions.end(); ) {
        if (it.value() == client) {
            it = m_subscriptions.erase(it);
        } else {
            ++it;
        }
    }
    client->deleteLater();
    qDebug() << "Client disconnected:" << client->socket()->peerAddress().toString();
}

bool CCommService::authenticate(CTcpClientHandler* client, const QJsonObject& obj)
{
    // 简单的认证逻辑，可以根据需要进行扩展
    SUser user;
    user.userName = obj["userName"].toString();
    user.password = obj["password"].toString();
    return IUserService::getIntance()->login(user);
}

void CCommService::handleSubscription(CTcpClientHandler* client, const QString& topic)
{
    m_subscriptions.insert(topic, client);
    qDebug() << "Client subscribed to topic:" << topic;
}

void CCommService::handleMessage(CTcpClientHandler* client,const QJsonObject& obj)
{
    QString topic = obj["topic"].toString();
    auto range = m_subscriptions.equal_range(topic);
    QJsonDocument doc(obj);
    QByteArray buf = doc.toJson();
    for (auto it = range.first; it != range.second; ++it) {
        if (it.value() != client) {
            it.value()->write(buf);
        }
    }
}
