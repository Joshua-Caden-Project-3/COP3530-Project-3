#include "Data.h"
#include <fstream>
#include <iostream>
#include <json.hpp>

namespace fs = std::filesystem;
using json = nlohmann::json;

std::vector<MatchResult> FootballData::parseJsonFile(const std::string& file_path) {
    std::vector<MatchResult> matches;
    std::ifstream file(file_path);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_path << std::endl;
        return matches;
    }

    try {
        json data;
        file >> data;

        if (data.is_array()) {
            for (const auto& match_data : data) {
                MatchResult match;
                match.competition = match_data.value("competition_name", "");
                match.home_team = match_data["home_team"].value("home_team_name", "");
                match.away_team = match_data["away_team"].value("away_team_name", "");
                match.home_score = match_data.value("home_score", 0);
                match.away_score = match_data.value("away_score", 0);
                match.date = match_data.value("match_date", "");

                if (!match.home_team.empty() && !match.away_team.empty()) {
                    matches.push_back(match);
                }
            }
        }
    } catch (const json::exception& e) {
        std::cerr << "JSON error in " << file_path << ": " << e.what() << std::endl;
    }

    return matches;
}

std::vector<MatchResult> FootballData::loadAllMatches(const std::string& directory_path) {
    std::vector<MatchResult> all_matches;

    if (!fs::exists(directory_path)) {
        throw std::runtime_error("Directory not found: " + directory_path);
    }

    try {
        for (const auto& entry : fs::recursive_directory_iterator(directory_path)) {
            if (entry.path().extension() == ".json") {
                auto file_matches = parseJsonFile(entry.path().string());
                all_matches.insert(all_matches.end(), file_matches.begin(), file_matches.end());
            }
        }
    } catch (const fs::filesystem_error& e) {
        throw std::runtime_error("Filesystem error: " + std::string(e.what()));
    }

    return all_matches;
}
