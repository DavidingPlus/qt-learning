#include "server.h"

#include <QtNetwork>

#include "connection.h"

Server::Server(QObject* parent)
    : QTcpServer(parent)
{
    listen(QHostAddress::Any);
}

void Server::incomingConnection(qintptr socketDescriptor)
{
    Connection* connection = new Connection(socketDescriptor, this);
    emit newConnection(connection);
}
