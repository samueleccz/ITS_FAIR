<?php 

require ("isset.php");


require ("connessione.php");

if($_SESSION["livello"] == 1){
    
$link = mysqli_connect($host, $user, $pass, $db); 

if (mysqli_connect_errno())
{
  echo "connessione fallita".die(mysql_connect_errno());
}

$query = "SELECT borsellino_utenti.* FROM borsellino_utenti WHERE id_utente=".$_GET["id"];
 

$result = mysqli_query($link, $query); // seconda istruzione

// controllo sul numero dei record coinvolti
if (mysqli_num_rows($result)!=0) // verifica se ci sono righe presenti
{
 $row = mysqli_fetch_assoc($result);

 echo" <html lang='en' dir='ltr'>
  <head>
    <meta charset='utf-8'>
    <link rel='stylesheet' href='styles.css'>
        <div class='wrapper'>
    <title> BAR - Modifica Profilo ". $row['nome'] ."</title>
        <link rel='stylesheet' href='styles.css'>
    <link rel='stylesheet' href='https://stackpath.bootstrapcdn.com/bootstrap/4.3.1/css/bootstrap.min.css'>
  </head>
  <body>
  <div class='title'> Modifica Profilo </div>
    <form action='modifica_utente_code.php' method='POST' enctype='multipart/form-data'>

        <div class='field'>
        <input type='text' value='".$row["nome"]."' name='nome'>
                       <label> Nome </label>
        </div>
<div class='field'>
        <input type='text' value='" .$row["cognome"]."' name='cognome'>
                       <label> Cognome </label>

        </div>
        <div class='field'>
                <input type='text' value='" .$row["data_nascita"]."' name='data'>
                       <label > Data di Nascita </label>

        </div>
    <div class='field'>
            <input type='text' value='" .$row["classe"]."' name='classe'>
                       <label> Classe </label>

   </div>
       <div class='field'>
            <input type='text' value='" .$row["telefono"]."' name='telefono'>
                       <label> Numero di Telefono </label>

   </div>

    <div class='field'>
            <input type='text' value=' " .$row["email"]."' name='email'>
                       <label> E-mail </label>
   </div>
<br>
     <input type='text' value=' " .$row["id_utente"]."' name='idut' hidden>
           <div class='custom-file'>
                <input type='file' class='file-input' name='fileToUpload' id='fileToUpload'>
               </div>
             <br>
        <div class='field'>
          <input type='submit' value='Invia'>
        </div>



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

} 



?>