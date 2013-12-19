<?php
require_once("../leaderboard.php");

// 127.0.0.1/post.php?id=1111&display_name=gregoriy&score=2

function Validate($a)
{
	if( !isset($a["id"]) || 
		!isset($a["display_name"]) ||
		!isset($a["score"]) 
		)
	{
		return false;
	}
	return true;
}

function Post($a)
{
	$lb = new LeaderBoard();
	$lb->Post($a["id"], $a["display_name"], $a["score"], "", "");
	$result = $lb->GetTop(10);
	
	$json = json_encode($result);
	echo $json;
}

$lb = new LeaderBoard();
$col = new Columns();

if(Validate($_GET))
{
	Post($_GET);
}
else
{
	echo 400;
}
?>