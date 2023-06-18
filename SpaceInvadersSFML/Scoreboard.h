#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <string>
#include <set>

class Scoreboard
{
public:
	void AddToScoreboard(const std::string& name, int score) { scores.insert({name, score }); }
private:
	struct Score{
		std::string username;
		int score;
	};
	struct SortByLarger{
		bool operator()(const Score& ls, const Score& rs) const
		{
			return ls.score > rs.score;
		}
	};
	std::multiset<Score, SortByLarger> scores;
};

#endif 