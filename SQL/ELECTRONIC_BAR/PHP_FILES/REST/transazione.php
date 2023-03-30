<?php 

require ("../connessione.php");

session_start();

$link = mysqli_connect($host, $user, $pass, $db);

if (mysqli_connect_errno())
{
  echo "connessione fallita".die(mysqli_connect_errno());   
}

$input= json_decode(file_get_contents('php://input'),true);
$utente = $input['utente'];
$prodotto = $input['prodotto'];
$prezzo = $input['prezzo'];
//$operatore = $input['operatore'];

$query="INSERT INTO `borsellino_transazione` (`tipologia`, `data_ora`, `importo`, `utente`, `operatore`, `prod`, `id_transazione`) VALUES ('1', CURRENT_TIMESTAMP, '$prezzo', '$utente', '24', '$prodotto' , NULL);";

$result= mysqli_query($link, $query);

echo $query;

?>