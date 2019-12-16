<?php
// include('mqtt_test.php');
 ?>
<script>
    var hp_player = 100;
    var time = 0;
    var game_state;
    var time_interval = 300;
    var time_send = 4000;
    var count = 0;
    var random_heal_or_enemy = 1;
    var level = 0;
    var i = 0;
    var persent = 25;
    var number_board;
    var state_score = 0;
    var score = 0;

    var pattern = [0,1,2, 2,0,4, 1,3,5, 2,4,3, 5,3,4, 3,5,8, 4,7,6, 5,8,7, 6,7,8, 7,8,8]; // main pattern | 3 level
    var pattern_number = [
        [5,4,3,1,4,7,9,11,8,7],   // A 0
        [10,7,8,9,5,4,3,1,2,4],   // B 1
        [8,4,1,2,3,7,8,9,5,4],    // C 2
        [5,14,9,4,3,12,5,1,4,7],  // D 3
        [1,5,4,8,11,7,6,1,3,9],   // E 4
        [12,7,6,14,5,9,5,4,3,8],  // F 5
        [5,11,6,1,8,4,10,6,1,9],  // G 6
        [9,1,6,10,4,11,2,5,12,7], // H 7
        [12,4,1,3,8,1,9,2,5,11]   // I 8
    ];
    // A B C   C A E   B D F   C E D   F D E   D F I   E H G   F I H   G H I   H I G
    game_state = setInterval(send_game_state, time_interval);

    function send_game_state(){

        if (persent > Math.floor(Math.random() * 100)) {
            random_heal_or_enemy = 2; // random HP
        }

        number_board = pattern_number[pattern[level]][i]; // number board
        if (number_board < 10){
            number_board = "0"+number_board;
        } if (random_heal_or_enemy < 10){
            random_heal_or_enemy = "0"+random_heal_or_enemy;
        }
        console.log(number_board, random_heal_or_enemy, time_send, time_interval, "Score :", score);
        // send(); // send pattern topic 'test_input'

        i++; // next board

        state_score = 0; //defult

        if (i % 10 == 0){
            console.log('next', level+1);
            i = 0;
            if (level != 10)
                level++;
        }

        if (level % 3 == 0 & level != 0 & i % 10 == 0){
            // clearInterval(game_state);
            Bonus_State();
        }

        if (level == 3 & i == 0){
            time_send = 3500;
        } else if (level == 5){
            time_send = 3000;
        } else if (level == 8 & i == 0){
            time_send = 2500;
            time_interval = 250;
            clearInterval(game_state);
            game_state = setInterval(send_game_state, time_interval);
        } else if (level == 9 & i == 0){
            time_send = 2000;
        } else if (level == 10 & i == 0){
            time_interval = 200;
            clearInterval(game_state);
            game_state = setInterval(send_game_state, time_interval);
        }
        random_heal_or_enemy = 1;
    }
    function Bonus_State(){
        console.log('Bonus_State');
        state_score = 2;
    }

    function check_score(num){
        if (num == 1) {
            state_score = 1;
            score += 1;
        } else if (num == -1) {
            state_score = 1;
            player_hp -= 10;
        } else if (num == 2) {
            state_score = 1;
            score += 1;
            player_hp += 5
        }
    }
</script>