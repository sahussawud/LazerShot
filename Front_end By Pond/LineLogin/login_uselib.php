<?php
session_start();
require_once("LineLoginLib.php");
include('../save.php');

// กรณีต้องการตรวจสอบการแจ้ง error ให้เปิด 3 บรรทัดล่างนี้ให้ทำงาน กรณีไม่ ให้ comment ปิดไป
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

// กรณีมีการเชื่อมต่อกับฐานข้อมูล
//require_once("dbconnect.php");

/// ส่วนการกำหนดค่านี้สามารถทำเป็นไฟล์ include แทนได้
define('LINE_LOGIN_CHANNEL_ID','1609992858');
define('LINE_LOGIN_CHANNEL_SECRET','f449135cfebc81aaccc95f4ab4e5b08b');
define('LINE_LOGIN_CALLBACK_URL','http://www.it.kmitl.ac.th/~it61070022/LazerShot/LineLogin/login_uselib_callback.php');

$LineLogin = new LineLoginLib(
    LINE_LOGIN_CHANNEL_ID, LINE_LOGIN_CHANNEL_SECRET, LINE_LOGIN_CALLBACK_URL);

if(!isset($_SESSION['ses_login_accToken_val'])){
    $LineLogin->authorize();
    exit;
}

$accToken = $_SESSION['ses_login_accToken_val'];
// Status Token Check
if($LineLogin->verifyToken($accToken)){
    echo $accToken."<br><hr>";
    echo "Token Status OK <br>";
}


echo "<pre>";
// Status Token Check with Result
//$statusToken = $LineLogin->verifyToken($accToken, true);
//print_r($statusToken);


//////////////////////////
echo "<hr>";
// GET LINE USERID FROM USER PROFILE
//$userID = $LineLogin->userProfile($accToken);
//echo $userID;

//////////////////////////
echo "<hr>";
// GET LINE USER PROFILE
$userInfo = $LineLogin->userProfile($accToken,true);
if(!is_null($userInfo) && is_array($userInfo) && array_key_exists('userId',$userInfo)){
    print_r($userInfo);
}

//exit;
echo "<hr>";

if(isset($_SESSION['ses_login_userData_val']) && $_SESSION['ses_login_userData_val']!=""){
    // GET USER DATA FROM ID TOKEN
    $lineUserData = json_decode($_SESSION['ses_login_userData_val'],true);
    print_r($lineUserData);
    echo "<hr>";
    echo "Line UserID: ".$lineUserData['sub']."<br>";
    echo "Line Display Name: ".$lineUserData['name']."<br>";
    echo '<img style="width:100px;" src="'.$lineUserData['picture'].'" /><br>';
    save_name($lineUserData['sub'], $lineUserData['name'], $lineUserData['picture']);
}


echo "<hr>";
if(isset($_SESSION['ses_login_refreshToken_val']) && $_SESSION['ses_login_refreshToken_val']!=""){
    echo '
    <form method="post">
    <button type="submit" name="refreshToken">Refresh Access Token</button>
    </form>
    ';
}
if(isset($_SESSION['ses_login_refreshToken_val']) && $_SESSION['ses_login_refreshToken_val']!=""){
    if(isset($_POST['refreshToken'])){
        $refreshToken = $_SESSION['ses_login_refreshToken_val'];
        $new_accToken = $LineLogin->refreshToken($refreshToken);
        if(isset($new_accToken) && is_string($new_accToken)){
            $_SESSION['ses_login_accToken_val'] = $new_accToken;
        }
        $LineLogin->redirect("login_uselib.php");
    }
}
// Revoke Token
//if($LineLogin->revokeToken($accToken)){
//  echo "Logout Line Success<br>";
//}
//
// Revoke Token with Result
//$statusRevoke = $LineLogin->revokeToken($accToken, true);
//print_r($statusRevoke);
?>
<?php
echo "<hr>";
if($LineLogin->verifyToken($accToken)){
?>
<form method="post">
<button type="submit" name="lineLogout">LINE Logout</button>
</form>
<?php }else{ ?>
<form method="post">
<button type="submit" name="lineLogin">LINE Login</button>
</form>
<?php } ?>
<?php
if(isset($_POST['lineLogin'])){
    $LineLogin->authorize();
    exit;
}
if(isset($_POST['lineLogout'])){
    unset(
        $_SESSION['ses_login_accToken_val'],
        $_SESSION['ses_login_refreshToken_val'],
        $_SESSION['ses_login_userData_val']
    );
    echo "<hr>";
    if($LineLogin->revokeToken($accToken)){
        echo "Logout Line Success<br>";
    }
    echo '
    <form method="post">
    <button type="submit" name="lineLogin">LINE Login</button>
    </form>
    ';
    $LineLogin->redirect("login_uselib.php");
}
?>