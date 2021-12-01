<!DOCTYPE html>
<?php
//check if logged in and set database data
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
$row_count = mysqli_num_rows($result);
 
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
$row_count = mysqli_num_rows($result);
 
//initialising some arrays to put caught values into
$datadate = array();
$datawattsout = array();
$datawind = array();
$datawattsin = array();
$wattsinRow = array();
$windRow = array();
$wattsoutRow = array();
 
//catching database values, getting them in the right format and put them in the correct array
$q = -1;
$deviceName = -1;
while($row = $result->fetch_assoc()) {
    $r = 0;
    if($deviceName != $row['deviceID']){
        $q++;
        $datadate[$q] = array('','','','','','','','','','');
        $datawattsin[$q] = array('','','','','','','','','','');
        $datawattsout[$q] = array('','','','','','','','','','');
        $datawind[$q] = array('','','','','','','','','','');
        $deviceName = $row['deviceID'];
        
    }
    $wattsinRow[$q] = explode("-", $row['PowerIn']);
    $windRow[$q] = explode("-", $row['windspeed']);
    $wattsoutRow[$q] = explode("-", $row['PowerOut']);
    while($r <= 9){
        array_shift($datadate[$q]);
        array_push($datadate[$q], $row['LastUpdated']);
        array_shift($datawattsin[$q]);
        array_push($datawattsin[$q], $wattsinRow[$q][$r]);
        array_shift($datawind[$q]);
        array_push($datawind[$q], $windRow[$q][$r]);
        array_shift($datawattsout[$q]);
        array_push($datawattsout[$q], $wattsoutRow[$q][$r]);
        $r++;
    }
} 
 
//copying the data arrays into javascript arrays
$dateArray = json_encode($datadate);
echo "var dateArray = ". $dateArray . ";\n";
$wattsinArray = json_encode($datawattsin);
echo "var wattsinArray = ". $wattsinArray . ";\n";
$windArray = json_encode($datawind);
echo "var windArray = ". $windArray . ";\n";
$wattsoutArray = json_encode($datawattsout);
echo "var wattsoutArray = ". $wattsoutArray . ";\n";
 
//creating empty arrays for different displays
$datawattsinT = array('','','','','','','','','','');
$wattsinArrayT = json_encode($datawattsinT);
echo "var wattsinArrayT = ". $wattsinArrayT . ";\n";
echo "var wattsinArrayAll = ". $wattsinArrayT . ";\n";
$datawindT = array('','','','','','','','','','');
$windArrayT = json_encode($datawindT);
echo "var windArrayT = ". $windArrayT . ";\n";
echo "var windArrayAll = ". $windArrayT . ";\n";
$datawattsoutT = array('','','','','','','','','','');
$wattsoutArrayT = json_encode($datawattsoutT);
echo "var wattsoutArrayT = ". $wattsoutArrayT . ";\n";
echo "var wattsoutArrayAll = ". $wattsoutArrayT . ";\n";
 
//getting fields off the database and storing them in js variables
$sql2 = "SELECT DISTINCT Field FROM Data WHERE userID = '".$_SESSION['userID']."' ORDER BY Field ASC";
$result2 = $conn->query($sql2);
$fieldCount = mysqli_num_rows($result2);
$fields = array();
while($row2 = $result2->fetch_assoc()) {
    array_push($fields, $row2['Field']);
} 
$fieldsEncode = json_encode($fields);
echo "var fields = ". $fieldsEncode . ";\n";
echo "var fieldCount = ". $fieldCount . ";\n";
 
//initialising/defining some variables
$wattsinRowField = array();
$windRowField = array();
$wattsoutRowField = array();
$wattsinRowFieldT = array();
$windRowFieldT = array();
$wattsoutRowFieldT = array();
$f = 0;
while($f <= $fieldCount){
    $wattsinRowField[] = 0;
    $wattsoutRowField[] = 0;
    $windRowField[] = 0;
    $wattsinRowFieldT[] = 0;
    $wattsoutRowFieldT[] = 0;
    $windRowFieldT[] = 0;
    $f++;
}
 
