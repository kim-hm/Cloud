<?php
$id = $_POST["id"];
$arr = explode("/", $id);

$con = mysqli_connect("localhost","rkaak6445","rlaals3308!","rkaak6445");
mysqli_set_charset($con,"utf8"); 

$insertSQL = "insert into customer(cno, id, pwd, name, email, phone)
values(null, '$arr[0]', '$arr[1]', '$arr[2]', '$arr[3]', '$arr[4]')";
mysqli_query($con,$insertSQL);
mysqli_close($con);
?>

<html>
   <body>
     <meta charset="UTF-8">
      <form action = "<?php $_PHP_SELF ?>" method = "POST">
         ID: <input type = "text" name = "id" />
         Pwd: <input type = "text" name = "pwd" />
         Name: <input type = "text" name = "name" />
         Email: <input type = "text" name = "email" />
         phone: <input type = "text" name = "phone" />
         <input type = "submit" />
      </form>
   </body>
</html>