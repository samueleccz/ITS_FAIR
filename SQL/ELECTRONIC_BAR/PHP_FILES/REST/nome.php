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

$query = "SELECT COUNT(*) as conta FROM borsellino_utenti WHERE id_utente ='".$utente."'";

$result= mysqli_query($link, $query);

    $row = mysqli_fetch_assoc($result);

   if ($row["conta"] == 1){


$query1="SELECT borsellino_utenti.nome, borsellino_utenti.cognome FROM borsellino_utenti WHERE id_utente ='".$utente."'";

$result1= mysqli_query($link, $query1);


 $row1 = mysqli_fetch_assoc($result1);
  
  echo json_encode($row1);
  
   }else{echo "Errore";}
  
?>