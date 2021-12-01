<!DOCTYPE html>
<?php
session_start();
if(!isset($_SESSION['username']) || !isset($_SESSION['password'])){
    header('Location: login.php');
}
$servername = "localhost";
$username = "ivo";
$password = "ebbers123";
$dbname = "website";
?>
<script>
<?php
//connect to the database and execute sql code
$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}
$sql = "SELECT DISTINCT deviceID FROM Data WHERE userID = '".$_SESSION['userID']."' ORDER BY DEVICEID ASC";
$result = $conn->query($sql);
 
//putting all device names into an array
$devices = array();
$deviceCount = mysqli_num_rows($result);
while($row = $result->fetch_assoc()) {
    array_push($devices, $row['deviceID']);
} 
 
//copying the device names into a javascript array
$devicesEncode = json_encode($devices);
echo "var devices = ". $devicesEncode . ";\n";
echo "var deviceCount = ". $deviceCount . ";\n";
$conn->close();
 
//connect to the database and execute sql code
$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
$sql = "SELECT * FROM Data WHERE userID = '".$_SESSION['userID']."' ORDER BY DEVICEID ASC, LASTUPDATED";
$result = $conn->query($sql);
 
//initialising some arrays to put caught values into
$datawattsout = array();
$wattsoutRow = array();
 
//catching database values, getting them in the right format and put them in the correct array
$q = -1;
$deviceName = -1;
while($row = $result->fetch_assoc()) {
    $r = 0;
    if($deviceName != $row['deviceID']){
        $q++;
        $datawattsout[$q] = array('','','','','','','','','','');
        $deviceName = $row['deviceID'];
        
    }
    $wattsoutRow[$q] = explode("-", $row['PowerOut']);
    while($r <= 9){
        array_shift($datawattsout[$q]);
        array_push($datawattsout[$q], $wattsoutRow[$q][$r]);
        $r++;
    }
} 
 
//copying the data arrays into javascript arrays
$wattsoutArray = json_encode($datawattsout);
echo "var wattsoutArray = ". $wattsoutArray . ";\n";
?>
var brokendevs = "";
for(var val = 0; val < deviceCount; val++){
    if(wattsoutArray[val][9] == '0'){
        brokendevs += "<span style='color:red;'>" + devices[val] + " is not generating any energy.</span></br>";
    }
    else{
        brokendevs += devices[val] + " is generating " + wattsoutArray[val][9] + " watt</br>";
    }
}
</script>
 
<!DOCTYPE html>
<html>
<head>
<title>Home</title>
<link rel="stylesheet" type="text/css" href="foundation.css">
<link rel="stylesheet" type="text/css" href="changes.css">
</head>
<body>
<div class="top-bar" style="padding:0%;" id="responsive-menu">
  <div class="top-bar-left">
    <ul class="dropdown menu" data-dropdown-menu>
      <li onMouseOver="this.style.backgroundColor='#33ccff'" onMouseOut="this.style.backgroundColor='#e6e6e6'"><a href="./index.php">Home</a></li>
      <li onMouseOver="this.style.backgroundColor='#33ccff'" onMouseOut="this.style.backgroundColor='#e6e6e6'"><a href="./readings.php">Readings</a></li>
      <li onMouseOver="this.style.backgroundColor='#33ccff'" onMouseOut="this.style.backgroundColor='#e6e6e6'"><a href="./logout.php">log out</a></li>
    </ul>
  </div>
</div>
 
<div class="content" style="background-color: white; text-align:center;">
    <div class="grid-y" style="height: 100%;">
        <div class="cell small-7 auto" style="background-color: #e6e6e6; margin-bottom: 2%;">
            <div class="grid-x" style="height: 100%;">
                <div class="cell small-6 auto">
                    [room available for news and other info]
                </div>
                <div class="cell small-6 auto" id="devlist" style="overflow-y: auto;">
                    <script>
                        document.getElementById("devlist").innerHTML = brokendevs;
                    </script>
                </div>
            </div>
        </div>
        <div class="cell small-3 auto" style="background-color: #e6e6e6; padding-left: 2%;">
            <h3>Contact</h3>
            <p>
            If any questions should arise, feel free to contact us.<br>
            tel: 1234567890<br>
            mail: spam@email.com<br>
            PO box: some PO box.
            </p>
        </div>
    </div>
</div>
</body>
</html>
