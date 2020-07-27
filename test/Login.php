<?php
$key=$_POST['key'];
$arr = explode("/", $key);

$con = mysqli_connect("localhost","rkaak6445","rlaals3308!","rkaak6445");
mysqli_set_charset($con,"utf8");

$sql = "select id, pwd from customer where(id='$arr[0]' AND pwd='$arr[1]')";
$rs=mysqli_query($con,$sql);

while($row=mysqli_fetch_array($rs)){
    echo $row['id'];
    echo "/";
    echo $row['pwd'];
    echo "/";
}
mysqli_close($con);
?>