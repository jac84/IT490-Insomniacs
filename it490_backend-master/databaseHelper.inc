<?php
require_once('path.inc');
require_once('get_host_info.inc');
require_once('rabbitMQLib.inc');


class DatabaseHelper
{
	private $conn;

// Attempts to connect to the database
// If the database does not exist log the error

	public function connect()
	{
		try
		{
		
			$this->conn = new PDO('mysql:host=localhost;dbname=login', 'root', 'punkrockgirl');
			return true;
		}
		catch(PDOException $e)
		{
			$message =  'Error: ' . $e->getMessage();
			$client = new rabbitMQClient("logRabbitMQ.ini","logServer");			
			$request = array();
			$request['type'] = "log";
			$request['message'] = $message;
			$response = $client->publish($request);
		}
		
		return false;
	}
// Grabs Users firstname/lastname from registered table
	public function getUserInfo($username, $password)
	{
		$stmt = $this->conn->prepare('SELECT firstName, lastName FROM USERS WHERE Username = :un AND password = :pw');
		$stmt->bindParam(':un', $username);
		$stmt->bindParam(':pw', $password);
		$stmt->setFetchMode(PDO::FETCH_ASSOC);
		$stmt->execute();
		
		$result = $stmt->fetch();
		
		//$stmt = $this->conn->prepare('SELECT * from registered where username = :un');
		//$stmt->bindParam(':un', $username);
		//$stmt->setFetchMode(PDO::FETCH_ASSOC);
		//$stmt->execute();

		
		return $result;
	}
	

	public function registerUser($username, $password, $firstname, $lastname, $email)
	{

		$database = mysql_connect ('localhost', 'root', 'password');
		mysql_select_db('login');
		$query = ("SELECT * FROM registered where username = '$username'");
		$t = mysql_query($query);
		if(mysql_num_rows($t) > 0)
		{
			echo "Username already exist";
			return false;
		}
 		else
		{
			
			$this->conn = new PDO('mysql:host=localhost;dbname=login', 'root', 'password');
			$stmt = $this->conn->prepare("INSERT INTO USERS (UserID, Username, Password, firstName, lastName, email) VALUES (NULL, :un, :pw, 1, :fname, :lname, :em)");
			$stmt->bindParam(':un', $username);
			$stmt->bindParam(':pw', $password);
			$stmt->bindParam('fname', $firstname);
			$stmt->bindParam('lname', $lastname);
			$stmt->bindParam(':em', $email);

			return $stmt->execute();
			return true;
		}
	}
	
	public function sessionId($username)
	{
		$this->conn = new PDO('mysql:host=localhost;dbname=login', 'root', 'password');
		$stmt->$this->conn->prepare("INSERT INTO SESSION (sessionId, UserID, timestamp) VALUES (NULL, :un, localtime()");
		$stmt->bindParam(':un', $username);
		
		$stmt->execute(); 
		// return true; 
	}
	public function __destruct()
	{
		$this->conn = null;
	}
}

?>