//adding all values of the same fields together, putting them in different arrays
$f = 0;
while($f <= $fieldCount){
    $wattsinRowFieldT[$f] = array(0,0,0,0,0,0,0,0,0,0);
    $windRowFieldT[$f] = array(0,0,0,0,0,0,0,0,0,0);
    $wattsoutRowFieldT[$f] = array(0,0,0,0,0,0,0,0,0,0);
    
    $sql3 = "SELECT * FROM Data WHERE userID = '".$_SESSION['userID']."' AND Field = '".$f."' ORDER BY Field ASC, LASTUPDATED";
    $result3 = $conn->query($sql3);
    $c = 0;
    
    
    while($row3 = $result3->fetch_assoc()) {
        $wattsinRowField[$c] = explode("-", $row3['PowerIn']);
        $windRowField[$c] = explode("-", $row3['windspeed']);
        $wattsoutRowField[$c] = explode("-", $row3['PowerOut']);
        $c++;
    } 
    
    
    $c2 = 1;
    while($c2 <= $c){
        $r = 0;
        while($r <= 9){ 
            $windRowFieldT[$f][$r] += $windRowField[$c2-1][$r];
            $wattsinRowFieldT[$f][$r] += $wattsinRowField[$c2-1][$r];
            $wattsoutRowFieldT[$f][$r] += $wattsoutRowField[$c2-1][$r];
            $r++;
        }
        $c2++;
    }
    $f++;
}
//copying the arrays into a javascript arrays
$wattsinArrayField = json_encode($wattsinRowFieldT);
echo "var wattsinArrayField = ". $wattsinArrayField . ";\n";
$windArrayField = json_encode($windRowFieldT);
echo "var windArrayField = ". $windArrayField . ";\n";
$wattsoutArrayField = json_encode($wattsoutRowFieldT);
echo "var wattsoutArrayField = ". $wattsoutArrayField . ";\n";
 
$conn->close();
?>
 
//adding all values of different devices together into 1 value of the same kind
var i = 0;
for(i; i < 10; i++){
    wattsinArrayT[i] = 0;
    windArrayT[i] = 0;
    wattsoutArrayT[i] = 0;
    wattsinArrayAll[i] = 0;
    windArrayAll[i] = 0;
    wattsoutArrayAll[i] = 0;
}
var d = 0;
for(d; d < deviceCount; d++){
    i = 0;
    for(i; i < 10; i++){
        if(!isNaN(parseFloat(wattsinArray[d][i]))){
            wattsinArrayT[i] = parseFloat(wattsinArrayT[i]) + parseFloat(wattsinArray[d][i]);
            wattsinArrayAll[i] = parseFloat(wattsinArrayAll[i]) + parseFloat(wattsinArray[d][i]);
        }
        if(!isNaN(parseFloat(windArray[d][i]))){
            windArrayT[i] = parseFloat(windArrayT[i]) + parseFloat(windArray[d][i]);
            windArrayAll[i] = parseFloat(windArrayAll[i]) + parseFloat(windArray[d][i]);
        }
        if(!isNaN(parseFloat(wattsoutArray[d][i]))){
            wattsoutArrayT[i] = parseFloat(wattsoutArrayT[i]) + parseFloat(wattsoutArray[d][i]);
            wattsoutArrayAll[i] = parseFloat(wattsoutArrayAll[i]) + parseFloat(wattsoutArray[d][i]);
        }
    }
}
</script>
 
 
<html>
<head>
<title>Readings</title>
<link rel="stylesheet" type="text/css" href="foundation.css">
<link rel="stylesheet" type="text/css" href="changes.css">
<script src="Chart.bundle.js"></script>
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
 
