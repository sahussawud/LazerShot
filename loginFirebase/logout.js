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
    db.collection('Users').get().then((snapshot)=>{
        snapshot.forEach(doc=>{
            if(user.displayName == doc.data().Name){
                console.log(doc.id, " : id => ", doc.data().Name);
                db.collection('Users').doc(doc.id).delete();
                console.log("Delete DB successfull");
            }
        });
    }); 
    user.delete().then(function() {
        console.log("Delete account successfull");
        window.location = "index.html";
    }).catch(function(error) {
        console.log(error);
    });
    
    
}

