
// var degrees = 0;
// var color = "lightblue";
// var bgcolor = "#222";
// var canvas, ctx, W, Htext;



// function init_rpm(name, val) {
//    canvas = document.getElementById(name);
//    ctx = canvas.getContext("2d");
//         //dimensions
//         W = canvas.width;
//         H = canvas.height;
//         //Clear the canvas everytime a chart is drawn
//         ctx.clearRect(0, 0, W, H);

//         //Background 360 degree arc
//         ctx.beginPath();
//         ctx.lineWidth = 25;
//         ctx.strokeStyle = bgcolor;
//         ctx.arc(W / 2, H / 2, Math.floor(W / 3), 0.7 * Math.PI, 0.3 * Math.PI, false);

//         ctx.stroke();

//         //center circle
//         ctx.save();
//         ctx.beginPath();
//         ctx.strokeStyle = 'rgba(255, 255, 255, .2)';
//         ctx.lineWidth = 10;
//         ctx.arc(W / 2, H / 2, Math.floor(W / 3) - 40, 0.7 * Math.PI, 0.3 * Math.PI, false);
//         ctx.stroke();
//         ctx.restore();

//         // scale
//         ctx.setTransform(1, 0, 0, 1, Math.floor(W / 2), Math.floor(W / 2));
//         ctx.beginPath();
//         ctx.lineWidth = 2;
//         ctx.strokeStyle = 'rgba(255, 255, 255, .3)';
//         // there should be 10 lines
//         var stepAngle = (Math.PI * 2) / 10;
//         // begin angle
//         ctx.rotate(0.7 * Math.PI);
//         // draw only 9 of the 10 lines
//         for (var i = 0; i < 9; i++) {
//             ctx.moveTo(Math.floor(W / 3) - 50, 0);
//             ctx.lineTo(Math.floor(W / 3) - 55, 0);
//             ctx.rotate(stepAngle);
//         }
//         ctx.stroke();
//         ctx.setTransform(1, 0, 0, 1, 0, 0);

//         // scale txt
//         ctx.fillStyle = 'rgba(255, 255, 255, .4)';
//         ctx.font = "1.5vh play";
//         ctx.textAlign = 'center';
//         ctx.textBaseline = 'middle';

//         var stepAngle = (Math.PI * 2) / 10;
//         var currentAngle = 0.20 * Math.PI;




//         //angle in radians =angle in drgrees*pi/180 fill color
//         var percent = val / 8000 * 100;
//         ctx.beginPath();
//         ctx.lineWidth = 30;
//         // ctx.strokeStyle= color;
//         var my_gradient = ctx.createLinearGradient(0, 150, 250, 300);
//         my_gradient.addColorStop(0, "#B31918");
//         my_gradient.addColorStop(1, "#FFA000");
//         ctx.strokeStyle = my_gradient;
//         //the arc  start from the rightmost end. if we deduct 90 degrees from the angles
//         //the arc will start from the top most end
//         ctx.arc(W / 2, H / 2, Math.floor(W / 3), 0.7 * Math.PI, 0.7 * Math.PI + 1.6 * Math.PI / 100 * percent, false); //you can see thr src now
//         ctx.stroke();


//         //add text
//         ctx.fillStyle = color;
//         ctx.font = "7vh play";
//         // text=Math.floor(degrees/360*8)+' RPM';
//         text = "";
//         text_width = ctx.measureText(text).width;
//         ctx.fillText(text, W / 2, H / 2 + 15);

//         ctx.font = "4vh play";
//         text2 = "95/100";
//         ctx.fillText(text2, W / 2, H / 2 + 110);
//     }


//     function draw(val, name, type) {
//         // console.log(val);
//         if (name != "" || name != null) {

//             if (type == "rpm") {
//                 if (val != "" || val != null) {
//                     degrees = val / 1000 / 8 * 360;
//                 } else {
//                     degrees = 180;
//                 }
//                 init_rpm(name, val);
//             } else if (type == "kmh") {
//                 if (val != "" || val != null) {
//                     degrees = val;
//                 } else {
//                     degrees = 180;
//                 }
//                 init_kmh(name);
//             }

//         } else {
//             console.log('can not find canvas id');
//         }

//     }


//     $(document).ready(function () {
//         //canvas init

//         draw(0, "canvas3", "rpm");



//         var rpmControl2 = document.querySelector('input[id=get_rpm]');
//         rpmControl2.addEventListener('input', function () {
//             draw(this.value, "canvas3", "rpm");
//         });


