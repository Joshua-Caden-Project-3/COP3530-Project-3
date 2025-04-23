
//
// Created by Joshie Land on 4/20/25.
//

#ifndef COP3530_P3_DATA_H
#define COP3530_P3_DATA_H

#include <string>
#include <vector>
#include <filesystem>
#include <iostream>

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
    bool loadFromDirectory(const std::string& data_path);
    const std::vector<MatchResult>& getAllMatches() const;

    std::vector<MatchResult> getMatchesForTeam(const std::string& team_name) const;
    std::vector<MatchResult> getMatchesForCompetition(const std::string& competition) const;

private:
    std::vector<MatchResult> matches_;
    bool parseJsonFile(const std::string& file_path);
    std::string extractJsonValue(const std::string& json, const std::string& key);
    int extractJsonInt(const std::string& json, const std::string& key);
};





#endif //COP3530_P3_DATA_H
