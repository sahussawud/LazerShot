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
        db.collection('Users').doc(uid).get().then(function(doc){
            console.log(doc.data());
        });
    }
});


function logout() {
    firebase.auth().signOut().then(function () {
        window.location = "index.html";
    }).catch(function (error) {
        // An error happened.
    });
}

function delAccount(){
    alert("Delete");
    var user = firebase.auth().currentUser;
    console.log(user);

    

    user.delete().then(function() {
        db.collection('Users').doc(uid).get().then(function(doc){
            db.collection('Users').doc(doc.id).delete();
        });
    }).catch(function(error) {
        console.log(error);
    });

    
    window.location = "index.html";
}

