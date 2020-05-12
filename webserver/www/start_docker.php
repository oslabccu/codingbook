<?php
header("content-type:text/html;charset=utf-8");
header('Access-Control-Allow-Origin: *'); 
header('Access-Control-Allow-Headers: *');
include("mysql_inc_test.php");
$YourName=$_POST['YourName'];
$lastherf=$_SERVER['HTTP_REFERER'];
$data["lastherf"] = $lastherf;
if(isset($YourName)){	
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
			$name= $row['name'] ;
			$pwd=  $row['password'] ;
			$checkipsql = "select *  from userip where studentid=?";
			$checkipresult = $con->prepare($checkipsql);
			$checkipresult->bindParam(1, $YourName);
			$checkipresult->execute();
			$checkiprow_count = $checkipresult->rowCount(); 
			$urltest=0;
			$urltestcount=0;
			while($urltest!=1&&$urltestcount<3){
				if($checkiprow_count<=0||$urltest==2){
					$data["checkipresultd"] = "0";
					$data["test"]="/usr/local/bin/python  socket_client.py 00  $YourName -p $pwd";
					exec("/usr/local/bin/python  socket_client.py 00  $YourName -p $pwd",$onback);//等同於命令`python python.py 引數`，並接收列印出來的資訊 
					$data["rowip"]=$onback[0];
					$ip_port=explode(":",$onback[0]);
					if($ip_port[0]!=NULL&&$ip_port[1]!=NULL){
						$data["ip"]= $ip_port[0];
						$data["port"]= $ip_port[1];
						$update_ip_sql="INSERT INTO userip (studentid, ip, port) VALUES('$YourName', '$ip_port[0]', '$ip_port[1]') ON DUPLICATE KEY UPDATE ip='$ip_port[0]',port='$ip_port[1]',time=CURRENT_TIMESTAMP";
						$con->query($update_ip_sql);
						$data["insertip"] = "1";
					}
					else{
						$data["insertip"] = "0";
					}
				}
				else{
					while($checkiprow = $checkipresult->fetch(PDO::FETCH_ASSOC)) {
						$data["checkipresultd"] = "1";
						$data["ip"]=  $checkiprow['ip'];
						$data["port"]=  $checkiprow['port'];
					}
				}
				sleep(3);
				/*if (!$x =fsockopen($data["ip"], $data["port"], $errno, $errstr, 1)){
					sleep(3);
					$data["urltest"] = "false";
					$sqldel = "DELETE FROM `userip` WHERE  studentid='$YourName'";
					exec("/usr/local/bin/python  socket_client.py 03 $YourName ");//等同於命令`python python.py 引數`，並接收列印出來的資訊 
					$resultdel = $con->query($sqldel);
					$urltest=2;
					$urltestcount=$urltestcount+1;
					sleep(6);
					
					
				}
				else{
					$data["urltest"] = "true";				
					fclose($x); //關閉連線，好寶寶都會養成的好習慣，也不知道有沒有用
					$urltest=1;
					
				}*/
				$urltest=1;
			}
			
        }  
    }
	
}  
echo json_encode($data);  
?>