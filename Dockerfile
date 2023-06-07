FROM ubuntu

LABEL author="f1xgun"

ENV TZ=Europe/Moscow
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt-get update
RUN apt-get install qt5-default qtbase5-dev qt5-qmake -y
RUN apt-get install build-essential -y

WORKDIR /Mikhaylov_221-3210
COPY *.cpp /Mikhaylov_221-3210
COPY *.h /Mikhaylov_221-3210
COPY *.pro /Mikhaylov_221-3210

RUN qmake echoServer.pro
RUN make hallServer

ENTRYPOINT ["./hallServer"]