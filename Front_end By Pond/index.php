<!DOCTYPE html>
<?php
include("mqtt_test.php");
?>

<!DOCTYPE html>
<html lang="en">
<!-- background -->
<div class="stars"></div>
<div class="twinkling"></div>
<head>

    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>LAZERSHOT</title>

    <!-- Latest compiled and minified CSS -->
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/css/bootstrap.min.css">
    <link rel="stylesheet" href="./style.css">

    <!-- jQuery library -->
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>

    <!-- Latest compiled JavaScript -->
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.0/js/bootstrap.min.js"></script>

    <script src="./script.js"></script>


</head>
<body>
    <div class="container">
        <div class="text-center">
            <h1 style="color: aqua;">DASHBOARD</h1>
        </div>
    </div>

    <!-- HP BAR_V.1 -->

    <!-- <div class="row">
        <div class="col-sm-4"><canvas id="canvas3" width="400" height="400"></canvas></div>
        <div class="col-sm-1"><input id="get_rpm" type="number"/></div>
    </div> -->

    <!-- HP BAR_V.2 -->
    <link href="https://fonts.googleapis.com/css?family=Raleway:400,300,600,800,900" rel="stylesheet" type="text/css">
    <div id="container"></div>

    <!-- ส่วนของ MQTT ของอ๋อง -->
    <br><br>
    <div id="button_time">
        <button class="button" onclick="send('1')">+</button>
        <button class="button" onclick="send('-1')">-</button>
    </div>
    <br><br>

    <!-- การส่งค่าขึ้น MQTT -->
    <div id="button_time">
        <input type="text" id="score" placeholder="Score" required></p>
        <button class="button" onclick="send('S')">send</button>
    </div>

    <br><br>
    <div id="button_time">
        <div class="col-md-1"> <a onclick="start('S')" class="btn btn-sm animated-button thar-two">Start</a> </div>
        <div class="col-md-1"> <a onclick="start('P')" class="btn btn-sm animated-button thar-two">Pause</a> </div>
        <div class="col-md-1"> <a onclick="start('R'), send('R')" class="btn btn-sm animated-button thar-two">Reset</a> </div>
    </div>
    <br><br><br>
    <div id="timer">00:00</div>
    <p id="sub_mqtt">Score: 0</p>
    <p id="player_hp">HP: 100%</p>
    <p id="number">0-0</p>
        <div class="row">
            <div class="col-md-4">
                <a onclick="test_score('1')" class="btn btn-sm animated-button thar-two">1</a>
            </div>
            <div class="col-md-4">
                <a onclick="test_score('2')" class="btn btn-sm animated-button thar-two">2</a>
            </div>
            <div class="col-md-4">
                <a onclick="test_score('3')" class="btn btn-sm animated-button thar-two">3</a>
            </div>
        </div>
        <div class="row">
            <div class="col-md-4">
                <a onclick="test_score('4')" class="btn btn-sm animated-button thar-two">4</a>
            </div>
            <div class="col-md-4">
                <a onclick="test_score('5')" class="btn btn-sm animated-button thar-two">5</a>
            </div>
            <div class="col-md-4">
                <a onclick="test_score('6')" class="btn btn-sm animated-button thar-two">6</a>
            </div>
        </div>
        <div class="row">
            <div class="col-md-4">
                <a onclick="test_score('7')" class="btn btn-sm animated-button thar-two">7</a>
            </div>
            <div class="col-md-4">
                <a onclick="test_score('8')" class="btn btn-sm animated-button thar-two">8</a>
            </div>
            <div class="col-md-4">
                <a onclick="test_score('9')" class="btn btn-sm animated-button thar-two">9</a>
            </div>
        </div>
</body>

</html>