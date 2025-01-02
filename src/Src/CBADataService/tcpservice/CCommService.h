// utf8文件
#ifndef CBADataService_CCOMMSERVICE_H
#define CBADataService_CCOMMSERVICE_H

#include <QTcpServer>
#include <QSet>
#include <QMultiMap>
#include <QJsonObject>
#include "CTcpClientHandler.h"
#include "CBADataService/CBADataService_global.h"

namespace CBADataService
{
class CBADataService_EXPORT CCommService : public QTcpServer
{
    Q_OBJECT
public:
    explicit CCommService(QObject *parent = nullptr);
    ~CCommService();
protected:
    void incomingConnection(qintptr socketDescriptor) override;
private slots:
    void onMessageReceived(CTcpClientHandler* client, const QByteArray& message);
    void onClientDisconnected(CTcpClientHandler* client);
private:
    bool authenticate(CTcpClientHandler* client,const QJsonObject& obj);
    void handleSubscription(CTcpClientHandler* client, const QString& topic);
    void handleMessage(CTcpClientHandler* client,const QJsonObject& obj);
    QSet<CTcpClientHandler*> m_authenticatedClients;
    QMultiMap<QString, CTcpClientHandler*> m_subscriptions; // topic -> clients
};
}

#endif // CBADataService_CCOMMSERVICE_H
