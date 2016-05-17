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
    
    $sql = "SELECT username FROM user WHERE username != 'a'";
    $result = $conn->query($sql);
    $conn->close();
    echo '<div id="anvandarDiv">';
    echo '<h3> Användare: </h3>';
    if ($result->num_rows > 0) {
        while($row = $result->fetch_assoc()) {
            echo("<form action='deleteUser.php' method='post'>");
            echo $row['username'];
            echo("<input type='hidden' name='deleteUser' value='" . $row['username'] . "'/>");
            echo("<input type='submit' class='commentButton' value='Ta bort användare'/>");
            echo("</form>");
            }
    }
    echo '</div>';
    ?>
<div id="laggTill">
    <h3> Lägg till användare </h3>
    <form action="saveUser.php" method='post'>
        <div><p>Användarnamn:</p>
            <input type="text" name='newUsername' class='text-author'/>   
        </div>
        <div><p>Lösenord:<p/>
            <input type="password" name='newPassword' class='text-author'/>   
        </div>
        <div>
            <input id="loginbutton" type="submit" value="Spara användare"/>
        </div>
    </form>
</div>