<?php

require("connessione.php");
require("isset.php");

if($_SESSION["livello"] == 2){
    
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
    <form action='transazione_bar_code.php' method='POST' enctype='multipart/form-data'>
         <div class='field'>
          <input type='text' name='soldi' required>
          <label> Inserisci Soldi </label>
        </div>
            <div class='field'>
                       <select  class='custom-select custom-select-lg mb-3' name='prodotto'> ";
    
           
          $sql1 = "SELECT prodotto, id_prodotto FROM borsellino_prodotto ORDER BY prodotto ASC";

            
               $link1 = mysqli_connect($host, $user, $pass, $db);
           $result1 = mysqli_query($link1,$sql1);


               if($result1->num_rows > 0)
                 {
                      while ($row1 = $result1->fetch_assoc())
                       {
                         
                         echo "<option value='".$row1['id_prodotto']."' >" . $row1['prodotto'] . "</option>";
                   
                       }
                                   }
       
       echo " </select></div>
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