//     });
//     var degrees = 0;
//     var color = "lightblue";
//     var bgcolor = "#222";
//     var canvas, ctx, W, Htext;



//     function init_rpm(name, val) {
//        canvas = document.getElementById(name);
//        ctx = canvas.getContext("2d");
//         //dimensions
//         W = canvas.width;
//         H = canvas.height;
//         //Clear the canvas everytime a chart is drawn
//         ctx.clearRect(0, 0, W, H);

//         //Background 360 degree arc
//         ctx.beginPath();
//         ctx.lineWidth = 25;
//         ctx.strokeStyle = bgcolor;
//         ctx.arc(W / 2, H / 2, Math.floor(W / 3), 0.7 * Math.PI, 0.3 * Math.PI, false);
//         ctx.stroke();

//         //center circle
//         ctx.save();
//         ctx.beginPath();
//         ctx.strokeStyle = 'rgba(255, 255, 255, .2)';
//         ctx.lineWidth = 10;
//         ctx.arc(W / 2, H / 2, Math.floor(W / 3) - 40, 0.7 * Math.PI, 0.3 * Math.PI, false);
//         ctx.stroke();
//         ctx.restore();

//         // scale
//         ctx.setTransform(1, 0, 0, 1, Math.floor(W / 2), Math.floor(W / 2));
//         ctx.beginPath();
//         ctx.lineWidth = 2;
//         ctx.strokeStyle = 'rgba(255, 255, 255, .3)';
//         // there should be 10 lines
//         var stepAngle = (Math.PI * 2) / 10;
//         // begin angle
//         ctx.rotate(0.7 * Math.PI);
//         // draw only 9 of the 10 lines
//         for (var i = 0; i < 9; i++) {
//             ctx.moveTo(Math.floor(W / 3) - 50, 0);
//             ctx.lineTo(Math.floor(W / 3) - 55, 0);
//             ctx.rotate(stepAngle);
//         }
//         ctx.stroke();
//         ctx.setTransform(1, 0, 0, 1, 0, 0);

//         // scale txt
//         ctx.fillStyle = 'rgba(255, 255, 255, .4)';
//         ctx.font = "1.5vh play";
//         ctx.textAlign = 'center';
//         ctx.textBaseline = 'middle';

//         var stepAngle = (Math.PI * 2) / 10;
//         var currentAngle = 0.20 * Math.PI;




//         //angle in radians =angle in drgrees*pi/180 fill color
//         var percent = val / 8000 * 100;
//         ctx.beginPath();
//         ctx.lineWidth = 30;
//         // ctx.strokeStyle= color;
//         var my_gradient = ctx.createLinearGradient(0, 150, 250, 300);
//         my_gradient.addColorStop(0, "#B31918");
//         my_gradient.addColorStop(1, "#FFA000");
//         ctx.strokeStyle = my_gradient;
//         //the arc  start from the rightmost end. if we deduct 90 degrees from the angles
//         //the arc will start from the top most end
//         ctx.arc(W / 2, H / 2, Math.floor(W / 3), 0.7 * Math.PI, 0.7 * Math.PI + 1.6 * Math.PI / 100 * percent, false); //you can see thr src now
//         ctx.stroke();


//         //add text
//         ctx.fillStyle = color;
//         ctx.font = "7vh play";
//         // text=Math.floor(degrees/360*8)+' RPM';
//         text = "";
//         text_width = ctx.measureText(text).width;
//         ctx.fillText(text, W / 2, H / 2 + 15);

//         ctx.font = "4vh play";
//         text2 = "95/100";
//         ctx.fillText(text2, W / 2, H / 2 + 110);
//     }


//     function draw(val, name, type) {
//         // console.log(val);
//         if (name != "" || name != null) {

//             if (type == "rpm") {
//                 if (val != "" || val != null) {
//                     degrees = val / 1000 / 8 * 360;
//                 } else {
//                     degrees = 180;
//                 }
//                 init_rpm(name, val);
//             } else if (type == "kmh") {
//                 if (val != "" || val != null) {
//                     degrees = val;
//                 } else {
//                     degrees = 180;
//                 }
//                 init_kmh(name);
//             }

//         } else {
//             console.log('can not find canvas id');
//         }

//     }


//     $(document).ready(function () {
//         //canvas init

//         draw(0, "canvas3", "rpm");



//         var rpmControl2 = document.querySelector('input[id=get_rpm]');
//         rpmControl2.addEventListener('input', function () {
//             draw(this.value, "canvas3", "rpm");
//         });


//     });

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
