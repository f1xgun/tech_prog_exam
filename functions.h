
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <QByteArray>

QByteArray parser(QByteArray req, int user_id);
QByteArray command_recognizer(std::string command, std::string login, std::string room_name, int user_id);

#endif // FUNCTIONS_H
