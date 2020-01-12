var score;
var id, highScore;
auth.onAuthStateChanged(user => {
    //console.log(user);
    if (user) {
        name = user.displayName;
        email = user.email;
        photoUrl = user.photoURL;
        emailVerified = user.emailVerified;
        uid = user.uid;
        console.log("Sign-in provider: " + emailVerified);
        console.log("  Provider-specific UID: " + uid);
        console.log("  Name: " + name);
        console.log("  Email: " + email);
        console.log("  Photo URL: " + photoUrl);
        document.getElementById('email').innerHTML = email;
        document.getElementById('name').innerHTML = name;
        document.title = name;
        id = uid
        db.collection('Users').doc(id).onSnapshot(function (doc) {
            if (doc.data().High_score != 0) {
                document.getElementById('high-score').innerHTML = "Your high score : " + doc.data().High_score;
            }
        });
        showGraph();
    }
});

// send score to flrestore.
const scoreForm = document.querySelector('#score-form');
scoreForm.addEventListener('submit', (e) => {
    e.preventDefault();
    var update = db.collection('Users').doc(id);
    const testScore = scoreForm['score'].value;
    update.onSnapshot(function (doc) {
        if (score.length == 0) {
            update.update({
                High_score: Number(testScore)
            });
        } else {
            if (doc.data().High_score < testScore) {
                update.update({
                    High_score: Number(testScore)
                });
            }
        }
        document.querySelector('#high-score').innerHTML = "Your high score : " + doc.data().High_score;
    });


    console.log(testScore);
    score.push(Number(testScore));
    //
    // db.collection('Users').doc(id).update({
    //     score: score
    // });
    update.update({
        score: score
    });
    scoreForm.reset();
});


function logout() {
    firebase.auth().signOut().then(function () {
        window.location = "index.html";
    }).catch(function (error) {
        console.log(error);
    });
}

function showGraph() {
    console.log(id);
    //db.collection('Users').doc(id).get().then(function (doc) {
    db.collection('Users').doc(id).onSnapshot(function (doc) {
        //console.log(doc.data());
        console.log(doc.data().score);
        score = doc.data().score;

        var i = 1;
        var arrayScore = [];
        var subScore = [];
        doc.data().score.forEach(element => {
            subScore.push(i, element);
            arrayScore.push(subScore);
            subScore = [];
            i++;
        });
        console.log(arrayScore);
        drawLogScales(arrayScore);
    });
}

google.charts.load('current', { packages: ['corechart', 'line'] });
google.charts.setOnLoadCallback(drawLogScales);

function drawLogScales(arrayScore) {
    var data = new google.visualization.DataTable();
    data.addColumn('number', 'X');
    data.addColumn('number', 'score line');

    // data.addRows([
    //     [1, 10], [2, 23], [3, 17], [4, 18]
    // ]);

    data.addRows(arrayScore);

    var options = {
        hAxis: {
            title: 'Time',
            logScale: true
        },
        vAxis: {
            title: 'Score',
            logScale: true
        },
        colors: ['#a52714', '#097138']
    };

    var chart = new google.visualization.LineChart(document.getElementById('chart_div'));
    chart.draw(data, options);
}


// function delAccount() {
//     alert("Delete");
//     var user = firebase.auth().currentUser;
//     console.log(user);



//     user.delete().then(function () {
//         db.collection('Users').doc(uid).get().then(function (doc) {
//             db.collection('Users').doc(doc.id).delete();
//         });
//     }).catch(function (error) {
//         console.log(error);
//     });
// }