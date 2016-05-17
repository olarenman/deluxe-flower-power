<!DOCTYPE html> 
<html>
    <head>
        <title>DlxFlwPwr</title>
        <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>   
        <script type="text/javascript" src="//ajax.googleapis.com/ajax/libs/jquery/1.10.2/jquery.min.js"></script>
        <script type="text/javascript" src="/chart.js"></script>
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
        
        <div id="curve_chart" style="width: 900px; height: 500px"></div>
    
    </body>
</html>
