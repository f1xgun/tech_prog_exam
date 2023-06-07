Ссылка на образ на DockerHub: https://hub.docker.com/repository/docker/f1xgun/tech-prog-exam/general
Для того чтобы собрать образ необходимо прописать команду
```
docker build -t tech-prog-exam .
```
Для запуска
```
docker run -it --rm -p 33333:33333 --name tech-prog-exam tech-prog-exam
```
