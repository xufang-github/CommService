// utf8文件
#ifndef CBADataService_CTCPCLIENTHANDLER_H
#define CBADataService_CTCPCLIENTHANDLER_H

#include <QTcpSocket>
#include <QObject>
#include <QByteArray>

namespace CBADataService 
{

class CTcpClientHandler : public QObject
{
    Q_OBJECT

public:
    explicit CTcpClientHandler(qintptr socketDescriptor, QObject *parent = nullptr);
    ~CTcpClientHandler();

    QTcpSocket* socket() const;
    void write(const QByteArray& buf);
signals:
    void messageReceived(CTcpClientHandler* client, const QByteArray& message);
    void disconnected(CTcpClientHandler* client);

private slots:
    void onReadyRead();
    void onDisconnected();

private:
    QTcpSocket* m_socket;
    QByteArray m_buffer;
};


}

#endif // CBADataService_CTCPCLIENTHANDLER_H
