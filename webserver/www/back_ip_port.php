<?php
header("content-type:text/html;charset=utf-8");
header('Access-Control-Allow-Origin: *'); 
header('Access-Control-Allow-Headers: *');
include("mysql_inc_test.php");
$YourName=$_POST['YourName'];
$lastherf=$_SERVER['HTTP_REFERER'];
$data["lastherf"] = $lastherf;
if(isset($YourName)){	
    $sql = "select *  from userip where studentid=?";	
	$result = $con->prepare($sql);
	$result->bindParam(1, $YourName);
	$result->execute();
    $row_count = $result->rowCount(); 
    if($row_count<=0){
        $data["api_named"] = "show  user ip";
        $data["resultd"] = "0";
        $data["messaged"] = "no data";
    }
    else{
        while($row = $result->fetch(PDO::FETCH_ASSOC)) {
			$data["api_named"] = "show user ip";
			if($row['ip']!=NULL&&$row['port']!=NULL){
				$data["resultd"] = "1";
				$data["url"]="http://".$row['ip'] .":".$row['port'] ;
			}
			else{
				$data["resultd"] = "0";
				$data["messaged"] = "no ip";
			}
        }  
    }
	
}  
echo json_encode($data);  
?>