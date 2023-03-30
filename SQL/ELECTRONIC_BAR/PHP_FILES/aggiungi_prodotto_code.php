<?php

require ("isset.php");
require ("connessione.php");
include('../../../digital.salvoamato.it/phpqrcode/qrlib.php'); 

 $prodotto = $_POST['prodotto'];
 $prezzo = $_POST['prezzo'];

$query= "INSERT INTO borsellino_prodotto (prodotto, prezzo, disponibile) VALUES ('$prodotto','$prezzo',1)";
  
  $link = mysqli_connect($host, $user, $pass, $db);

$result = mysqli_query($link, $query);

         
$query1 = "SELECT max(id_prodotto) AS chiave FROM borsellino_prodotto";
$result1 = mysqli_query($link, $query1);
$row1 = mysqli_fetch_assoc($result1);

$codice = $row1["chiave"];

echo $codice;

	$pngAbsoluteFilePath = "/var/www/vhosts/salvoamato.it/5C2020.salvoamato.it/cucuzza/Borsellino/foto/prodotti/".$codice.".png"; 
    $urlRelativeFilePath = 'http://5c2020.salvoamato.it/cucuzza/Borsellino/foto/prodotti/'.$codice.'.png'; 
   echo $urlRelativeFilePath;  
    // generating 
	//QRcode::png($codice, $pngAbsoluteFilePath); 
    if (!file_exists($pngAbsoluteFilePath)) { 
		  
        QRcode::png($codice, $pngAbsoluteFilePath); 
       
    } else { 
        echo 'il file esiste già!'; 
    //    echo '<hr />'; 
    } 

header('Location: scelta.php');

?>