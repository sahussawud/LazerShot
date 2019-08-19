<?php
include('function.php');
 ?>
<form method="POST">
    <label>
        <h3 class="">user_id</h3>
        <sp class=""></sp>
        <input type="text" name="user_id" class="" placeholder="user_id" required="required">
    </label>
    <sp class=""></sp>
    <label>
        <h3 class="">Name</h3>
        <sp class=""></sp>
        <input type="text" name="name" class="" placeholder="Name" required="required">
    </label>
    <sp class=""></sp>
    <label>
        <h3 class="">url_pic</h3>
        <sp class=""></sp>
        <input type="text" name="url_pic" class="" placeholder="url_pic" required="required">
    </label>
    <sp class=""></sp>
     <label>
        <h3 class="">score</h3>
        <sp class=""></sp>
        <input type="text" name="score" class="" placeholder="score" required="required">
    </label>
    <sp class=""></sp>
    <button type="submit" value="send" name="form" class="">Send</button>
</form>

<?php
    print_r(sizeof($_POST));
    if (sizeof($_POST) > 0) {
        $data = $_POST;
        if ($data['form'] == 'send') {
            $user_id = $data['user_id'];
            $name = $data['name'];
            $url_pic = $data['url_pic'];
            $score = $data['score'];
            $sql = "SELECT * FROM user_table WHERE user_id = '$user_id';";
            $result = confetch($sql);
            if ($result[0]['user_id'] != $user_id){
                $sql = "INSERT INTO user_table(user_id, name, url_pic) VALUES('$user_id','$name', '$url_pic')";
                $con = con();
                mysqli_query($con, $sql);
            }
            $sql = "INSERT INTO score_table(owner_id, score) VALUES('$user_id','$score')";
            $con = con();
            mysqli_query($con, $sql);
            echo "Success";
        }
    }
?>