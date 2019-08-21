
    var pos;
    var myVar;
    var myRandom;
    var second = 0;
    var minute = 0;
    var state = 0;
    var number = 0;
    var state_score = 0;
    var player_hp = 100;
    var time_;
    var time_interval = 1500;
    function start(msg){
        if (msg == 'P'){
            clearInterval(myVar);
            clearInterval(myRandom);
            state = 0;
        }
        if (msg == 'R'){
            clearInterval(myVar);
            clearInterval(myRandom);
            second = 0;
            minute = 0;
            state = 0;
            player_hp = 100;
            document.getElementById("timer").innerHTML = "00:00";
            document.getElementById("number").innerHTML = 1 + "-" + 1;
        }
        if (msg == 'S' && state == 0) {
            myVar = setInterval(myTimer, 1000);
            myRandom = setInterval(random, time_interval);
            function myTimer() {
                if (second % 60 == 0 && second != 0)
                    minute += 1;
                if (second%60 < 10 && minute < 10){
                    document.getElementById("timer").innerHTML = "0" + minute + ":" + "0" + second%60;
                } else if (second%60 < 10){
                    document.getElementById("timer").innerHTML = minute + ":" + "0" + second%60;
                } else if (minute < 10){
                    document.getElementById("timer").innerHTML = "0" + minute + ":" + second%60;
                } else {
                    document.getElementById("timer").innerHTML = minute + ":" + second%60;
                }
                second += 1;
                state = 1;
            }
            function random(){
                var min = 1;
                var max = 10;
                var random_heal_or_enemy = 1;
                number = Math.floor(Math.random() * (+max - +min)) + +min;
                if (state_score == 0 && second != 1){
                    player_hp -= 10;
                    // send('-1');
                } if (player_hp <= 0){
                    start('P');
                    time_ = document.getElementById("timer").innerHTML;
                    alert("Score: "+score+"\n"+"Time: "+time_);
                    player_hp = 100;
                    document.getElementById("number").innerHTML = 1 + "-" + 1;
                    start('R');
                    send('R');
                }
                state_score = 0;
                if (20 > Math.floor(Math.random() * 100)) {
                  var random_heal_or_enemy = 2;
                }
                document.getElementById("sub_mqtt").style.color = "lightblue";
                document.getElementById("number").innerHTML = number + "-" + random_heal_or_enemy;
                document.getElementById("player_hp").innerHTML = "HP: "+player_hp+"%";
                // if (number < 10)
                //     number = "0"+number;
                // if (random_heal_or_enemy < 10)
                //     random_heal_or_enemy = "0"+random_heal_or_enemy;
                // send("01"+","+"01"+","+"1500");
            }
        }
    }
    function test_score(pos){
        if (pos == number && state_score == 0){
            document.getElementById("sub_mqtt").style.color = "lightgreen";
            state_score = 1;
            send('1');
        } else if (state_score == 0) {
            document.getElementById("sub_mqtt").style.color = "red";
            state_score = 1;
            player_hp -= 5;
            // send('-1');
        }
    }