<div class="content" style="background-color: white;">
    <div class="grid-y" style="height: 100%;">
        <div class="cell small-4" style="margin-bottom: 4.33333%;">
            <div class="grid-x" style="height: 100%">
                <div class="cell small-3" style="background-color: #e6e6e6; padding-left:0.5%">
                    <div style="height: auto; margin-bottom:0px;"><b>select/deselect windmills</b></div>
                    <div style="height: 90%; width: 100%; overflow-y: auto;">
                        <?php
                        //creating checkboxes equal to the amount of devices for logged in user
                            if($deviceCount == 0){
                                echo "no available windmills.";
                            }
                            
                            else{
                                $checkcount = 0;
                                echo '<ul class="no-bullet">';
                                while($checkcount < $deviceCount){
                                    echo '<li><input type="checkbox" name="checkboxname" id="Check'.$checkcount.'"  onclick="DisplayClients('.$checkcount.'); setTotalValues('.$checkcount.');" checked> '.$devices[$checkcount].'</li>';
                                    $checkcount++;
                                }
                                echo '</ul>';
                            }
                        ?>
                    </div>
                </div>
                <div class="cell small-8 small-offset-1" style="background-color: #e6e6e6; padding-left:0.5%">
                    <div style="height: 100%; width: 100%; overflow-y: auto;">
                        <div style="height: auto;">
                            <b><p id="totalvalues" style="margin-bottom:0px;"></p></b>
                        </div>
                        <div style="height: 90%;">
                            <?php
                            //displaying current values for above selected devices
                                if($deviceCount == 0){
                                    echo "no available windmills.";
                                }
                                
                                else{
                                    $textcount = 0;
                                    $wattsinRN = 0;
                                    $windRN = 0;
                                    $wattsoutRN = 0;
                                    $d = 0;
 
                                    while($textcount < $deviceCount){
                                        echo '<p id="valuesC'.$textcount.'">current values for '.$devices[$textcount].': power in = '.round($datawattsin[$textcount][9],2).'V, 
                                        power out = '.round($datawattsout[$textcount][9],2).'W, windspeed = '.round($datawind[$textcount][9],2).'</p>';
                                        $textcount++;
                                    }
                                }
                            ?>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <div class="cell auto" style="background-color: white; opacity: 0.9; padding-bottom: 3.5%;">
            <div class="grid-x">
                <button class="cell small-2" id="FCbutton" style="text-align:center; outline:none; cursor:pointer; margin-bottom:1%; padding-bottom:0.2%;" onclick="changeforecast()" onMouseOver="this.style.color='#33ccff'" onMouseOut="this.style.color='#000000'">go to forecast</button>
                <div class="cell small-6" id="legendtext" style="text-align:center;">click on one of the legend members to show/hide that member</div>
                <div class="cell small-2">
                <span id="radiobuttons">
                    <input type="radio" name="areaselect" id="devCheck" onclick="changedropdown();" checked>single&nbsp;</input>
                    <input type="radio" name="areaselect" id="fieldCheck" onclick="changedropdown();">field&nbsp;</input>
                    <input type="radio" name="areaselect" id="allCheck" onclick="changedropdown();">all&nbsp;</input>
                </span>
                </div>
                <span id="dropdownbar">
                    <select id="selectDev" class="cell small-2" onchange="changecontentDev()">
                        <?php 
                        //dropdown options equal to the amount of devices available
                            if($deviceCount > 0){
                                echo '<option disabled selected value> -- select a device -- </option>';
                                echo '<option value="0" selected="selected">'.$devices[0].'</option>';
                                $selectCount = 1;
                                while($selectCount < $deviceCount){
                                    echo '<option value="'.$selectCount.'">'.$devices[$selectCount].'</option>';
                                    $selectCount++;
                                }
                            }
 
                        ?>
                    </select>
                    <select id="selectField" class="cell small-2" style="display:none;" onchange="changecontentField()">
                        <?php 
                        //dropdown options equal to the amount of fields available
                            if($fieldCount > 0){
                                echo '<option disabled selected value> -- select a field -- </option>';
                                echo '<option value="0" selected="selected">field '.$fields[0].'</option>';
                                $selectCount = 1;
                                while($selectCount < $fieldCount){
                                    echo '<option value="'.$selectCount.'">field '.$fields[$selectCount].'</option>';
                                    $selectCount++;
                                }
                            }
 
 
                        ?>
                    </select>
                    <select id="selectAll" class="cell small-2" style="display:none;">
                    <option disabled selected value>showing total of all devices</option>
                    </select>
                </span>
            </div>
            <div style="height:100%; width:100%;" id="contentdisplay">
                <?php
                //creating canvasses equal to the amount of devices
                    echo'<canvas id="chart0"></canvas>';
                    $canvasCount = 1;
                    while($canvasCount < $deviceCount){
                        echo'<canvas id="chart'.$canvasCount.'" style="display: none"></canvas>';
                        $canvasCount++;
                    }
                ?>
                
                <?php
                //creating canvasses equal to the amount of fields
                    $canvasFCount = 0;
                    while($canvasFCount < $fieldCount){
                        echo'<canvas id="chartF'.$canvasFCount.'" style="display: none"></canvas>';
                        $canvasFCount++;
                    }
                ?>
                <canvas id="chartAll" style="display:none"></canvas>
                
                <script>
                    //setting starting point of wind map
                    var latitude = 51.991;
                    var longitude = 5.937;
                    
                    //creating the wind map
                    document.write('<iframe id="windy" style="display:none" width="100%" height="780px%" src="https://embed.windy.com/embed2.html?lat='+latitude+'&'+longitude+'&zoom=9&level=surface&overlay=wind&menu=&message=&marker=&calendar=&pressure=&type=map&location=coordinates&detail=true&detailLat='+latitude+'&detailLon='+longitude+'&metricWind=default&metricTemp=default" frameborder="0"></iframe>');
                </script>
            </div>  
        </div>
    </div>
