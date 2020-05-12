<?php
header("content-type:text/html;charset=utf-8");
header('Access-Control-Allow-Origin: *'); 
header('Access-Control-Allow-Headers: *');
include("mysql_inc_test.php");
$account=$_POST['account'];
$pwd=$_POST['pwd'];
/*$account=$_GET['account'];
$pwd=$_GET['pwd'];
$oldpwd=$_GET['oldpwd'];*/
$lastherf=$_SERVER['HTTP_REFERER'];
$data["lastherf"] = $lastherf;
if(isset($account)&&isset($pwd)&&preg_match("/restart.html/",$lastherf)){	
	$sql="select * from user where password=? and studentid=?";
	$result = $con->prepare($sql);
	$result->bindParam(1, $pwd);	
	$result->bindParam(2, $account);
	$result->execute();	
    $row_count = $result->rowCount(); 
    if($row_count<=0){
        $data["api_named"] = "restart  user ip";
        $data["resultd"] = "-1";
        $data["messaged"] = "pwdwrong";
    }
    else{
        while($row = $result->fetch(PDO::FETCH_ASSOC)) {
			$data["api_named"] = "restart  user ip";
			$data["resultd"] = "1";
            exec("/usr/local/bin/python  socket_client.py 03 $account ");//等同於命令`python python.py 引數`，並接收列印出來的資訊 
			$sqldel = "DELETE FROM `userip` WHERE  studentid='$account'";		
			$resultdel = $con->query($sqldel);
			
			
        }  
    }
    
	
} 
echo json_encode($data);   
?>