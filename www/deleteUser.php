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
    
$stmt = $conn->prepare("DELETE FROM user WHERE username = ?");
$stmt->bind_param('s', $_POST['deleteUser']);
$stmt->execute();
$conn->close();

include 'page.php';