<!DOCTYPE php>
<?php
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
 
$un = "[put in username here]";
$pw = password_hash("[put in password here]", PASSWORD_DEFAULT);
 
$sql = "INSERT INTO Users (username, password, userID)
VALUES ('$un', '$pw', 5)";
 
if ($conn->query($sql) === TRUE) {
    echo "New record created successfully";
} else {
    echo "Error: " . $sql . "<br>" . $conn->error;
}
 
$conn->close();
?>