</div>
 
<script>
//first time set for current values
document.getElementById("totalvalues").innerHTML = "current total of selected values: power in = " + wattsinArrayT[9] + "V, power out = " + wattsoutArrayT[9] + "W, avg. windspeed = " + windArrayT[9] + "km/h"
 
//drawing all the charts into the canvasses
i = 0;
for(i; i < deviceCount; i++){
        showGraph(i);
}
i = 0;
for(i; i < fieldCount; i++){
        showGraphField(i);
}
showAllGraph(0);
 
 
 
//function for setting the display to block/none the current values
function DisplayClients(val) {
    var checkBox = document.getElementById("Check"+val);
    var text = document.getElementById("valuesC"+val);
    if (checkBox.checked == false){
        text.style.display = "none";
    }
    else {
        text.style.display = "block";
    }
}
 
//function for adding/subtracting values from the displayed total of the current values and updating the text
function setTotalValues(val){
    var Box = document.getElementById("Check"+val);
    if (Box.checked == false){
        
        i = 0;
        for(i; i < 10; i++){
            if(!isNaN(parseFloat(wattsinArray[val][i]))){
                wattsinArrayT[i] = parseFloat(wattsinArrayT[i]) - parseFloat(wattsinArray[val][i]);
            }
            if(!isNaN(parseFloat(windArray[val][i]))){
                windArrayT[i] = parseFloat(windArrayT[i]) - parseFloat(windArray[val][i]);
            }
            if(!isNaN(parseFloat(wattsoutArray[val][i]))){
                wattsoutArrayT[i] = parseFloat(wattsoutArrayT[i]) - parseFloat(wattsoutArray[val][i]);
            }
        }       
    }
    else {
        i = 0;
        for(i; i < 10; i++){
            if(!isNaN(parseFloat(wattsinArray[val][i]))){
                wattsinArrayT[i] = parseFloat(wattsinArrayT[i]) + parseFloat(wattsinArray[val][i]);
            }
            if(!isNaN(parseFloat(windArray[val][i]))){
                windArrayT[i] = parseFloat(windArrayT[i]) + parseFloat(windArray[val][i]);
            }
            if(!isNaN(parseFloat(wattsoutArray[val][i]))){
                wattsoutArrayT[i] = parseFloat(wattsoutArrayT[i]) + parseFloat(wattsoutArray[val][i]);
            }
        }
    }
    document.getElementById("totalvalues").innerHTML = "current total of selected values: power in = " + wattsinArrayT[9] + "V, power out = " + wattsoutArrayT[9] + "W, avg. windspeed = " + windArrayT[9] + "km/h";
}
 
