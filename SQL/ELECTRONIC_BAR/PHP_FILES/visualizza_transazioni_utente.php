<?php 

require ("isset.php");


require ("connessione.php");


$link = mysqli_connect($host, $user, $pass, $db); 

if (mysqli_connect_errno())
{
  echo "connessione fallita".die(mysql_connect_errno());
}

$query = "SELECT borsellino_transazione.importo, borsellino_utenti.nome, borsellino_utenti.cognome, borsellino_utenti.cognome, borsellino_transazione.data_ora, borsellino_prodotto.prodotto FROM `borsellino_transazione` 
INNER JOIN borsellino_utenti ON borsellino_utenti.id_utente = borsellino_transazione.utente
INNER JOIN borsellino_prodotto ON borsellino_prodotto.id_prodotto = borsellino_transazione.prod
WHERE borsellino_utenti.id_utente =". $_SESSION['id'];

$result = mysqli_query($link, $query); // seconda istruzione


if (mysqli_num_rows($result)!=0)
{

 echo" <html lang='en' dir='ltr'>
  <head>
    <meta charset='utf-8'>
    <link rel='stylesheet' href='styles.css'>
        <div class='wrapper' style='width: 919px'>
    <title> BAR - Transazioni  </title>
  </head>
  <body>
  <div class='title'> Transazioni </div>
    <form>";
    
     while($row = mysqli_fetch_assoc($result))
  {
  
              echo " 
               <div class='field' style='width: 200px; float: right; margin-left: 19px;'>
        <input type='text' value='" .$row["prodotto"]."' readonly>
          <a><label style='transform: translateY(-150%); background-color : white' >Utente</label></a>
        </div>
        
              <div class='field' style='width: 200px; float: right; margin-left: 19px;'>
        <input type='text' value='" .$row["data_ora"]."' readonly>
        <a><label style='transform: translateY(-150%); background-color : white' >Data e Ora</label></a>

        </div>
        
        
        
        <div class='field' style='width: 200px; float: right'>
        <input type='text' value='".($row["importo"])."\xE2\x82\xAc' readonly style='border-color :'>
        <a><label style='transform: translateY(-150%); background-color : white' >Importo</label></a>

        </div>
   
        
        <div class='field' style='width: 200px; float: '>
        <input type='text' value='" .$row["nome"]." ".$row["cognome"]."' readonly>
          <a><label style='transform: translateY(-150%); background-color : white' >Utente</label></a>
        </div>
    
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





?>