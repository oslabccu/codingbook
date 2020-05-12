#!/bin/bash


if false;then
starttime=$(date +%s)
for((i=0;i<5;i++));do
        {
            sleep 3;echo 1>>aa && endtime=$(date +%s) && echo "hi fucking $i $(expr $endtime - $starttime)"    
        }
done
wait
cat aa|wc -l
rm aa

fi

for((i=0;i<100;i++));do
    {
        #sudo docker run -d --rm --name=shell_script_test$i -e PASSWOED=qqq -P sp:0.1
        ./socket_client.py 00 shell_script_test$i -p qqq 
    }&
done

echo "OK"   

