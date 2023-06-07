
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QByteArray>

QByteArray parser(QByteArray req);
QByteArray command_recognizer(std::string command, std::string login, std::string room_name);

#endif // FUNCTIONS_H
