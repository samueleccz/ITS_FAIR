<?php

require ("connessione.php");

session_start();

$link = mysqli_connect($host, $user, $pass, $db);

if (mysqli_connect_errno())
{
  echo "connessione fallita".die(mysqli_connect_errno());   
}

$password=md5($_GET["password"]);

$query = "SELECT COUNT(*) AS conta, livello, id_utente FROM borsellino_utenti WHERE nome = '".$_GET["username"]."' AND password = '".$password."'";


$result= mysqli_query($link, $query);

  if(!$result){

    echo ("Errorcode: " . mysqli_errno($link));
        mysqli_close($link);
  } 

if(mysqli_num_rows($result)!=0)
    $row = mysqli_fetch_assoc($result);

   if ($row["conta"] == 1){
  
       $_SESSION["nome"] = $_GET["username"];
       $_SESSION["livello"] = $row["livello"];
       $_SESSION["id"] = $row["id_utente"];
       $_SESSION["log"]=TRUE;
     header('Location:scelta.php');
 
   }else{
	   echo "<meta name='viewport' content='width=device-width, initial-scale=1'>";
       
       echo "<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css'>";

       echo "<p class='col-md-12'> Utente non autorizzato. Torna Alla Pagina Di <a href='interfaccia_login.php'> Login </a></p>";  }

?>