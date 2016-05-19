<?php


    session_start();

    $username = 'dlxflwpwr';
    $password = 'dlxflwpwr';
    $servername = 'localhost';
    $table = 'dlxflwpwr';
    
    $conn = new \mysqli($servername, $username, $password, $table);
    
    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    } 
    
    $sql = "SELECT username FROM user WHERE username != 'admin'";
    $result = $conn->query($sql);
    $conn->close();
    
    if ($result->num_rows > 0) {
        while($row = $result->fetch_assoc()) {
            echo '<div class="hej">';
            echo("<form action='deleteUser.php' method='post'>");
            echo '<p>' . $row['username'] . '</p>';
            echo("<input type='hidden' name='deleteUser' value='" . $row['username'] . "'/>");
            echo("<input type='submit' class='commentButton' value='Ta bort användare'/>");
            echo("</form>");
            echo '</div>';
            }
    }
    else {
        echo '<p>Inga ännu registredare användare</p>';
    }
