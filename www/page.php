<!DOCTYPE html> 
<html>
    <head>
        <title>DlxFlwPwr</title>
        <link href="reset.css" rel="stylesheet" type="text/css"/>
        <link href="main.css" rel="stylesheet" type="text/css"/>
        <meta charset="utf-8" />
        <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>   
        <script type="text/javascript" src="//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js"></script>
        <script type="text/javascript" src="/chart.js"></script>
        <script type="text/javascript">
            function vattna() {
                $.get("runflower.php");
                return false;
            }
         </script>

    </head>
    
    

    <body>
    <div id="pageBig">
        <div id="upper">
            
            <div id="flower">
                <img src="../bilder/flowerpot.png" alt="Bild på blomma">
            </div>
            <h1>Välkommen till DlxFlwPwr</h1>
            <div id="inlogged">
                <div>
                <p> Inloggad som: <?php session_start(); echo $_SESSION['username']; ?> </p>
                </div>
                <div>
                    <form action="logout.php">
                        <button id="logoutbutton" type="submit" value="Submit">Logga ut</button>
                    </form>
                </div>


            </div>
        </div>
        <div id="center" >
            <?php 
                session_start();
                if($_SESSION['username'] == 'admin') {
                    include 'admin.php';
                }
                
                include 'center.php';
            ?>
        </div>
    </div>
    </body>
</html>