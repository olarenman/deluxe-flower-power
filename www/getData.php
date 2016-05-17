<?php 

      //open connection to mysql db
      $connection = mysqli_connect("localhost","dlxflwpwr","dlxflwpwr","data")
      or die("Error " . mysqli_error($connection));

      $sql = "SELECT * FROM (SELECT time, data FROM data ORDER BY time DESC LIMIT 20) AS x ORDER BY time";

      $result = mysqli_query($connection, $sql)
      or die("Error in Selecting " . mysqli_error($connection));

      $temparray = array();

      while($row = mysqli_fetch_assoc($result))
      {
	$temparray[] = $row;
	}

      echo json_encode($temparray);

?>