//function to switch between forecast and charts
function changeforecast(){
    var e = document.getElementById("selectDev");
    var val = e.options[e.selectedIndex].value;
    var o = document.getElementById("selectField");
    var val2 = o.options[o.selectedIndex].value;
    var s = document.getElementById("chart"+val);
    var f = document.getElementById("chartF"+val2);
    var a = document.getElementById("chartAll");
    var w = document.getElementById("windy");
    if(s.style.display != "none" || a.style.display != "none" || f.style.display != "none"){
        s.style.display = "none";
        a.style.display = "none";
        f.style.display = "none";
        w.style.display = "block";
        document.getElementById('FCbutton').textContent = "go to readings";
        document.getElementById('legendtext').style.display = "none";
        e.classList.add("small-offset-8");
        document.getElementById("radiobuttons").style.display = "none";
        document.getElementById("dropdownbar").style.display = "none";
    }
    else{
        if(document.getElementById("devCheck").checked == true){
            s.style.display = "block";
            a.style.display = "none";
            f.style.display = "none";
        }
        else if(document.getElementById("allCheck").checked == true){
            a.style.display = "block";
            s.style.display = "none";
            f.style.display = "none";
        }
        else{
            f.style.display = "block";
            a.style.display = "none";
            s.style.display = "none";
        }
        w.style.display = "none";
        if(document.getElementById('FCbutton').textContent == "go to readings"){
            document.getElementById('FCbutton').textContent = "go to forecast";
        }
        document.getElementById("radiobuttons").style.display = "block";
        document.getElementById("dropdownbar").style.display = "block";
        document.getElementById('FCbutton').textContent = "go to forecast";
        document.getElementById('legendtext').style.display = "block";
        e.classList.remove("small-offset-8");       
    }
}
 
//function to switch between the single device charts
function changecontentDev(){
    var e = document.getElementById("selectDev");
    var val = e.options[e.selectedIndex].value;
    i = 0;
    for(i; i < deviceCount; i++){
        var x = document.getElementById("chart"+i);
        x.style.display = "none";
    }
    var s = document.getElementById("chart"+val);
    s.style.display = "block";
    if(document.getElementById('FCbutton').textContent == "go to readings"){
        document.getElementById('FCbutton').textContent = "go to forecast";
        document.getElementById("windy").style.display = "none";
    }
}
 
//function to switch between the field charts
function changecontentField(){
    var e = document.getElementById("selectField");
    var val = e.options[e.selectedIndex].value;
    i = 0;
    for(i; i < fieldCount; i++){
        var x = document.getElementById("chartF"+i);
        x.style.display = "none";
    }
    var s = document.getElementById("chartF"+val);
    s.style.display = "block";
    if(document.getElementById('FCbutton').textContent == "go to readings"){
        document.getElementById('FCbutton').textContent = "go to forecast";
        document.getElementById("windy").style.display = "none";
    }
}
 
//function to switch between single/field/all charts
function changedropdown(){
    var d = document.getElementById("devCheck");
    var f = document.getElementById("fieldCheck");
    var a = document.getElementById("allCheck");
    
    if (d.checked == true){
        document.getElementById('selectDev').style.display = "block";
        document.getElementById('selectField').style.display = "none";
        document.getElementById('selectAll').style.display = "none";
        document.getElementById('chartAll').style.display = "none";
        
        var e = document.getElementById("selectDev");
        var val = e.options[e.selectedIndex].value;
        var x = document.getElementById("chart"+val);
        x.style.display = "block";
        i = 0;
        for(i; i < fieldCount; i++){
            var s = document.getElementById("chartF"+i);
            s.style.display = "none";
        }
        
    }
    if (f.checked == true){
        document.getElementById('selectDev').style.display = "none";
        document.getElementById('selectField').style.display = "block";
        document.getElementById('selectAll').style.display = "none";
        document.getElementById('chartAll').style.display = "none";
        i = 0;
        for(i; i < deviceCount; i++){
            var x = document.getElementById("chart"+i);
            x.style.display = "none";
        }
        var e = document.getElementById("selectField");
        var val = e.options[e.selectedIndex].value;
        var s = document.getElementById("chartF"+val);
        s.style.display = "block";
    }
    if (a.checked == true){
        document.getElementById('selectDev').style.display = "none";
        document.getElementById('selectField').style.display = "none";
        document.getElementById('selectAll').style.display = "block";
        document.getElementById('chartAll').style.display = "block";
        i = 0;
        for(i; i < deviceCount; i++){
            var x = document.getElementById("chart"+i);
            x.style.display = "none";
        }
        i = 0;
        for(i; i < fieldCount; i++){
            var s = document.getElementById("chartF"+i);
            s.style.display = "none";
        }
    }
}
 
