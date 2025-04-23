#include "Data.h"
#include <fstream>
#include <sstream>

namespace fs = std::filesystem;

MatchResult FootballData::parseJsonFile(const std::string& file_path) {
    MatchResult match;
    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << file_path << "\n";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();
    std::string json_str = buffer.str();
    file.close();

    size_t pos = 0;
    size_t match_count = 0;

    while ((pos = json_str.find('{', pos)) != std::string::npos) {
        size_t end_pos = json_str.find('}', pos);
        if (end_pos == std::string::npos) break;

        std::string match_json = json_str.substr(pos, end_pos - pos + 1);
        pos = end_pos + 1;

        try {
            // Extract competition name
            match.competition = extractJsonValue(match_json, "competition_name");

            // Extract home team info
            std::string home_team_json = extractJsonValue(match_json, "home_team");
            match.home_team = extractJsonValue(home_team_json, "home_team_name");

            // Extract away team info
            std::string away_team_json = extractJsonValue(match_json, "away_team");
            match.away_team = extractJsonValue(away_team_json, "away_team_name");

            // Extract scores
            match.home_score = extractJsonInt(match_json, "home_score");
            match.away_score = extractJsonInt(match_json, "away_score");

            // Extract date
            match.date = extractJsonValue(match_json, "match_date");

            if (!match.home_team.empty() && !match.away_team.empty()) {
                match_count++;
            }
        } catch (...) {
            continue;
        }
    }

    if (match_count == 0) {
        std::cerr << "Warning: No valid matches found in " << file_path << "\n";
    }

    return match;
}

std::string FootballData::extractJsonValue(const std::string& json, const std::string& key) {
    const std::string key_pattern = "\"" + key + "\":";
    size_t key_pos = json.find(key_pattern);
    if (key_pos == std::string::npos) return "";

    size_t value_start = json.find_first_of("\"", key_pos + key_pattern.length());
    if (value_start == std::string::npos) return "";

    size_t value_end = json.find_first_of("\"", value_start + 1);
    if (value_end == std::string::npos) return "";

    return json.substr(value_start + 1, value_end - value_start - 1);
}

 int FootballData::extractJsonInt(const std::string& json, const std::string& key) {
    const std::string key_pattern = "\"" + key + "\":";
    size_t key_pos = json.find(key_pattern);
    if (key_pos == std::string::npos) return 0;

    size_t value_start = key_pos + key_pattern.length();
    size_t value_end = json.find_first_of(",}", value_start);

    try {
        std::string num_str = json.substr(value_start, value_end - value_start);
        return std::stoi(num_str);
    } catch (...) {
        return 0;
    }
}
