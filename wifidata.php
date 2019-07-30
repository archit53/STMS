<?php ?><br data-mce-bogus="1">
 <?php
$hostname = "localhost";
$username = "root";
$password = "";
$db="demo";
 
$conn = new mysqli($hostname, $username, $password,$db);
 
if ($conn->connect_error) {
echo "Connection failed: " ;
}
 else{
     echo "connection established";
     $newf=$_GET[per];
     if($newf>=0&&$newf<=40)
     	 $newf=$newf."FILLED\nNO ACTION REQUIRED";
   
    else if($newf>40&&$newf<=70)
    $newf=$newf." GOING TO BE FILLED SOON!!!!";
    else
    $newf=$newf."FILLED\nALERT!!!!EMPTY IT NOW!!";
     $sql_insert="insert into `locations` (`lat`,`lng`,`location_status`,`description`)  values  ('$_GET[tempc]','$_GET[tempc1]','$_GET[status]','$newf')";
     
     
$qry = mysqli_query($conn ,$sql_insert);
 }
?>