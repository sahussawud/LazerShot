var data = [];
var user_name;
var score;
var highScore;
var history;
var txt = "";
auth.onAuthStateChanged(user => {
    //console.log(user);
    if (user) {
        name = user.displayName;
        email = user.email;
        photoUrl = user.photoURL;
        emailVerified = user.emailVerified;
        uid = user.uid;
        user_name = name;
        console.log("Sign-in provider: " + emailVerified);
        console.log("  Provider-specific UID: " + uid);
        console.log("  Name: " + name);
        console.log("  Email: " + email);
        console.log("  Photo URL: " + photoUrl);
        document.getElementById('name').innerHTML = name;
        document.title = name;

        db.collection('Users').doc(uid).get().then(function(doc){
            console.log(doc.data().score);
            score = doc.data().score;
            highScore = doc.data().High_score;
            txt = "";
            var i = 0;
            var count = score.length;
            // while (1) {
            //     if (count == 0 || i == 5){
            //         break;
            //     } else {
            //         txt += "<div>"+(i+1)+". "+score[count-1]+"</div>";
            //         i++;
            //         count--;
            //     }
            // }
            // document.getElementById('history').innerHTML = txt;
        });


        txt = "";
        // console.log("admin");
        txt += '<table class="table table-hover mt-5" id="table0">';
        txt += '<thead>';
        txt += '<tr>';
        txt += '<th scope="col">No.</th>';
        txt += '<th scope="col">Name</th>';
        txt += '<th scope="col">Score</th>';
        // txt += '<th scope="col">Time</th>';
        // txt += '<th scope="col">DEL</th>';
        txt += '</tr>';
        txt += '</thead>';
        txt += '<tbody></tbody>';
        txt += '</table>';
        document.getElementById("out").innerHTML = txt;

        db.collection('Users').get().then((snapshot)=>{
            snapshot.forEach(doc=>{
                var dic = {Name:doc.data().Name, Score:doc.data().High_score, Time:"101010", ID:doc.id};
                data.push(dic);
                console.log(data);
                if (data.length == snapshot.size){
                    data.sort(function (a, b) {
                        return b.Score - a.Score;
                    });
                    data.forEach(dic => createTable([dic.Name, dic.Score, dic.Time, dic.ID]));
                }

                // createTable(lis);
            })
        })


        // var lis = [name, "999", "10_10_20:10:30", "5yT1mrdfe7TRnNQ3pnREXxL3wNz1"];
        // createTable(lis);

    }
});

function createTable (lis){
    var name = lis[0];
    var score = lis[1];
    var time = lis[2];
    var btn = '<button type="button" class="btn btn-danger" disabled>Delete</button>';

    var table = document.getElementById("table0");
    var count = table.tBodies[0].childElementCount;

    var nRow = table.tBodies[0].insertRow(count);
    console.log(user_name+" "+name);
    if (user_name == name)
        nRow.className = "table-primary";
    var lis = [count+1, name, score, /*time, btn*/];

    for (i in lis) {
        console.log(i, lis[i]);
        if (i == 2){
            nRow.insertCell(i).setAttribute('id', lis[1]);
            document.getElementById(lis[1]).innerHTML = lis[i];
        }
        else
            nRow.insertCell(i).innerHTML = lis[i];
    }
}

function logout() {
    firebase.auth().signOut().then(function () {
        window.location = "index.html";
    }).catch(function (error) {
        // An error happened.
    });
}


function updateScore(id, score) {
    for (i in data){
        if (data[i].Name == id) {
            data[i].Score = score;
            // console.log(data[i]);
            var table = document.getElementById("table0");
            //or use :  var table = document.all.tableid;
            for(var i = table.rows.length - 1; i > 0; i--)
            {
                table.deleteRow(i);
            }
            data.sort(function (a, b) {
                return b.Score - a.Score;
            });

            data.forEach(dic => createTable([dic.Name, dic.Score, dic.Time, dic.ID]));
        }
    }
}
