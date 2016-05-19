<div id="text">
    <p>Du är inloggad som administratör. Här kan du lägga till och ta bort användare i ditt DlxFlwPwr system.</p>
</div>

<div id="users" class="admindiv">
    <h3>Registrerade användare</h3>
    <?php include 'users.php'; ?>
</div>  
<div id="laggTill" class="admindiv">
    <h3> Lägg till ny användare </h3>
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
