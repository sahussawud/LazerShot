// import "paho.javascript-1.0.3/paho-mqtt.js";
var clientid = "asdasdasdasd";
client = new Paho.MQTT.Client("broker.mqttdashboard.com", Number(8000), clientid);
client.onConnectionLost = onConnectionLost;
client.onMessageArrived = onMessageArrived;

client.connect({onSuccess:onConnect});

var topic_sup = "lazershot/Score";
var topic_pub = "test_output_ong";
var mq_to_msg;
var state_call = 0;
var num = 0;


auth.onAuthStateChanged(user => {
    //console.log(user);
    if (user) {
        name = user.displayName;
        email = user.email;
        photoUrl = user.photoURL;
        emailVerified = user.emailVerified;
        uid = user.uid;
        user_name = name;
        db.collection('Users').doc(uid).get().then(function(doc){
            console.log(doc.data().score);
            score = doc.data().score;
            highScore = doc.data().High_score;
            txt = "";
            var i = 0;
            var count = score.length;
        });
    }
});



function onConnect() {
    console.log("onConnect");
    client.subscribe(topic_sup);
    state_call = 1;
// document.getElementById("stage").innerHTML = "Ready";
// document.getElementById("stage").style.color = "lightgreen";

}

function send(msg){
    if (msg == 'R'){
        score = 0;
        // document.getElementById("sub_mqtt").innerHTML = "Score: "+score;
    }
    else if (msg == 'S'){
        // message = new Paho.MQTT.Message(document.getElementById("score").value);
        message.destinationName = topic_pub;
        client.send(message);
    }
    else{
        // message = new Paho.MQTT.Message(msg);
        message.destinationName = topic_pub;
        client.send(message);
    }
}

function onConnectionLost(responseObject) {
    if (responseObject.errorCode !== 0) {
        console.log("onConnectionLost:"+responseObject.errorMessage);
        // setTimeout(function(){window.location.reload(true);}, 5000);
    }
}

function onMessageArrived(message) {
    mq_to_msg = message.payloadString;
    console.log("onMessageArrived:"+mq_to_msg);
    // if (mq_to_msg == "F") {
        num = Number(mq_to_msg);
        var update = db.collection('Users').doc(uid);
        const testScore = num;
        update.onSnapshot(function (doc) {
            if (score.length == 0) {
                update.update({
                    High_score: testScore
                });
            } else {
                if (doc.data().High_score < testScore) {
                    update.update({
                        High_score: testScore
                    });
                }
            }
        });

        score.push(num);

        update.update({
            score: score
        });
        setTimeout(function(){window.location = 'score.html';}, 10000);
    // }
    // else {
        // num += Number(mq_to_msg);
        // console.log(num+" "+highScore);
        // document.getElementById('score_board').innerHTML = num
        // if (num > highScore){
            // document.getElementById(name).innerHTML = num;
            // updateScore(name, Number(document.getElementById(name).innerHTML));
        // }

    // }

}


function isNumeric(n) {
    return !isNaN(parseFloat(n)) && isFinite(n);
}