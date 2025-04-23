#ifndef COP3530_P3_DATA_H
#define COP3530_P3_DATA_H

#include <string>
#include <vector>
#include <filesystem>
#include <json.hpp>

struct MatchResult {
    std::string competition;
    std::string home_team;
    std::string away_team;
    int home_score;
    int away_score;
    std::string date;
};

class FootballData {
public:
    static std::vector<MatchResult> parseJsonFile(const std::string& file_path);
    static std::vector<MatchResult> loadAllMatches(const std::string& directory_path);
};

#endif // COP3530_P3_DATA_H