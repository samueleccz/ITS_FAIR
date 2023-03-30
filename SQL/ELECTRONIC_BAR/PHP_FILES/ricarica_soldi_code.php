<?php

require ("isset.php");
require ("connessione.php");
  
  
  $link = mysqli_connect($host, $user, $pass, $db); 


$soldi = $_GET['soldi'];
$operatore = $_SESSION['id'];


$utente = $_GET['id'];

 
  $query1 = "INSERT INTO `borsellino_transazione` (`tipologia`, `data_ora`, `importo`, `utente`, `operatore`, `prod`, `id_transazione`) VALUES ('0', CURRENT_TIMESTAMP, '$soldi', '$utente', '$operatore', '3', NULL);";




echo $soldi;
echo $utente;
echo $operatore;
 

$result= mysqli_query($link, $query1);

if(!$result){

echo $query;

}else { echo "Inserimento riuscito";
header('Location: scelta.php');
}



echo $result." ";

?>
