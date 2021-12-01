<!DOCTYPE php>
<?php
session_start();
$_SESSION['wrongData1'] = false;
$_SESSION['wrongData2'] = false;
 
$servername = "localhost";
$username = "ivo";
$password = "ebbers123";
$dbname = "website";
 
// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
if(trim($_REQUEST['username']) == '' || trim($_REQUEST['password']) == ''){
    $conn->close();
    $_SESSION['wrongData1'] = true;
    header('Location: login.php');
}
$DBusername = $_REQUEST['username'];
$sql = "SELECT * FROM Users WHERE username='$DBusername'";
$result = $conn->query($sql);
    // output data of each row
    while($row = $result->fetch_assoc()) {
        
        if (!password_verify($_REQUEST['password'], $row['password'])){
            $_SESSION['wrongData2'] = true;
            $conn->close();
            header('Location: login.php');
        }
        else{
            $_SESSION['username'] = $_REQUEST['username'];
            $_SESSION['password'] = $_REQUEST['password'];
            $_SESSION['userID'] = $row['userID'];
            $_SESSION['wrongData1'] = false;
            $_SESSION['wrongData2'] = false;
            $conn->close();
            header('Location: index.php');  
        }
    }
?>
