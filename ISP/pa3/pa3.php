<?php 
  session_start();
?>
<!DOCTYPE html>
<html>
<head>

  <title>Kyle Lugo pa3</title>

  <link rel="stylesheet" href="styles.css"> 
  <style>

  </style>

</head>
<body>

  <?php 
    $currentValue = 0.0;
    
    if (isset($_SESSION['currentValue'])) {
      $currentValue = $_SESSION['currentValue'];
    }

    if($_POST) {
      $newValue = $_POST["newValue"];
      
      if(isset($_POST['plus'])) {
        $currentValue += $newValue;
        $_SESSION['currentValue'] = $currentValue;
      } 
      elseif(isset($_POST['minus'])) {
        $currentValue -= $newValue;
        $_SESSION['currentValue'] = $currentValue;
      } 
      elseif(isset($_POST['multiply'])) {
        $currentValue *= $newValue;
        $_SESSION['currentValue'] = $currentValue;
      } 
      elseif(isset($_POST['divide'])) {
        $currentValue /= $newValue;
        $_SESSION['currentValue'] = $currentValue;
      } 
      else { // equal
        $currentValue = $newValue;
        $_SESSION['currentValue'] = $currentValue;
      }
    }
  ?>

  <form method="post" action="<?php echo $_SERVER['PHP_SELF'];?>">
    <table>
      <caption> A Calculator </caption>
      <tr>
        <td> <?php print ("$currentValue") ?> </td>
      </tr>
      <tr>
        <td> <input type="submit" name="plus" value="+"> </td>
        <td> <input type="submit" name="minus" value="-"> </td>
      </tr>
      <tr>
        <td> <input type="submit" name="multiply" value="*"> </td>
        <td> <input type="submit" name="divide" value="/"> </td>
      </tr>
      <tr>
        <td> <input type="text" name="newValue"> </td>
        <td> <input type="submit" name="equal" value="="> </td>
      </tr>
    </table>
  </form>

</body>
</html>