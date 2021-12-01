<!DOCTYPE html>
<?php
session_start();
if(!isset($_SESSION['wrongData1']) || !isset($_SESSION['wrongData2'])){
$_SESSION['wrongData1'] = false;
$_SESSION['wrongData2'] = false;
}
if(isset($_SESSION['username']) && isset($_SESSION['password'])){
header('Location: index.php');
}
 
?>
<!DOCTYPE html>
<html>
<head>
<title>Log in</title>
<link rel="stylesheet" type="text/css" href="foundation.css">
<link rel="stylesheet" type="text/css" href="changes.css">
</head>
<body>
<div class="content" style="height:100%;">
    <div class="grid-x">
        <div class="cell small-8 small-offset-2" style="background-color: white; padding: 1%; margin-top: 8.3333333%; opacity: 0.9;">
            <form method="post" class="log-in-form" action="checklogin.php">
                <h4 class="text-center">Fill in your details</h4>
                    <label>Username
                <input type="text" placeholder="example123" name="username">
                </label>
                <label>Password
                    <input type="password" placeholder="Password" id="show-password" name="password">
                </label>
                <input type="checkbox" onclick="showPW()"><label for="show-password">Show password</label>
                <?php 
                    if($_SESSION['wrongData1']==true){
                        echo "<span style='color:red;'>please fill in all fields</span>";
                    }
                    else if($_SESSION['wrongData2']==true){
                        echo "<span style='color:red;'>this username/password is incorrect</span>";
                    }
                ?>
                <p><input type="submit" class="button expanded" value="Log in"></input></p>
                <p class="text-center"><a href="#" onclick="forgotPassword();">Forgot your password?</a></p>
            </form>
        </div>
    </div>
</div>
<script>
function showPW() {
    var x = document.getElementById("show-password");
    if (x.type === "password") {
        x.type = "text";
    } else {
        x.type = "password";
    }
}
 
function forgotPassword() {
    alert("please contact one of the following options to reset your password:\ntel: 1234567890\nemail: spam@email.com");
}
</script>
</body>
</html>
