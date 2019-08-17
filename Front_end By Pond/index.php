<!DOCTYPE html>
<?php
    include("mqtt_test.php")
?>

<html>
    <head>

    </head>
    <body>
        <button class="btn-hover color-2" onclick="send('1')">+</button>
        <button class="btn-hover color-2" onclick="send('-1')">-</button>
        <button class="btn-hover color-2" onclick="random()">Random</button>
        <button class="btn-hover color-2" onclick="send('R')">Reset</button>
<!--         <form method="POST">
            <input type="text" id="score" placeholder="Score" required></p>
            <button class="btn-hover color-2" onclick="send()">send</button>
        </form> -->
        <p id="demo">X</p>
        <p id="number">1</p>
    </body>
    <style>
        #demo{
        text-align: center;
        top:200px;
        color: green;
        font-size: 50px;
        font-family: 'Pacifico', cursive;
        }
        #number{
        text-align: center;
        top:200px;
        font-size: 50px;
        font-family: 'Pacifico', cursive;
        }
    </style>
</html>