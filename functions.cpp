#include "functions.h"
#include "mytcpserver.h"


QMap<std::string, std::vector<int>> rooms;
QByteArray parser(QByteArray req) {
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
    return command_recognizer(command, login, room_name);
}

QByteArray command_recognizer(std::string command, std::string login, std::string room_name) {
    if (command == "start") {
        // todo: check user not in query
        if (rooms.contains(room_name)) {
            // do req to db
            rooms[room_name].push_back(rooms[room_name].size() + 1);
            return QByteArray::fromStdString("Вы успешно подключились к комнате");
        }
        if (rooms[room_name].size() == 7) {
            return QByteArray::fromStdString("disconnect");
        }
    }
    else
        if (command == "break") {
        return QByteArray::fromStdString("break");
    }
    else if (command == "stats") {
        return QByteArray::fromStdString("stats");
    }
    else if (command == "rooms") {
        for (const auto& room : rooms) {
            qDebug() << room;
        }
        return QByteArray::fromStdString(rooms.firstKey());
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
