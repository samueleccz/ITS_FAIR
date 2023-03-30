<?php 

require ("isset.php");


require ("connessione.php");


if($_SESSION['livello'] == 2){

$link = mysqli_connect($host, $user, $pass, $db); 

if (mysqli_connect_errno())
{
  echo "connessione fallita".die(mysql_connect_errno());
}

$query = "SELECT borsellino_prodotto.* from borsellino_prodotto where id_prodotto != 3";



$result = mysqli_query($link, $query); // seconda istruzione

// controllo sul numero dei record coinvolti
if (mysqli_num_rows($result)!=0) // verifica se ci sono righe presenti
{

 echo" <html lang='en' dir='ltr'>
  <head>
    <meta charset='utf-8'>
    <link rel='stylesheet' href='styles.css'>
        <div class='wrapper' style='width: 720px'>
    <title> BAR - Lista Prodotti  </title>
  </head>
  <body>
  <div class='title'> Lista Prodotti </div>
    <form>";

    
     while($row = mysqli_fetch_assoc($result)) //CICLE WHILE PRINT DATABASES ITEMS ; CICLO WHILE STAMPA GLI ARTICOLI DEL DATABASE 
  {
  

              echo " 
             
        <div class='field' style='width: 200px; float: right; margin-left: 19px;'>
            <img src='foto/prodotti/".$row['id_prodotto'].".png'>
        <a><label style='transform: translateY(-150%); background-color : white' >Codice QR'</label></a>

        </div>
        
        <div class='field' style='width: 200px; float: right; margin-left: 19px;'>
        <input type='text' value='".($row["prezzo"])."\xE2\x82\xAc' readonly style='border-color :'></a>
        <a><label style='transform: translateY(-150%); background-color : white' >Prezzo</label></a>


        
        </div>
        <div class='field' style='width: 220px;'>
       <input type='text' value='" .$row["prodotto"]."' readonly>
          <a><label style='transform: translateY(-150%); background-color : white' >Prodotto</label></a>
        </div>
     
     
     <br><br>
";

  }
  echo"
<div class='signup-link'>
<a href='https://www.iiscucuzzaeuclide.edu.it/'> <p style='color:grey'> IIS CUCUZZA-EUCLIDE </p> </a> 
</div>
<div>
</form>
</body>
</html>";
}




@mysqli_free_result($result);

@mysqli_close($link);
}else { echo "Utente non autorizzato";}




?>