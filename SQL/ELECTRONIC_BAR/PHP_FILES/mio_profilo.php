<?php 

require ("isset.php");


require ("connessione.php");


$link = mysqli_connect($host, $user, $pass, $db); 

if (mysqli_connect_errno())
{
  echo "connessione fallita".die(mysql_connect_errno());
}

$query = "SELECT borsellino_utenti.* FROM borsellino_utenti WHERE id_utente=".$_SESSION["id"];
 
$query1 = "SELECT SUM(importo) as Saldo , borsellino_transazione.utente FROM `borsellino_transazione` WHERE utente =".$_SESSION["id"] ;

$result = mysqli_query($link, $query); // seconda istruzione
$result1 = mysqli_query($link, $query1); // seconda istruzione

// controllo sul numero dei record coinvolti
if (mysqli_num_rows($result)!=0) // verifica se ci sono righe presenti
{
 $row = mysqli_fetch_assoc($result);
 $row1 = mysqli_fetch_assoc($result1);

 echo" <html lang='en' dir='ltr'>
  <head>
    <meta charset='utf-8'>
    <link rel='stylesheet' href='styles.css'>
        <div class='wrapper'>
    <title> BAR - Il Mio Profilo </title>
  </head>
  <body>
  <div class='title'> Il Mio Profilo </div>
    <form>
              
                 
       
                 <div>

        <img src='foto/".$row["foto"]."' width='150' height='200' style='border-radius: 50%;'> "; 
       
          echo "<img src='foto/".$_SESSION['id'].".png' width='150' height='200'>";
            
     
        echo "
        </div>
        
         <div class='field'>
        <input type='text' value='Nome : " .$row["nome"]."' readonly>

        </div>
<div class='field'>
        <input type='text' value='Cognome : " .$row["cognome"]."' readonly>

        </div>
        <div class='field'>
                <input type='text' value='Data di Nascita : " .$row["data_nascita"]."' readonly>

        </div>
    <div class='field'>
            <input type='text' value='Classe : " .$row["classe"]."' readonly>

   </div>
       <div class='field'>
            <input type='text' value='Telefono : " .$row["telefono"]."' readonly>

   </div>

    <div class='field'>
            <input type='text' value='E-mail : " .$row["email"]."' readonly>

   </div>

    <div class='field'>
            <input type='text' value='Soldi : " .$row1["Saldo"]."' readonly>

   </div>


<div class='signup-link'>
<a href='https://www.iiscucuzzaeuclide.edu.it/'> <p style='color:grey'> IIS CUCUZZA-EUCLIDE </p> </a> 
</div>
<div>
        </div>

</form>
</body>
</html>";
}



@mysqli_free_result($result);

@mysqli_close($link);





?>