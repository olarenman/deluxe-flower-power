<?php

session_start();


if(isset($_SESSION['username'])) {  
    if($_SESSION['username'] == 'admin') {
        include 'admin.php';
    }
    else {
        include 'plant.php';
    }
}
