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
        <div id="loginDiv">
            <h1> Logga in på DlxFlwPwr System </h1> <br>
        
            <div id="login">
                <form action="login.php" method='post'>
                
                    <div><p>Användarnamn:</p>
                        <input type="text" name='username' class='text-author'/>   
                    </div>
                    <div><p>Lösenord:<p/>
                        <input type="password" name='password' class='text-author'/>   
                    </div>
                    <div>
                        <input id="loginbutton" type="submit" value="Logga in"/>
                    </div>
                </form>
            </div>
        </div>
    </body>
</html>