// utf8文件
#ifndef CTCPCLIENTHANDLER_H
#define CTCPCLIENTHANDLER_H

#include <QTcpSocket>
#include <QObject>
#include <QByteArray>
#include <QTimer>
#include "CBADataService/CBADataService_global.h"
#include "CBADataService/user/IUserService.h"

namespace CBADataService
{
class CBADataService_EXPORT CCommClient : public QObject
{
    Q_OBJECT
public:
    enum EConnState 
    {
        EConnState_DisConnected,
        EConnState_Connecting,
        EConnState_Connected,
    };


    CCommClient(QObject *parent = nullptr);
    ~CCommClient();
    void connectToServer(const QString& ip,quint16 port);
    QTcpSocket* socket() const;
    // 登录
    void login(const SUser& user);
    // 发送信息
    void sendMessage(const QString& topic,const QString& message);
    // 订阅
    void subscribe(const QString& topic);
public:signals:
    void disconnected();
    // 收到登录消息
    void sigLogin(bool success);
    // 收到订阅消息
    void sigMessageReceived(const QString& topic,const QString& message);
private slots:
    void onReadyRead();
    void onDisconnected();
    void attemptReconnect();
    void onConnected();
    void onNetError(QAbstractSocket::SocketError socketError);
private:
    void write(const QByteArray& buf);
private:
    QTcpSocket* m_socket;
    QByteArray m_buffer;
    QTimer* m_reconnectTimer;
    qintptr m_socketDescriptor;
    QSet<QString> m_subscriptions;
    // 是否连接
    EConnState m_state;
    SUser m_user;
};
}

#endif // CTCPCLIENTHANDLER_H
