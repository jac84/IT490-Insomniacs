<!DOCTYPE html>
<html>

<style>
	body{
	background-color: #d3d3d3
	}
</style>

<head>Insomniacs</head><br><br>

<body>

<?php

require_once('path.inc');
require_once('get_host_info.inc');
require_once('rabbitMQLib.inc');

$username = $_POST['username'];
$password = $_POST['password'];
$firstname = $_POST['firstname'];
$lastname = $_POST['lastname'];

$client = new rabbitMQClient("testRabbitMQ.ini","testServer");
echo "here";

$request = array();
$request['type'] = "register";
$request['username'] = "$username";
$request['password'] = "$password";
$request['firstname'] = "$firstname";
$request['lastname'] = "$lastname";

//$request['message'] = "HI";

$response = $client->send_request($request);
//$response = $client->publish($request);


echo "client received response: ".PHP_EOL;
print_r($response);
echo "\n\n";

echo $argv[0]." END".PHP_EOL;

?>


</body>

</html>

