<?php
    
    session_start();
    session_destroy();

     header('Location: interfaccia_login.php');
     
?>