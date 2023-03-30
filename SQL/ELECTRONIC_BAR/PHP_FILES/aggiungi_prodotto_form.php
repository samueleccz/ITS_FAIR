<?php

require("connessione.php");
require("isset.php");

if($_SESSION["livello"] == 2){
    
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
  <div class='title'> Aggiungi Prodotto </div>
    <form action='aggiungi_prodotto_code.php' method='POST' enctype='multipart/form-data'>
        <div class='field'>
          <input type='text' name='prodotto' required>
          <label>Prodotto</label>
        </div>
         <div class='field'>
          <input type='text' name='prezzo' required>
          <label> Prezzo</label>
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