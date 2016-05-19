<?php 
      //open connection to mysql db

        $username = 'dlxflwpwr';
        $password = 'dlxflwpwr';
        $servername = 'localhost';
        $table = 'dlxflwpwr';
        
        $conn = new \mysqli($servername, $username, $password, $table);

      $sql = "SELECT * FROM (SELECT time, data FROM data ORDER BY time DESC LIMIT 20) AS x ORDER BY time";
      $result = $conn->query($sql);

      $temparray = array();
      while($row = $result->fetch_assoc())
      {
	$temparray[] = $row;
	}
      echo json_encode($temparray);
?>