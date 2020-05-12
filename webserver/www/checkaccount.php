<?php
header("content-type:text/html;charset=utf-8");
header('Access-Control-Allow-Origin: *'); 
header('Access-Control-Allow-Headers: *');
include("mysql_inc_test.php");
$YourName=$_POST['YourName'];
$lastherf=$_SERVER['HTTP_REFERER'];
$data["lastherf"] = $lastherf;
if(isset($YourName)&&preg_match("/signup.html/",$lastherf)){	
    $sql = "select *  from user where studentid=?";		
    $result = $con->prepare($sql);
	$result->bindParam(1, $YourName);
	$result->execute();	
    $row_count = $result->rowCount(); 
    if($row_count<=0){
        $data["api_named"] = "show  usr";
        $data["resultd"] = "0";
        $data["messaged"] = "no data";
    }
    else{
        while($row = $result->fetch(PDO::FETCH_ASSOC)) {
			$data["api_named"] = "show  usr";
			$data["resultd"] = "1";
            $data["name"]= $row['name'] ;
			$data["password"]= $row['password'] ;	
        }  
    }
	
}    
echo json_encode($data);
?>