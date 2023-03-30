<?php

session_start();

if (!isset($_SESSION['log'])){

	
    die("<meta name='viewport' content='width=device-width, initial-scale=1'> 
    <link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css'>
    <p class='col-md-12'> Devi effettuare il Login. Torna Alla Pagina Di <a href='interfaccia_login.php'>  Login </a></p>"); 
       
                             }

if ($_SESSION['log']==FALSE){ die("Non sei autorizzato");}

?>