//function to get a date
function getADate(minusDate) {
    var date = new Date();
    date.setDate(date.getDate()-minusDate);
    return date.getDate() + '/' + (date.getMonth()+1) + '/' + date.getFullYear();
}
 
 
//function to draw a chart for single device
function showGraph(val){
    var data = {
      labels: [getADate(9), getADate(8), getADate(7), getADate(6), getADate(5), getADate(4), getADate(3), getADate(2), getADate(1), getADate(0)],
      datasets: [{
        label: "Power in [W]",
        backgroundColor: "rgba(255,203,0,0.2)",
        borderColor: "rgba(255,203,0,1)",
        borderWidth: 2,
        hoverBackgroundColor: "rgba(255,203,0,0.4)",
        hoverBorderColor: "rgba(255,203,0,1)",
        data: [wattsinArray[val][0], wattsinArray[val][1], wattsinArray[val][2], wattsinArray[val][3], wattsinArray[val][4], wattsinArray[val][5], wattsinArray[val][6], wattsinArray[val][7], wattsinArray[val][8], wattsinArray[val][9]],
      },
      {
        label: "Power out [W]",
        backgroundColor: "rgba(255,99,132,0.2)",
        borderColor: "rgba(255,99,132,1)",
        borderWidth: 2,
        hoverBackgroundColor: "rgba(255,99,132,0.4)",
        hoverBorderColor: "rgba(255,99,132,1)",
        data: [wattsoutArray[val][0], wattsoutArray[val][1], wattsoutArray[val][2], wattsoutArray[val][3], wattsoutArray[val][4], wattsoutArray[val][5], wattsoutArray[val][6], wattsoutArray[val][7], wattsoutArray[val][8], wattsoutArray[val][9]],
      }, 
      {
        label: "Wind speed [km/h]",
        backgroundColor: "rgba(0,153,255,0.2)",
        borderColor: "rgba(0,153,255,1)",
        borderWidth: 2,
        hoverBackgroundColor: "rgba(0,153,255,0.4)",
        hoverBorderColor: "rgba(0,153,255,1)",
        data: [windArray[val][0], windArray[val][1], windArray[val][2], windArray[val][3], windArray[val][4], windArray[val][5], windArray[val][6], windArray[val][7], windArray[val][8], windArray[val][9]],
      }]
    };
 
    var options = {
        connectNullData: true,
        maintainAspectRatio: false,
        scales: {
        yAxes: [{
          stacked: false,
          gridLines: {
            display: true,
            color: "rgba(255,99,132,0.2)"
          }
        }],
        xAxes: [{
          gridLines: {
            display: false
          }
        }]
      }
    };
var ctx = document.getElementById("chart"+val);
new Chart(ctx, {
type: 'line',
data: data,
options: options
});
}
 
//function to draw a chart for fields
function showGraphField(val){
    var data = {
      labels: [getADate(9), getADate(8), getADate(7), getADate(6), getADate(5), getADate(4), getADate(3), getADate(2), getADate(1), getADate(0)],
      datasets: [{
        label: "Power in [W]",
        backgroundColor: "rgba(255,203,0,0.2)",
        borderColor: "rgba(255,203,0,1)",
        borderWidth: 2,
        hoverBackgroundColor: "rgba(255,203,0,0.4)",
        hoverBorderColor: "rgba(255,203,0,1)",
        data: [wattsinArrayField[val][0], wattsinArrayField[val][1], wattsinArrayField[val][2], wattsinArrayField[val][3], wattsinArrayField[val][4], wattsinArrayField[val][5], wattsinArrayField[val][6], wattsinArrayField[val][7], wattsinArrayField[val][8], wattsinArrayField[val][9]],
      },
      {
        label: "Power out [W]",
        backgroundColor: "rgba(255,99,132,0.2)",
        borderColor: "rgba(255,99,132,1)",
        borderWidth: 2,
        hoverBackgroundColor: "rgba(255,99,132,0.4)",
        hoverBorderColor: "rgba(255,99,132,1)",
        data: [wattsoutArrayField[val][0], wattsoutArrayField[val][1], wattsoutArrayField[val][2], wattsoutArrayField[val][3], wattsoutArrayField[val][4], wattsoutArrayField[val][5], wattsoutArrayField[val][6], wattsoutArrayField[val][7], wattsoutArrayField[val][8], wattsoutArrayField[val][9]],
      }, 
      {
        label: "Wind speed [km/h]",
        backgroundColor: "rgba(0,153,255,0.2)",
        borderColor: "rgba(0,153,255,1)",
        borderWidth: 2,
        hoverBackgroundColor: "rgba(0,153,255,0.4)",
        hoverBorderColor: "rgba(0,153,255,1)",
        data: [(windArrayField[val][0]/fieldCount), (windArrayField[val][1]/fieldCount), (windArrayField[val][2]/fieldCount), (windArrayField[val][3]/fieldCount), (windArrayField[val][4]/fieldCount), (windArrayField[val][5]/fieldCount), (windArrayField[val][6]/fieldCount), (windArrayField[val][7]/fieldCount), (windArrayField[val][8]/fieldCount), (windArrayField[val][9]/fieldCount)],
      }]
    };
 
    var options = {
        connectNullData: true,
        maintainAspectRatio: false,
        scales: {
        yAxes: [{
          stacked: false,
          gridLines: {
            display: true,
            color: "rgba(255,99,132,0.2)"
          }
        }],
        xAxes: [{
          gridLines: {
            display: false
          }
        }]
      }
    };
var ctx = document.getElementById("chartF"+val);
new Chart(ctx, {
type: 'line',
data: data,
options: options
});
}
 
