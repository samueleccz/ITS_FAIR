<?php 

require ("isset.php");


require ("connessione.php");


    
$link = mysqli_connect($host, $user, $pass, $db); 

if (mysqli_connect_errno())
{
  echo "connessione fallita".die(mysql_connect_errno());
}

$query = "SELECT borsellino_prodotto.* from borsellino_prodotto where id_prodotto != 3 and id_prodotto=".$_GET["id"];
 

$result = mysqli_query($link, $query); // seconda istruzione

// controllo sul numero dei record coinvolti
if (mysqli_num_rows($result)!=0) // verifica se ci sono righe presenti
{
 $row = mysqli_fetch_assoc($result);

 echo" <html lang='en' dir='ltr'>
  <head>
    <meta charset='utf-8'>
    <link rel='stylesheet' href='styles.css'>
        <div class='wrapper'>
    <title> BAR - Modifica Prodotto</title>
        <link rel='stylesheet' href='styles.css'>
    <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css'>
  </head>
  <body>
  <div class='title'> Modifica Prodotto </div>
    <form action='modifica_prod_code.php' method='POST' enctype='multipart/form-data'>

        <div class='field'>
        <input type='text' value='".$row["prodotto"]."' name='nome'>
                       <label> Nome </label>
        </div>
<div class='field'>
        <input type='text' value='" .$row["prezzo"]."' name='prezzo'>
                       <label> Prezzo </label>

        </div>
        <div class='field'>
                <input type='text' value='" .$row["disponibile"]."' name='disp'>
                       <label > Disponibilita' </label>

        </div>
             <br>
        <div class='field'>
          <input type='submit' value='Invia'>
        </div>



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