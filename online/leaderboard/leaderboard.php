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
		$insert = "INSERT INTO $this->table ($c->id, $c->name, $c->score, $c->save, $c->other) VALUES ('$id', '$name', $score, '$best_save', '$other')";
		$update = "UPDATE $this->table SET $c->name='$name', $c->score=$score, $c->save='$best_save', $c->other='$other' WHERE $c->id LIKE '$id'";
		
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
		$request = "SELECT $c->id, $c->name, $c->score FROM $this->table ORDER BY $c->score DESC LIMIt $size";
		$response = $this->link->query($request);
		$i = 1;
		while ($myrow = $response->fetch_assoc())
		{
		  $myrow["rank"] = "$i";
		  $i++;
		  $result[]=$myrow;
		}
		return $result;
	}
	public function HasMe($id)
	{
		$c = new Columns();
		$request = "SELECT COUNT($c->id) FROM $this->table WHERE $c->id LIKE '$id'";
		$response = $this->link->query($request)->fetch_array();
		return $response[0][0] == "1";
	}
	public function GetMe($id)
	{
		if($this->HasMe($id))
		{
			$c = new Columns();
			$rankQuery = "";		
			$rankQuery = $rankQuery."SELECT `my`.*, 1+COUNT(`b`.`$c->id`) AS `$c->rank`";
			$rankQuery = $rankQuery."FROM `$this->table` AS `b` JOIN `$this->table` AS `my`";
			$rankQuery = $rankQuery."ON(`b`.`$c->score`>`my`.`$c->score` OR (`b`.`$c->score`=`my`.`$c->score` AND `b`.`$c->id`<`my`.`$c->id`))";
			$rankQuery = $rankQuery."WHERE `my`.`$c->id`='$id'";
			$response = $this->link->query($rankQuery);
			return $response->fetch_assoc();
		}
		return null;
	}

};
?>