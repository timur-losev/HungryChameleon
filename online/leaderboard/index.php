<?php
require_once("leaderboard.php");

$lb = new LeaderBoard();

$result = $lb->GetTop(10);

$json = json_encode($result);
echo $json;

?>