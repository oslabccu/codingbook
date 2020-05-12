#!/bin/bash 
docker run  --name=mariadb -d  -e PUID=1000   -e PGID=1000 -e MYSQL_ROOT_PASSWORD=oslab  -e TZ=Asia/Taipei  -e MYSQL_DATABASE=testdb  -e MYSQL_USER=testusr -e MYSQL_PASSWORD=testusr  -v /dbpath/config:/config --restart always  linuxserver/mariadb
docker run --name=my-phpmyadmin   -d --link mariadb:db -p 8081:80  --restart always phpmyadmin/phpmyadmin
docker run  --name=nginx  -d  -e PUID=1000   -e PGID=1000   -e TZ=Asia/Taipei   -p 80:80   -p 8082:443   -v /webpath/config:/config   --restart always   --link mariadb:db  nginx
