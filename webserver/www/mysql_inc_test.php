<?php
    //資料庫設定
    $dbServer = "db";
    $dbName = "testdb";
    $dbUser = "testusr";
    $dbPass = "testusr";
	//ip
	$ip ="140.123.97.31";
    //連線資料庫伺服器
    try {
        $con=new PDO("mysql:host=".$dbServer.";dbname=".$dbName.";charset=utf8", $dbUser, $dbPass);
    }catch (PDOException $e) {
    print "Error!: " . $e->getMessage() . "<br/>";
    die();
    }

?>