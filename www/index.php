<!DOCTYPE html>

<?php 
session_start();
session_destroy();
?>

<html>
    <head>
            <title>DlxFlwPwr</title>
            <link href="reset.css" rel="stylesheet" type="text/css"/>
            <link href="main.css" rel="stylesheet" type="text/css"/>
            <meta charset="utf-8" />
    </head>
    <body>
        <div id="loginBig">
            <div id ="logintop">
                <div id="flowerpot" >
                    <img src="../bilder/flowerpot.png" alt="Bild på blomma i kruka">
                </div>
                <h1>DlxFlwPwr System </h1> <br>
            </div>
            <div id="loginDiv">
                <div id="login">
                    <h1> Var vänlig logga in </h1>
                    <form action="login.php" method='post'>
                
                        <div class="logfeild"><p>Användarnamn:</p>
                            <input type="text" name='username' class='text-author'/>   
                        </div>
                        <div class="logfeild"><p>Lösenord:<p/>
                            <input type="password" name='password' class='text-author'/>   
                        </div>
                        <div class="logfeild">
                            <input id="loginbutton" type="submit" value="Logga in"/>
                        </div>
                    </form>
                </div>
            </div>
        </div>
    </body>
</html>