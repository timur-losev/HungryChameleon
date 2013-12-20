<?php
require_once("../leaderboard.php");

if(isset($_GET["id"]))
{
	$lb = new LeaderBoard();
	$result = $lb->GetMe($_GET["id"]);
	if($result)
	{
		$json = json_encode($result);
		echo $json;
	}
	else
	{
		// Does not exist
		echo 0;
	}
}
else 
{
	// No parameters
	echo 0;
}
?>