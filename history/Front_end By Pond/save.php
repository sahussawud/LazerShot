<?php
    include('function.php');
    function save_name($user_id, $name, $url_pic){
        $sql = "SELECT * FROM user_table WHERE user_id = '$user_id';";
        $result = confetch($sql);
        if ($result[0]['user_id'] != $user_id){
            $sql = "INSERT INTO user_table(user_id, name, url_pic) VALUES('$user_id','$name', '$url_pic')";
            $con = con();
            mysqli_query($con, $sql);
        }
    }

    function save_score($user_id, $score){
        $sql = "INSERT INTO score_table(owner_id, score) VALUES('$user_id','$score')";
        $con = con();
        mysqli_query($con, $sql);
    }
?>