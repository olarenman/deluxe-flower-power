        <script type="text/javascript">
            function vattna() {
                $.get("runflower.php");
                return false;
            }
         </script>


<div class="centerdiv" id="centerhigh">
    <div id="centerleft">
        <h1> Aktuell fuktighet i din planta är: </h1>
        <?php include 'fuktighet.php'; ?>
        <h3>Tryck på vattenkannan för att vattna din planta i 5 sekunder</h3>
    </div>
    
    <div id ="vattnadiv">
        <a href="javascript:vattna();"> <img src="../bilder/Vattenkanna.png" alt="Vattna"> </a>
    </div>
    <div id="blomvattna">
        <img src="../bilder/flowerpot.png" alt="Bild på blomma">
    </div>
    

</div>
<div class="centerdiv" id="centerlow">
    <h1> Statistik över jordfuktighet i din planta </h1>    
    <div id="curve_chart"></div>
</div>