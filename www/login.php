<?php


session_start();

if (!empty($_POST['username']) and !empty($_POST['password'])) {
    
    $username = 'dlxflwpwr';
    $password = 'dlxflwpwr';
    $servername = 'localhost';
    $table = 'dlxflwpwr';

    $conn = new \mysqli($servername, $username, $password, $table);

    if ($conn->connect_error) {
        die("Connection failed: " . $conn->connect_error);
    } 

    $sql = "SELECT username, password FROM user";
    $result = $conn->query($sql);

    
    if ($result->num_rows > 0) {
        while($row = $result->fetch_assoc()) {
            if($row['username'] == $_POST['username'] and $row['password'] == $_POST['password']) {
                $_SESSION['username'] = $_POST['username'];
                break;
            }
        }
    }
    $conn->close();
   }
   
if (isset($_SESSION['username'])) {
    include 'page.php';
}
else {
include 'index.php';

}
