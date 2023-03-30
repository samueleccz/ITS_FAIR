<?php

require ("../connessione.php");

session_start();

$link = mysqli_connect($host, $user, $pass, $db);

if (mysqli_connect_errno())
{
  echo "connessione fallita".die(mysqli_connect_errno());   
}

$input= json_decode(file_get_contents('php://input'),true);
$nome = $input['nome'];
$password= md5($input['password']);

$query = "SELECT COUNT(*) as conta FROM borsellino_utenti WHERE nome='".$nome."' AND password='".$password."'";

$result= mysqli_query($link, $query);

  if(!$result){

    echo ("Errorcode: " . mysqli_errno($link));
        mysqli_close($link);
  } 

if(mysqli_num_rows($result)!=0)
    $row = mysqli_fetch_assoc($result);


   if ($row["conta"] == 1){
     
     
     
  $query1 = "SELECT SUM(importo) as Saldo, borsellino_utenti.nome, borsellino_utenti.cognome, borsellino_utenti.foto, borsellino_utenti.password, borsellino_utenti.livello, borsellino_utenti.id_utente FROM `borsellino_transazione`
  INNER JOIN borsellino_utenti ON borsellino_transazione.utente = borsellino_utenti.id_utente
  WHERE nome = '".$nome."' AND password = '".$password."'";
  
  $result1= mysqli_query($link, $query1);

   $row1 = mysqli_fetch_assoc($result1);
  
  echo json_encode($row1);
 
   }else{
       
       http_response_code(404);
       
	    }

?>