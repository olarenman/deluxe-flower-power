<?php

    $username = 'dlxflwpwr';
    $password = 'dlxflwpwr';
    $servername = 'localhost';
    $table = 'dlxflwpwr';

    $conn = new \mysqli($servername, $username, $password, $table);

    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    } 

    $sql = "SELECT data FROM data WHERE id = (SELECT max(id) FROM data)";
    $result = $conn->query($sql);
    $conn->close();
    
    if ($result->num_rows > 0) {
        $row = $result->fetch_assoc();
        echo '<h2>' . $row['data'] . '% </h2>';
    }
    else {
        echo 'Inga värden i databasen';
    }