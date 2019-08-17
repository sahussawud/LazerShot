<!DOCTYPE html>
<?php
    include("mqtt_test.php")
?>

<!DOCTYPE html>
<html lang="en">
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
        <div class="row">
            <div class="col-sm-1">
                    <center>
                        <h1 style="color: aqua;">DASHBOARD</h1>
                    </center>

            </div>
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

    <div id="clockdiv">
        <div>
            <span class="days" id="day"></span>
            <div class="smalltext">Days</div>
        </div>
        <div>
            <span class="hours" id="hour"></span>
            <div class="smalltext">Hours</div>
        </div>
        <div>
            <span class="minutes" id="minute"></span>
            <div class="smalltext">Minutes</div>
        </div>
        <div>
            <span class="seconds" id="second"></span>
            <div class="smalltext">Seconds</div>
        </div>
    </div>

<p id="time"></p>

    <!-- ศส่วนของ MQTT ของอ๋อง -->
    <button class="btn-hover color-2" onclick="send('1')">+</button>
    <button class="btn-hover color-2" onclick="send('-1')">-</button>
    <button class="btn-hover color-2" onclick="random()">Random</button>
    <button class="btn-hover color-2" onclick="send('R')">Reset</button>
    <!-- การส่งค่าขึ้น MQTT -->
    <input type="text" id="score" placeholder="Score" required></p>
    <button class="btn-hover color-2" onclick="send('S')">send</button>
    <p id="sub_mqtt">X</p>
    <p id="number">1</p>
</body>

</body>
</html>