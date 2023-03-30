<?php 

require ("isset.php");

require ("connessione.php");


if($_FILES['fileToUpload']['name'] != ""){
echo $_FILES['fileToUpload']['name'];
$target_dir = "/var/www/vhosts/salvoamato.it/5C2020.salvoamato.it/cucuzza/Borsellino/fotoprod/"; // percorso della cartella corrente sul server, esso deve avere i giusti permessi
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

$prodo = addslashes($_POST['nome']); 
$price = addslashes($_POST['prezzo']);
$disponib = addslashes($_POST['disp']);
$img = $_FILES["fileToUpload"]["name"];

 $query = "UPDATE borsellino_prodotti SET prodotto='".$prodo."',prezzo='".$price."',disponibile='".$disponib."' WHERE id_prodotto=".$_GET['id'];



 }else{
     
 $prodo = addslashes($_POST['nome']); 
$price = addslashes($_POST['prezzo']);
$disponib = addslashes($_POST['disp']);

 $query = "UPDATE borsellino_prodotti SET prodotto='".$prodo."',prezzo='".$price."',disponibile='".$disponib."' WHERE id_prodotto=".$_GET['id'];
}
     
     $link = mysqli_connect($host, $user, $pass, $db);


 
 
$result = mysqli_query($link, $query); 

if(!$result){


echo "inserimento fallito"." ".mysqli_error($link);


}else{ echo "Inserimento riuscito";

header('Location: scelta.php');
}

    

    
  


?>[Enter code here]