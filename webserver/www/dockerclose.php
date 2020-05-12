<?php
header("content-type:text/html;charset=utf-8");
header('Access-Control-Allow-Origin: *'); 
header('Access-Control-Allow-Headers: *');
include("mysql_inc_test.php");

$account=$_POST['account'];
//$account=$_GET['account'];
if(isset($account)){	
	$sqldel = "DELETE FROM `userip` WHERE  studentid='$account'";		
	if ($con->query($sqldel) == TRUE) {
		echo "OK";
	} else {
		echo "Error" . $con->error;
	}
}  
?>