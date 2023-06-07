#include "functions.h"
#include "mytcpserver.h"


QMap<std::string, QMap<int, std::string>> rooms = {};
QByteArray parser(QByteArray req, int user_id) {
    std::string req_string = req.toStdString();
    std::string command = "";
    std::string login = "";
    std::string room_name = "";
    if (req_string.find('&') != std::string::npos) {
        if (req_string.find("login") != std::string::npos) {
            login = req_string.substr(req_string.find("login") + 6, req_string.find("roomname") - req_string.find("login") - 7);
        }
        if (req_string.find("roomname") != std::string::npos) {
            room_name = req_string.substr(req_string.find("roomname") + 9);
        }
        command = req_string.substr(0, req_string.find('&'));
    }
    else {
        command = req_string;
    }
    qDebug() << QString::fromStdString(command) << QString::fromStdString(login) << QString::fromStdString(room_name);
    return command_recognizer(command, login, room_name, user_id);
}

QByteArray command_recognizer(std::string command, std::string login, std::string room_name, int user_id) {
    if (command == "start") {
        for (const auto& room : rooms) {
            if (room.contains(user_id)) {
                return QByteArray::fromStdString("Вы уже состоите в одной из очередей!");
            }
        }
        // todo: check user not in query
        if (rooms.contains(room_name)) {
            QMap<int, std::string>& room = rooms[room_name];
            room[user_id] = login;
            if (room.size() == 7) {
                return QByteArray::fromStdString("disconnect");
            }
            return QByteArray::fromStdString("Вы успешно подключились к комнате");
        }
        return QByteArray::fromStdString("Комната с таким названием не существует!");
    }
    else if (command == "break") {
        for (auto& room : rooms) {
            if (room.contains(user_id)) {
                for (auto it = room.begin(); it != room.end();) {
                    if (it.key() == user_id) {
                        room.erase(it);
                        return QByteArray::fromStdString("Вы успешно покинули очередь!");
                    }
                }
            }
        }
        return QByteArray::fromStdString("Вы не состоите ни в одной очереди!");
    }
    else if (command == "stats") {
        for (const auto& room : rooms) {
            if (room.contains(user_id)) {
                QByteArray result;
                for (const auto& user : room) {
                    qDebug() << QString::fromStdString(user);
                }
//                qDebug() << room;
            }
        }
        return QByteArray::fromStdString("Вы не состоите ни в одной очереди!");
    }
    else if (command == "rooms") {
        for (const auto& room : rooms.keys()) {
            qDebug() << QString::fromStdString(room);
        }
        return QByteArray::fromStdString("Комнаты:");
    }
    else if (command == "newroom") {
        if (!rooms.contains(room_name)) {
            rooms[room_name] = {};
            return QByteArray::fromStdString("Комната успешно добавлена!");
        }
        return QByteArray::fromStdString("Комната с таким именем уже создана!");
    }
    else {
        return QByteArray::fromStdString("Неизвестная команда!");
    }
}
