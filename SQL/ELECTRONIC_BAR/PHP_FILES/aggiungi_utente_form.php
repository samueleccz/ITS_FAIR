<?php

require("connessione.php");
require("isset.php");

if($_SESSION["livello"] == 1){
    
    $link = mysqli_connect($host, $user, $pass, $db); 

if (mysqli_connect_errno())
{
  echo "connessione fallita".die(mysql_connect_errno());
}


echo "

<!DOCTYPE html>

<html lang='en' dir='ltr'>
  <head>
    <meta charset='utf-8'>
    <link rel='stylesheet' href='styles.css'>
    <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css'>

  </head>
  <body>
    <div class='wrapper'>
  <div class='title'> Aggiungi Utente </div>
    <form action='aggiungi_utente_code.php' method='POST' enctype='multipart/form-data'>
        <div class='field'>
          <input type='text' name='username' required>
          <label>Nome utente</label>
        </div>
         <div class='field'>
          <input type='text' name='cognome' required>
          <label>Cognome utente</label>
        </div>
<div class='field'>
          <input type='password' name='password' required>
          <label>Password utente</label>
        </div>
<div class='field'>
          <input type='mail' name='mail' required>
          <label>Mail utente</label>
        </div>
<div class='field'>
        
          <input type='date' name='date' required>
         
        </div>
<div class='field'>
           <input type='number' name='telefono' required>
           <label>Numero di telefono +39</label>
</div>
<br>
<div class='-file'>
               
                <input type='file' class='file-input' id='fileToUpload' name='fileToUpload'>
  
</div>
<br>
<div class='field'>
  <select class='custom-select custom-select-lg mb-3' id='livello' name='livello'>

  <option value='1'>Segreteria</option>
  <option value='2'>Bar</option>
  <option value='3'>Studente</option>
</select>
</div>
<div class='field'>
<input type='text' name='classe' required>
<label>Classe: 5^C ITI</label>

</select>
</div>
<div class='content'>
        
</div>
<div class='field'>
          <input type='submit' value='CREA'>
        </div>
<div class='signup-link'>
<a href='https://www.iiscucuzzaeuclide.edu.it/'> <p style='color:grey'> IIS CUCUZZA-EUCLIDE </p> </a> 
</div>
</form>
</div>
</body>
</html> 

";

}else{echo "utente non autorizzato. <a href='scelta.php'> Clicca  </a> per tornare indietro";}

?>