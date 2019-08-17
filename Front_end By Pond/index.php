<!DOCTYPE html>
<?php
    include("mqtt_test.php")
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
    <div class="container-fluid">

        <div class="media col-sm-4">
            <div class="media-left">
                <img src="https://cdn.shopify.com/s/files/1/2265/4045/products/Productshot.jpg?v=1545336364" class="media-object" style="width:100px">
            </div>
                <div class="media-body">
                    <h4 class="media-heading" style="color: azure">NAME : IP 198.168.0.1</h4>
                    <img src="https://thumbs.gfycat.com/WideShowyJohndory.webp" style="width: 180px">
                </div>
            </div>
        </div>

    <!-- HP BAR_V.1 -->

    <div class="row">
            <div class="col-sm-4"><canvas id="canvas3" width="400" height="400"></canvas></div>
            <div class="col-sm-1"><input id="get_rpm" type="number"/></div>
    </div>

    <div id="timer">00:00</div>
    <br><br>
    <div style="text-align: center;">
        <div class="col-md-1 col-sm-1 col-xs-3"> <a onclick="start('S')" class="btn btn-sm animated-button thar-two">Start</a> </div>
        <!-- <button class="button Start" onclick="start('S')">Start</button> -->
        <button class="button Start" onclick="start('P')">Pause</button>
        <button class="button Start" onclick="start('R')">Reset</button>

    </div>
    <!-- ศส่วนของ MQTT ของอ๋อง -->

        <button class="button" onclick="send('1')">+</button>
        <button class="button" onclick="send('-1')">-</button>
        <button class="button" onclick="random()">Random</button>
        <button class="button" onclick="send('R')">Reset</button>
    <!-- การส่งค่าขึ้น MQTT -->
    <input type="text" id="score" placeholder="Score" required></p>
    <button class="btn-hover color-2" onclick="send('S')">send</button>
    <p id="sub_mqtt">X</p>
    <p id="number">1</p>
</body>

</body>
</html>