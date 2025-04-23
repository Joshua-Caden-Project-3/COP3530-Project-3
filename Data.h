
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

    static MatchResult parseJsonFile(const std::string& file_path);
    static std::string extractJsonValue(const std::string& json, const std::string& key);
    static int extractJsonInt(const std::string& json, const std::string& key);


};





#endif //COP3530_P3_DATA_H
