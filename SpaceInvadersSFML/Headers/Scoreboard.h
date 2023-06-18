#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <string>
#include <set>
#include <fstream>


struct Score {
	std::string username;
	int score;
};
struct SortByLarger {
	bool operator()(const Score& ls, const Score& rs) const{return ls.score > rs.score;}
};

class Scoreboard
{
public:
	void AddToScoreboard(const std::string& name, int score) { scores.insert({ name, score }); }
	void SaveScoreboard()
	{
		std::ofstream score_file("Data/scoreboard.txt");
		for (auto& score : scores)
			score_file << score.username << " " << score.score <<"\n";
	}
public:
	std::multiset<Score, SortByLarger> scores;
};

#endif 