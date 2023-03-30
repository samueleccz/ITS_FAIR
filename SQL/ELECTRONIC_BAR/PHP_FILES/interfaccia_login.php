<?php ?>


<!DOCTYPE html>

<html lang="en" dir="ltr">
  <head>
    <meta charset="utf-8">
    <link rel="stylesheet" href="styles.css">
    <title> BAR - Login </title>
  </head>
  <body>
    <div class="wrapper">
  <div class="title"> Login </div>
    <form action="login.php" method="GET">
        <div class="field">
          <input type="text" name="username" required>
          <label>Username</label>
        </div>
<div class="field">
          <input type="password" name="password" required>
          <label>Password</label>
        </div>
<div class="content">
          <div class="checkbox">
            <input type="checkbox" id="remember-me">
            <label for="remember-me" style="font-size:15px; color:grey"> Ricordami </label>
          </div>
</div>
<div class="field">
          <input type="submit" value="Login">
        </div>
<div class="signup-link">
<a href='https://www.iiscucuzzaeuclide.edu.it/'> <p style="color:grey"> IIS CUCUZZA-EUCLIDE </p> </a> 
</div>
</form>
</div>
</body>
</html>
