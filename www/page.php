<!DOCTYPE html> 
<html>
    <head>
        <title>DlxFlwPwr</title>
        <link href="reset.css" rel="stylesheet" type="text/css"/>
        <link href="main.css" rel="stylesheet" type="text/css"/>
        <meta charset="utf-8" />
    </head>

    <body>

        <div id="upper">
            <h3> Inloggad som <?php session_start(); echo $_SESSION['username']; ?> </h3>
        </div>
        <div id="center" >
            <?php 
                session_start();
                if($_SESSION['username'] == 'a') {
                    include 'admin.php';
                }
                else {
                    include 'center.php';
                }
            ?>
        </div>
    
    </body>
</html>