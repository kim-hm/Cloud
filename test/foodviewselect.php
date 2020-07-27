<?php

$con = mysqli_connect("localhost","rkaak6445","rlaals3308!","rkaak6445");

mysqli_set_charset($con,"utf8");
$name = $_POST['name'];
$sql = "select * from food where fname like '%$name%'";
$rs=mysqli_query($con,$sql);

while($result=mysqli_fetch_assoc($rs)){
	echo '#';
	echo $result['fnum'];
	echo "/";
	echo $result['fname'];
	echo "/";
	echo $result['fprice'];
	echo "/";
	echo $result['fquantity'];
	echo "/";
	echo $result['furl'];
}

mysqli_close($con);

?>