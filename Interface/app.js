//database
const db = firebase.database();
const userinfo = db.ref("users");
const newuser = db.ref("latest_key/key");
const top100 = db.ref("top100");
const query = userinfo.orderByChild("score").limitToLast(100);
new Vue({
  el:"#rank",
  data:{
    name:'',
    rankscore:[],
    score:0,
  },
  methods:{
    storeRank:function(){
      userinfo.push({name:this.name,score:this.score});
    }
  },
  created(){
    top100.remove();
    query.on('value', function (snapshot) {
      snapshot.forEach(function (childSnapshot) {
          top100.push(childSnapshot.val());
          //console.log(rankscore);
      });
    });

    userinfo.limitToLast(1).on('child_added', snapshot=>{
      var rankscore = snapshot.val();
      newuser.set(snapshot.key);
      //rankscore='';
      //console.log(rankscore);
    });

    //top100.on('child_added', snapshot=>{
    //  rankscore=snapshot.val();
    //  this.rankscore.push(snapshot.val());
    //})
  }
})
