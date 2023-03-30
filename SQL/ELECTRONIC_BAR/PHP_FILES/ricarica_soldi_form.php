<?php

require("connessione.php");
require("isset.php");

if($_SESSION["livello"] == 1){
    
    $link = mysqli_connect($host, $user, $pass, $db); 

if (mysqli_connect_errno())
{
  echo "connessione fallita".die(mysql_connect_errno());
}


$query = "SELECT borsellino_utenti.* FROM borsellino_utenti WHERE id_utente=".$_GET["id"];

 $result= mysqli_query($link, $query);

$row = mysqli_fetch_assoc($result);

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
  <div class='title'> Menu' Transazione </div>
    <form action='ricarica_soldi_code.php' method='GET' enctype='multipart/form-data'>
         <div class='field'>
          <input type='text' name='soldi' required>
          <label> Inserisci Soldi </label>
        </div>
        
        <input type='text' value='".$row['id_utente']."' name='id' hidden>
        
<div class='field'>
          <input type='submit' value='RICARICA'>
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