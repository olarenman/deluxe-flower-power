<?php

session_start();

if (!empty($_POST['newUsername']) and !empty($_POST['newPassword'])) {

    $username = 'dlxflwpwr';
    $password = 'dlxflwpwr';
    $servername = 'localhost';
    $table = 'dlxflwpwr';
    
    $conn = new \mysqli($servername, $username, $password, $table);
    
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    }    

    $stmt = $conn->prepare("INSERT INTO user (username, password) VALUES (?, ?)");
    $stmt->bind_param("ss", $_POST['newUsername'], $_POST['newPassword']);

    if (!$stmt->execute()) {        
        if($conn->errno == 1062) {
            echo '<script> alert("Användaren finns redan, välj ett annat användarnamn")</script>';
        }
    }
    $conn->close();
}
else {
    echo '<script> alert("Välj både användarnamn och lösenord")</script>';
}

include 'page.php';