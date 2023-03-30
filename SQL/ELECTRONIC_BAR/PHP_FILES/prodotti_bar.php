<?php 

require ("isset.php");


require ("connessione.php");


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
    <title> BAR - Transazioni  </title>
  </head>
  <body>
  <div class='title'> Prodotti </div>
    <form>";

    
     while($row = mysqli_fetch_assoc($result)) //CICLE WHILE PRINT DATABASES ITEMS ; CICLO WHILE STAMPA GLI ARTICOLI DEL DATABASE 
  {
  
      if($row["disponibile"]==1)
        $dis = 'si';
      if($row["disponibile"]==0)
      $dis= 'no';
              echo " 
             
              <div class='field' style='width: 200px; float: right; margin-left: 19px;'>";
              
         
        
        echo "<input type='text' value='" . $dis."' readonly>
        <a><label style='transform: translateY(-150%); background-color : white' >Disponibilita'</label></a>

        </div>
        
        <div class='field' style='width: 200px; float: right; margin-left: 19px;'>
        <input type='text' value='".($row["prezzo"])."\xE2\x82\xAc' readonly style='border-color :'></a>
        <a><label style='transform: translateY(-150%); background-color : white' >Prezzo</label></a>


        
        </div>
        <div class='field' style='width: 220px;'>
        <a href='modifica_prodotti.php?id=".$row["id_prodotto"]."'><input type='text' value='" .$row["prodotto"]."' readonly>
          <a><label style='transform: translateY(-150%); background-color : white' >Nome</label></a>
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