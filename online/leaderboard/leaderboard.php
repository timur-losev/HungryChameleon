<?php

class Columns
{
	public $id = "id";
	public $name = "display_name";
	public $score = "score";
	public $rank = "rank";
	public $save = "best_save";
	public $activity = "last_activity";
	public $other = "other";
};

class LeaderBoard
{
	public $server = "mysql.hostinger.ru";
	public $username = "u593266246_cmlb1";
	public $password = "ThyVK9uNErRTwFHF";
	public $database = "u593266246_cmlb1";
	public $table = "chameleon_leaders";

	public $link;
	function __construct()
	{
		$this->link = mysqli_init();
		$this->link->real_connect($this->server, $this->username, $this->password, $this->database);
	}

	function __destruct()
	{
		$this->link->close();
	}

	public function post($id, $name, $score, $best_save, $other)
	{
		$c = new Columns();
		$db = $this->link;
		$resp = $db->query("(SELECT $c->rank FROM $this->table WHERE $c->score>$score ORDER BY $c->score ASC LIMIT 1)")->fetch_all();
		if(count($resp))
			$myRank = 1+$resp[0][0];
		else
			$myRank = 1;
		$insert = "INSERT INTO $this->table ($c->id, $c->name, $c->score, $c->save, $c->other, $c->rank) VALUES ('$id', '$name', $score, '$best_save', '$other', $myRank)";
		$update = "UPDATE $this->table SET $c->name='$name', $c->score=$score, $c->save='$best_save', $c->other='$other', $c->rank=$myRank WHERE $c->id LIKE '$id'";


		$updateRank = "UPDATE $this->table SET $c->rank=$c->rank+1 WHERE $c->score<$score";
		//echo $update;
		if($this->HasMe($id))
			$query = $update;
		else
			$query = $insert;

		//$db->begin_transaction();
		$db->query($query);
		//$db->query($updateRank);
		//$db->commit();

	}
	public function GetTop($size)
	{
		$c = new Columns();
		$request = "SELECT $c->id, $c->name, $c->score, $c->rank FROM $this->table ORDER BY $c->score DESC";
		$response = $this->link->query($request);
		while ($myrow = $response->fetch_array(MYSQLI_ASSOC))
		{
		  $result[]=$myrow;
		}
		return $result;
	}
	public function HasMe($id)
	{
		$c = new Columns();
		$request = "SELECT COUNT($c->id) FROM $this->table WHERE $c->id LIKE '$id'";
		$response = $this->link->query($request)->fetch_all();
		return $response[0][0] == "1";
	}
};
?>