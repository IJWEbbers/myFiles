<!DOCTYPE php>
<?php
 session_start();
 session_destroy();
 session_start();
 $_SESSION['wrongData1'] = false;
  $_SESSION['wrongData2'] = false;
 header('Location: login.php');
exit;
?>
