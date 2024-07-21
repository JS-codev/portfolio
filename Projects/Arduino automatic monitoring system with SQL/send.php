<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>Untitled Document</title>
</head>
<?php
	//establish connection to database
	$dbuser = "root";  // enter your username for mysql
	$dbpass = "";  // enter your password for mysql
	$dbhost = "localhost";      // this is usually "localhost" unless your database resides on a different server
	$dbname = "projectinfo";			//database name
	$conn = mysqli_connect($dbhost, $dbuser, $dbpass) or die ('Error connecting to mysql @'.$dbhost);
	mysqli_select_db($conn,$dbname);
	//$dbh = mysql_pconnect($MyHostname , $MyUsername, $MyPassword);
	$selected = mysqli_select_db($conn,$dbname);


    // Prepare the SQL statement, please change to your database
	$SQL = "INSERT INTO `machine`(`percent`, `temp`, `Time_time`, `ultrasonicsensor`) VALUES ('".$_GET['percent']."','".$_GET['temp']."',now(),'".$_GET['ultrasonicsensor']."')";
echo $SQL;   
   if(mysqli_query($conn,$SQL))
	{
			echo " Successful";
	}

?>
<body>
</body>
</html>
