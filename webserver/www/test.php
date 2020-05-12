<?php
header("content-type:text/html;charset=utf-8");
header('Access-Control-Allow-Origin: *'); 
header('Access-Control-Allow-Headers: *');
include("mysql_inc_test.php");
/*$YourName=$_POST['YourName'];
if(isset($YourName)){	
    $sql = "select *  from user where studentid=?";	
	$stmt = $con->prepare($sql);
	$stmt->bindParam(1, $YourName);
	$result=$stmt->execute();
	//echo $stmt->rowCount();
    //$result = $con->query($sql);	
    $row_count = $stmt->rowCount(); 
    if($row_count<=0){
        $data["api_named"] = "show  usr";
        $data["resultd"] = "0";
        $data["messaged"] = "no data";
    }
    else{
        while($row = $stmt->fetch(PDO::FETCH_ASSOC)) {
			$data["api_named"] = "show  usr";
			$data["resultd"] = "1";
            $data["name"]= $row['name'] ;
			$data["password"]= $row['password'] ;	
        }  
    }
	
}  */  
$hostip="140.123.97.31";
$port="32768";
$data["back"] = "OK";
if (!$x =fsockopen($hostip, $port, $errno, $errstr, 1)) //測試連線
	{
		$data["test"] = "false";
	}
else
	{
		$data["test"] = "true";
		if ($x){fclose($x); //關閉連線，好寶寶都會養成的好習慣，也不知道有沒有用
		}
	}
echo json_encode($data);
?>