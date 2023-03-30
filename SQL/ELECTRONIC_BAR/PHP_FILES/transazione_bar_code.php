<?php

require ("isset.php");
require ("connessione.php");
  
  
  $link = mysqli_connect($host, $user, $pass, $db); 


$soldi = ($_POST['soldi']) * (-1);
$operatore = $_SESSION['id'];
$prodotto = $_POST['prodotto'];


$utente = $_POST['id'];

 
  $query1 = "INSERT INTO `borsellino_transazione` (`tipologia`, `data_ora`, `importo`, `utente`, `operatore`, `prod`, `id_transazione`) VALUES ('1', CURRENT_TIMESTAMP, '$soldi', '$utente', '$operatore', '$prodotto' , NULL);";




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
