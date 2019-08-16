var degrees = 0;
    var color = "lightblue";
    var bgcolor = "#222";
    var canvas, ctx, W, Htext;



    function init_rpm(name, val) {
         canvas = document.getElementById(name);
        ctx = canvas.getContext("2d");
        //dimensions
        W = canvas.width;
        H = canvas.height;
        //Clear the canvas everytime a chart is drawn
        ctx.clearRect(0, 0, W, H);

        //Background 360 degree arc
        ctx.beginPath();
        ctx.lineWidth = 25;
        ctx.strokeStyle = bgcolor;
        ctx.arc(W / 2, H / 2, Math.floor(W / 3), 0.7 * Math.PI, 0.3 * Math.PI, false);
        
        ctx.stroke();

        //center circle
        ctx.save();
        ctx.beginPath();
        ctx.strokeStyle = 'rgba(255, 255, 255, .2)';
        ctx.lineWidth = 10;
        ctx.arc(W / 2, H / 2, Math.floor(W / 3) - 40, 0.7 * Math.PI, 0.3 * Math.PI, false);
        ctx.stroke();
        ctx.restore();

        // scale
        ctx.setTransform(1, 0, 0, 1, Math.floor(W / 2), Math.floor(W / 2));
        ctx.beginPath();
        ctx.lineWidth = 2;
        ctx.strokeStyle = 'rgba(255, 255, 255, .3)';
        // there should be 10 lines
        var stepAngle = (Math.PI * 2) / 10;
        // begin angle
        ctx.rotate(0.7 * Math.PI);
        // draw only 9 of the 10 lines
        for (var i = 0; i < 9; i++) {
            ctx.moveTo(Math.floor(W / 3) - 50, 0);
            ctx.lineTo(Math.floor(W / 3) - 55, 0);
            ctx.rotate(stepAngle);
        }
        ctx.stroke();
        ctx.setTransform(1, 0, 0, 1, 0, 0);

        // scale txt
        ctx.fillStyle = 'rgba(255, 255, 255, .4)';
        ctx.font = "1.5vh play";
        ctx.textAlign = 'center';
        ctx.textBaseline = 'middle';

        var stepAngle = (Math.PI * 2) / 10;
        var currentAngle = 0.20 * Math.PI;

      


        //angle in radians =angle in drgrees*pi/180 fill color
        var percent = val / 8000 * 100;
        ctx.beginPath();
        ctx.lineWidth = 30;
        // ctx.strokeStyle= color;
        var my_gradient = ctx.createLinearGradient(0, 150, 250, 300);
        my_gradient.addColorStop(0, "#B31918");
        my_gradient.addColorStop(1, "#FFA000");
        ctx.strokeStyle = my_gradient;
        //the arc  start from the rightmost end. if we deduct 90 degrees from the angles 
        //the arc will start from the top most end
        ctx.arc(W / 2, H / 2, Math.floor(W / 3), 0.7 * Math.PI, 0.7 * Math.PI + 1.6 * Math.PI / 100 * percent, false); //you can see thr src now
        ctx.stroke();


        //add text
        ctx.fillStyle = color;
        ctx.font = "7vh play";
        // text=Math.floor(degrees/360*8)+' RPM';
        text = "15:13";
        text_width = ctx.measureText(text).width;
        ctx.fillText(text, W / 2, H / 2 + 15);

        ctx.font = "4vh play";
        text2 = "95/100";
        ctx.fillText(text2, W / 2, H / 2 + 110);
    }

   
    function draw(val, name, type) {
        // console.log(val);
        if (name != "" || name != null) {

            if (type == "rpm") {
                if (val != "" || val != null) {
                    degrees = val / 1000 / 8 * 360;
                } else {
                    degrees = 180;
                }
                init_rpm(name, val);
            } else if (type == "kmh") {
                if (val != "" || val != null) {
                    degrees = val;
                } else {
                    degrees = 180;
                }
                init_kmh(name);
            }

        } else {
            console.log('can not find canvas id');
        }

    }


    $(document).ready(function () {
        //canvas init

        draw(0, "canvas3", "rpm");



        var rpmControl2 = document.querySelector('input[id=get_rpm]');
        rpmControl2.addEventListener('input', function () {
            draw(this.value, "canvas3", "rpm");
        });


    });