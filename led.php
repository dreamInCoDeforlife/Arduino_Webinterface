<?php

$onoffdata = $_GET["state"];

$textfile = "LED_data.txt";
$fileLocation = "$textfile";
$fh = fopen($fileLocation, 'w') or die("Error opening file!");

$stringToWrite = "$onoffdata";
fwrite($fh,$strongToWrite);

fclose($fh);

header("Location:index.html");
?>