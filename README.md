Codingbook
===
webserver
---
>這裡使用了三個container用以建立webserver，包含了***nginx***、***phpmyadmin***、***mariadb***。
>因為需要在nginx中執行python，所以首先先要建立nginx的image
>```
>$ cd /home/yourusername/codingbook/webserver/nginxdockerfile
>$ sudo docker build -t nginx . --no-cache
>```
>建立完畢後執行shell用以創建這三個container，其中mariadb與其他兩者間有所以需要先行建立
>，nignx所開放的port為使用者連線進來的port，並且可以調整網頁放置的位置，預設為 ***/webpath/config***。
>```
>cd /home/yourusername/codingbook/webserver
>sudo shell opencontainer.sh
>```
>接著將www資料夾整個複製至 ***/webpath/config/www***中
>```
>cp /home/yourusername/codingbook/webserver/www /webpath/config/www
>```
>最後進入phpmyadmin中將sql檔匯入即可
>```
>開啟瀏覽器，輸入伺服器IP:8081則可進入phpmyadmin中，預設帳密皆為testusr，可在opencontainer.sh進行更改。
>進入後點選testdb，並匯入webserver中的testdb.sql。
>最後將帳號密碼與相關資訊匯入user資料表即可。
>```
