#!/bin/bash
#讀取txt建立user

filename='user_list2.txt'
exec < $filename
#一行一行讀入
while read line
do
	./cpe_add_users1.sh $line $line #建立掛載user,group,quota
	./browser.sh $line $line #建立ftp帳戶
    echo "$line ok!"
done

filebrowser -a 140.123.97.31 -p 7999 -r /home/ccugrp

exit 0
