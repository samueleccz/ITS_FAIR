<?php

require ("isset.php");

require ("connessione.php");

if($_SESSION["livello"]==2){

$link = mysqli_connect($host, $user, $pass, $db);

if (mysqli_connect_errno())
{
  echo "connessione fallita".die(mysql_connect_errno());
}

//QUERY
$query ="SELECT borsellino_utenti.nome, borsellino_utenti.cognome, borsellino_utenti.classe, borsellino_utenti.livello, borsellino_utenti.id_utente FROM `borsellino_utenti` ORDER BY borsellino_utenti.livello ASC";

$result = mysqli_query($link, $query);


if (mysqli_num_rows($result)!=0) 
{

    

   echo" <html lang='en' dir='ltr'>
  <head>
    <meta charset='utf-8'>
    <link rel='stylesheet' href='styles.css'>
        <div class='wrapper' style='width: 700px'>
    <title> BAR - Transazioni  </title>
  </head>
  <body>
  <div class='title'> Lista utenti </div>
    <form>";
    
     while($row = mysqli_fetch_assoc($result)) //CICLE WHILE PRINT DATABASES ITEMS ; CICLO WHILE STAMPA GLI ARTICOLI DEL DATABASE 
  {
  
       if($row["livello"]==1){
           
           
           $livello = "Segreteria";
           
       }else if($row["livello"]==2) {
           
           $livello = "Bar";
           
           
       }else if($row["livello"]==3) {
           
           $livello = "Utente";
           
           
       }
       
       
       
              echo " 
              <div class='field' style='width: 200px; float: right; margin-left: 19px;'>
        <input type='text' value='" .$livello."' readonly>
        <a><label style='transform: translateY(-150%); background-color : white' >Livello</label></a>

        </div>
        
        <div class='field' style='width: 200px; float: right'>
        <input type='text' value='".($row["classe"])."' readonly style='border-color :'>
        <a><label style='transform: translateY(-150%); background-color : white' >Classe</label></a>


        
        </div>
        <div class='field' style='width: 210px; float:'>
       <a href='transazione_bar_form.php?id=".$row["id_utente"]."'> <input type='text' value='" .$row["nome"]." ".$row["cognome"]."' readonly> </a>
          <a><label style='transform: translateY(-150%); background-color : white' >Utente</label></a>
        </div>
        
        <input type='text' value='" .$row["nome"]. "' name='id' hidden>
   
       
";

  }
  echo"
<div class='signup-link'>
<a href='https://www.iiscucuzzaeuclide.edu.it/'> <p style='color:grey'> IIS CUCUZZA-EUCLIDE </p> </a> 
</div>
<div>
</form>
</body>
</html>";
}




@mysqli_free_result($result);

@mysqli_close($link);
}else{echo "utente non autorizzato. <a href='scelta.php'> Clicca  </a> per tornare indietro";

}




?>