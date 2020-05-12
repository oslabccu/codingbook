<?php
$params = "abc"; 
$path="testpython.py "; //需要注意的是：末尾要加一個空格
exec("/usr/local/bin/python  testpython.py  123",$test);//等同於命令`python python.py 引數`，並接收列印出來的資訊 
//passthru("id");
echo $test[0];
?>