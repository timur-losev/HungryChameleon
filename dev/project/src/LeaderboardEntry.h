#pragma once

struct LeaderboardEntry
{
	LeaderboardEntry()
					:name(), score(0), rank(0) {}


	LeaderboardEntry(const std::string _name, int _score, int _rank)
					:name(_name), score(_score), rank(_rank){}

	std::string name;
	int score;
	int rank;
};

typedef std::vector<LeaderboardEntry> LeaderboardEntries_t;