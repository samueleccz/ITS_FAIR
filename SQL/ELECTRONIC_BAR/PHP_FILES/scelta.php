<?php

require("connessione.php");
require("isset.php");



if($_SESSION["livello"] == 1){
    
   echo" <html lang='en' dir='ltr'>
  <head>
    <meta charset='utf-8'>
    <link rel='stylesheet' href='styles.css'>
    <title> BAR - Scelta Operazioni </title>
  </head>
  <body>
    <div class='wrapper'>
  <div class='title'> Portale Segreteria </div>
    <form>
        <div class='field'>
          <a href='aggiungi_utente_form.php'><input type='button' value='Aggiungi Utente' required style='color : black; text-align : left; border-color : black'></a>
        </div>
<div class='field'>
          <a href='elenco_utenti.php'><input type='button' value='Modifica Utente' required style='color : black; text-align : left; border-color : black'></a>
        </div>
        <div class='field'>
          <a href='mio_profilo.php'><input type='button' value='Il Mio Profilo' required style='color : black; text-align : left; border-color : black'></a>
        </div>
    <div class='field'>
          <a href='elenco_utenti_ricarica.php'><input type='button' value='Ricarica Soldi' required style='color : black; text-align : left; border-color : black'></a>
    </div>
    <div class='field'>
      <a href='distruggises.php'><input type='button' value='Esci dal Profilo' required style='color : red; text-align : left; border-color : red'></a>
   </div>

<div class='signup-link'>
<a href='https://www.iiscucuzzaeuclide.edu.it/'> <p style='color:grey'> IIS CUCUZZA-EUCLIDE </p> </a> 
</div>
</form>
</div>
</body>
</html>";
}

if($_SESSION["livello"] == 2){
    
   echo" <html lang='en' dir='ltr'>
  <head>
    <meta charset='utf-8'>
    <link rel='stylesheet' href='styles.css'>
        <title> BAR - Scelta Operazioni </title>
  </head>
  <body>
    <div class='wrapper'>
  <div class='title'> Portale Bar </div>
    <form>
<div class='field'>
          <a href='visualizza_transazioni_full.php'><input type='button' value='Visualizza Transazioni' required style='color : black; text-align : left; border-color : black'></a>
        </div>
        <div class='field'>
          <a href='mio_profilo.php'><input type='button' value='Il Mio Profilo' required style='color : black; text-align : left; border-color : black'></a>
        </div>
            <div class='field'>
          <a href='elenco_utenti_transazione.php'><input type='button' value='Menu Transazioni' required style='color : black; text-align : left; border-color : black'></a>
    </div>
     <div class='field'>
          <a href='elenco_prodotti_tablet.php'><input type='button' value='Prodotti' required style='color : black; text-align : left; border-color : black'></a>
    </div>
         <div class='field'>
          <a href='aggiungi_prodotto_form.php'><input type='button' value='Aggiungi Prodotti' required style='color : black; text-align : left; border-color : black'></a>
    </div>
            <div class='field'>
      <a href='distruggises.php'><input type='button' value='Esci dal Profilo' required style='color : red; text-align : left; border-color : red'></a>
   </div>

<div class='signup-link'>
<a href='https://www.iiscucuzzaeuclide.edu.it/'> <p style='color:grey'> IIS CUCUZZA-EUCLIDE </p> </a> 
</div>
</form>
</div>
</body>
</html>";
}

if($_SESSION["livello"] == 3){
    
   echo" <html lang='en' dir='ltr'>
  <head>
    <meta charset='utf-8'>
    <link rel='stylesheet' href='styles.css'>
        <title> BAR - Scelta Operazioni </title>
  </head>
  <body>
    <div class='wrapper'>
  <div class='title'> Portale Utente </div>
    <form>
<div class='field'>
          <a href='visualizza_transazioni_utente.php'><input type='button' value='Visualizza Transazioni' required style='color : black; text-align : left; border-color : black'></a>
        </div>
        <div class='field'>
          <a href='mio_profilo.php'><input type='button' value='Il Mio Profilo' required style='color : black; text-align : left; border-color : black'></a>
        </div>
            <div class='field'>
      <a href='distruggises.php'><input type='button' value='Esci dal Profilo' required style='color : red; text-align : left; border-color : red'></a>
   </div>

<div class='signup-link'>
<a href='https://www.iiscucuzzaeuclide.edu.it/'> <p style='color:grey'> IIS CUCUZZA-EUCLIDE </p> </a> 
</div>
</form>
</div>
</body>
</html>";
}



?>