//function to draw a chart for everything together
function showAllGraph(val){
    var data = {
      labels: [getADate(9), getADate(8), getADate(7), getADate(6), getADate(5), getADate(4), getADate(3), getADate(2), getADate(1), getADate(0)],
      datasets: [{
        label: "Power in [V]",
        backgroundColor: "rgba(255,203,0,0.2)",
        borderColor: "rgba(255,203,0,1)",
        borderWidth: 2,
        hoverBackgroundColor: "rgba(255,203,0,0.4)",
        hoverBorderColor: "rgba(255,203,0,1)",
        data: [wattsinArrayAll[0], wattsinArrayAll[1], wattsinArrayAll[2], wattsinArrayAll[3], wattsinArrayAll[4], wattsinArrayAll[5], wattsinArrayAll[6], wattsinArrayAll[7], wattsinArrayAll[8], wattsinArrayAll[9]],
      },
      {
        label: "Power out [W]",
        backgroundColor: "rgba(255,99,132,0.2)",
        borderColor: "rgba(255,99,132,1)",
        borderWidth: 2,
        hoverBackgroundColor: "rgba(255,99,132,0.4)",
        hoverBorderColor: "rgba(255,99,132,1)",
        data: [wattsoutArrayAll[0], wattsoutArrayAll[1], wattsoutArrayAll[2], wattsoutArrayAll[3], wattsoutArrayAll[4], wattsoutArrayAll[5], wattsoutArrayAll[6], wattsoutArrayAll[7], wattsoutArrayAll[8], wattsoutArrayAll[9]],
      }, 
      {
        label: "avg. Wind speed [km/h]",
        backgroundColor: "rgba(0,153,255,0.2)",
        borderColor: "rgba(0,153,255,1)",
        borderWidth: 2,
        hoverBackgroundColor: "rgba(0,153,255,0.4)",
        hoverBorderColor: "rgba(0,153,255,1)",
        data: [(windArrayAll[0]/deviceCount), (windArrayAll[1]/deviceCount), (windArrayAll[2]/deviceCount), (windArrayAll[3]/deviceCount), (windArrayAll[4]/deviceCount), (windArrayAll[5]/deviceCount), (windArrayAll[6]/deviceCount), (windArrayAll[7]/deviceCount), (windArrayAll[8]/deviceCount), (windArrayAll[9]/deviceCount)],
      }]
    };
 
    var options = {
        connectNullData: true,
        maintainAspectRatio: false,
        scales: {
        yAxes: [{
          stacked: false,
          gridLines: {
            display: true,
            color: "rgba(255,99,132,0.2)"
          }
        }],
        xAxes: [{
          gridLines: {
            display: false
          }
        }]
      }
    };
var ctx = document.getElementById("chartAll");
new Chart(ctx, {
type: 'line',
data: data,
options: options
});
}
 
</script>
</body>
</html>
