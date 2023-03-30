<?php

require ("isset.php");
require ("connessione.php");
include('../../../digital.salvoamato.it/phpqrcode/qrlib.php'); 

if($_FILES['fileToUpload']['name'] != ""){
$target_dir = "/var/www/vhosts/salvoamato.it/5C2020.salvoamato.it/cucuzza/Borsellino/foto/"; // percorso della cartella corrente sul server, esso deve avere i giusti permessi
$target_file = $target_dir . basename($_FILES["fileToUpload"]["name"]); //percorso completo del nome del file.
$uploadOk = 1;
$imageFileType = strtolower(pathinfo($target_file,PATHINFO_EXTENSION)); //estrae l'estensione

// verifica se è una vera immagine
if(isset($_POST["invia"])) {
  $check = getimagesize($_FILES["fileToUpload"]["tmp_name"]);
  if($check !== false) {
    echo "E' una immagine - " . $check["mime"] . ".";
    $uploadOk = 1;
  } else {
    echo "non è una immagine.";
    $uploadOk = 0;
  }
}

// Verifica se c'è un file con lo stesso nome sil file system
if (file_exists($target_file)) {
  echo "Il file esiste già con lo stesso nome.";
  $uploadOk = 0;
}

// Check file size
if ($_FILES["fileToUpload"]["size"] > 500000) { //dim max 500 kb.
  echo "Il file è troppo grande.";
  $uploadOk = 0;
}


// Check if $uploadOk is set to 0 by an error
if ($uploadOk == 0) {
  echo "Non è possibile copiare il file.";
// if everything is ok, try to upload file
} else {
  if (move_uploaded_file($_FILES["fileToUpload"]["tmp_name"], $target_file)) {
    echo " file ". htmlspecialchars( basename( $_FILES["fileToUpload"]["name"])). " copiato.";
  } else {
    echo "File non copiato";
  }
}
    
    $link = mysqli_connect($host, $user, $pass, $db);

$Nome = addslashes($_POST['username']); 
$Cognome = addslashes($_POST['cognome']);
$password = md5($_POST['password']);
$email = $_POST['mail'];
$Data = $_POST['date'];
$telefono = $_POST['telefono'];
$Classe = $_POST['classe'];
$livello = $_POST['livello'];
$img = $_FILES["fileToUpload"]["name"];

   //  $query = "INSERT INTO borsellino_utenti (nome, cognome, data_nascita, telefono, email, livello, classe, foto, password) VALUES ('$Nome', '$Cognome', '$Data', '$telefono', '$email', '$livello', '$Classe', '$immagine' '$password')";

$query= "INSERT INTO `borsellino_utenti` (`nome`, `cognome`, `data_nascita`, `telefono`, `email`, `livello`, `classe`, `foto`, `password`, `id_utente`) VALUES ('$Nome', '$Cognome', '$Data', '$telefono', '$email', '$livello', '$Classe', '$img', '$password', NULL)";
//"INSERT INTO `borsellino_utenti`(`nome`, `cognome`, `data_nascita`, `telefono`, `email`, `livello`, `classe`, `foto`, `password`,) VALUES ($Nome, $Cognome, $Data, $telefono, $email, $livello, $Classe, $immagine, $password)";

 }else{
     
     $Nome = addslashes($_POST['username']); 
     $Cognome = addslashes($_POST['cognome']);
     $password = md5($_POST['password']);
     $email = $_POST['mail'];
     $Data = $_POST['date'];
     $telefono = $_POST['telefono']; 
     $Classe = $_POST['classe'];
     $livello = $_POST['livello'];
     $immagine='';
$query= "INSERT INTO `borsellino_utenti` (`nome`, `cognome`, `data_nascita`, `telefono`, `email`, `livello`, `classe`, `foto`, `password`, `id_utente`) VALUES ('$Nome', '$Cognome', '$Data', '$telefono', '$email', '$livello', '$Classe', '$immagine', '$password', NULL)";

     
 }
     
     $link = mysqli_connect($host, $user, $pass, $db);



$result = mysqli_query($link, $query);

echo $result; 
                        
$query1 = "SELECT max(id_utente) AS chiave FROM borsellino_utenti";
$result1 = mysqli_query($link, $query1);
$row1 = mysqli_fetch_assoc($result1);
$codice = $row1["chiave"];

echo $codice;


	$pngAbsoluteFilePath = "/var/www/vhosts/salvoamato.it/5C2020.salvoamato.it/cucuzza/Borsellino/foto/".$codice.".png"; 
    $urlRelativeFilePath = 'http://5c2020.salvoamato.it/cucuzza/Borsellino/foto/'.$codice.'.png'; 
   echo $urlRelativeFilePath;  
    // generating 
	//QRcode::png($codice, $pngAbsoluteFilePath); 
    if (!file_exists($pngAbsoluteFilePath)) { 
		  
        QRcode::png($codice, $pngAbsoluteFilePath); 
       
    } else { 
        echo 'il file esiste già!'; 
    //    echo '<hr />'; 
    } 


if(!$result){

echo $query;
//header('Location: scelta.php');

//echo "inserimento fallito"." ".mysqli_error($link);


}else { echo "Inserimento riuscito";
header('Location: scelta.php');}



echo $result." ";

?>
