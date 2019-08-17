<script src="paho.javascript-1.0.3/paho-mqtt.js"></script>
<script>
    client = new Paho.MQTT.Client("broker.mqttdashboard.com", Number(8000), "ongsuwannoo");
    client.onConnectionLost = onConnectionLost;
    client.onMessageArrived = onMessageArrived;

    client.connect({onSuccess:onConnect});
    var score = 0;

    function onConnect() {
      console.log("onConnect");
      client.subscribe("rew");
    }

    function send(msg){
      if (msg == 'R'){
        score = 0;
        document.getElementById("demo").innerHTML = score;
      }
      else if (msg == 'S'){
        message = new Paho.MQTT.Message(document.getElementById("score").value);
        message.destinationName = "rew";
        client.send(message);
      }
      else{
        message = new Paho.MQTT.Message(msg);
        message.destinationName = "rew";
        client.send(message);
      }
    }

    function onConnectionLost(responseObject) {
      if (responseObject.errorCode !== 0) {
        console.log("onConnectionLost:"+responseObject.errorMessage);
      }
    }

    function onMessageArrived(message) {
      console.log("onMessageArrived:"+message.payloadString);
      score += Number(message.payloadString);
      document.getElementById("demo").innerHTML = score;
    }

    function random(){
      var min = 1;
      var max = 16;
      number = Math.floor(Math.random() * (+max - +min)) + +min;
      document.getElementById("number").innerHTML = number;
    }

</script>