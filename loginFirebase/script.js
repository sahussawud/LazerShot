// get data
const db = firebase.firestore();
db.collection('Users').get().then(snapshot => {
    snapshot.forEach(doc => {
        console.log(doc.data());
    });
});

// auth.onAuthStateChanged(user => {
//     console.log(user);
// });


const signupForm = document.querySelector('#signUp-Form');
signupForm.addEventListener('submit', (e) => {
    e.preventDefault();

    //get user info
    const email = signupForm['signUp-Email'].value;
    const password = signupForm['signUp-Password'].value;
    const checkPassword = signupForm['signUp-Password2'].value;
    const name = signupForm['signUp-Name'].value;
    console.log(email, password, name);

    //sign up the user
    if (password == checkPassword) {
        auth.createUserWithEmailAndPassword(email, password).then(cred => {
            console.log(cred.user.uid)
            signupForm.reset();
            $('#modal-1').modal('hide');
            cred.user.updateProfile({
                displayName: name
            }).then(function () {
                // Update successful.
            }).catch(function (error) {
                // An error happened.
            });

            console.log(cred.user);
            db.collection('Users').doc(cred.user.uid).set({
                Name: name,
                Email: email,
                Password: password
            });
            
        });
    } else {
        alert("Sign up fail");
        signupForm.reset();
    }

});

const loginForm = document.querySelector('#login-form');
loginForm.addEventListener('submit', (e) => {
    e.preventDefault();

    //get user info
    const email = loginForm['login-Email'].value;
    const password = loginForm['login-Password'].value;

    auth.signInWithEmailAndPassword(email, password).then(cred => {
        console.log(cred.user);
        signupForm.reset();
        window.location = "user.html";
    }).catch(function (error) {
        // Handle Errors here.
        var errorCode = error.code;
        var errorMessage = error.message;
        console.log(errorMessage);
        alert("Login fail");
        loginForm.reset();
    });
});

function forgetpass() {
    var emailAddress = document.querySelector('#login-form').email.value;
    auth.sendPasswordResetEmail(emailAddress).then(function () {
        console.log(emailAddress);
    }).catch(function (error) {
        console.log(error);
    });
    
}
