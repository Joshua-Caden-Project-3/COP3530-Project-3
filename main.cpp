#include "Data.h"
#include "Mergesort.cpp"
#include "Quicksort.cpp"
#include <iostream>
#include <iomanip>
#include <filesystem>
#include <sstream>
#include <algorithm>
#include <cctype>

namespace fs = std::filesystem;

bool iequals(const std::string& a, const std::string& b) {
    return std::equal(a.begin(), a.end(), b.begin(), b.end(),
                      [](char a, char b) { return tolower(a) == tolower(b); });
}

void displayMatches(const std::vector<MatchResult>& matches, size_t limit = 5,
                    const std::string& title = "RECENT MATCHES") {
    if (matches.empty()) {
        std::cout << "No matches found.\n";
        return;
    }

    size_t count = std::min(matches.size(), limit);
    size_t start = matches.size() > count ? matches.size() - count : 0;

    std::cout << "\n" << title << " (" << count << " of " << matches.size() << "):\n"
              << std::left << std::setw(12) << "DATE" << std::setw(25) << "HOME"
              << std::setw(10) << "SCORE" << std::setw(25) << "AWAY\n"
              << std::string(72, '-') << "\n";

    for (size_t i = start; i < matches.size(); i++) {
        const auto& m = matches[i];
        std::cout << std::setw(12) << m.date.substr(0, 10)
                  << std::setw(25) << (m.home_team.size() > 24 ? m.home_team.substr(0,23)+"." : m.home_team)
                  << std::setw(3) << m.home_score << " - " << std::setw(3) << m.away_score
                  << std::setw(25) << (m.away_team.size() > 24 ? m.away_team.substr(0,23)+"." : m.away_team)
                  << "\n";
    }
}

double calculateWinProbability(const std::vector<MatchResult>& matches, const std::string& target_team) {
    if (matches.empty()) return 0.0;

    int wins = 0;
    int total = 0;

    for (const auto& m : matches) {
        bool is_home = iequals(m.home_team, target_team);
        bool is_away = iequals(m.away_team, target_team);

        if (is_home || is_away) {
            total++;
            if ((is_home && m.home_score > m.away_score) ||
                (is_away && m.away_score > m.home_score)) {
                wins++;
            }
        }
    }

    return (total > 0) ? (static_cast<double>(wins) / total) * 100 : 0.0;
}

std::string formatTeamName(std::string name) {
    std::replace(name.begin(), name.end(), '_', ' ');
    name.erase(name.begin(), std::find_if(name.begin(), name.end(), [](int ch) { return !std::isspace(ch); }));
    name.erase(std::find_if(name.rbegin(), name.rend(), [](int ch) { return !std::isspace(ch); }).base(), name.end());
    return name;
}

int main() {
    std::vector<MatchResult> all_matches;

    try {
        std::string data_path = "../statsbomb_data";
        std::cout << "Loading data from: " << fs::absolute(data_path) << "\n";

        all_matches = FootballData::loadAllMatches(data_path);

        if (all_matches.empty()) {
            std::cerr << "Error: No matches loaded. Check:\n"
                      << "1. Data path exists\n"
                      << "2. JSON files are in the directory\n"
                      << "3. Files have correct format\n";
            return 1;
        }

        std::cout << "Successfully loaded " << all_matches.size() << " matches.\n";

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    bool running = true;
    while (running) {
        std::cout << "\nFootball Match Predictor\n"
                  << "1 <team> - Team win probability\n"
                  << "2 <team> <opponent> - Head-to-head\n"
                  << "3 - Show all matches\n"
                  << "4 - Quit\n"
                  << "Enter command: ";

        std::string line;
        std::getline(std::cin, line);
        std::istringstream iss(line);
        std::string cmd, team_input, opponent_input;
        iss >> cmd >> team_input >> opponent_input;

        std::string team = formatTeamName(team_input);
        std::string opponent = formatTeamName(opponent_input);

        if (cmd == "1" && !team.empty()) {
            auto team_matches = Quicksort(all_matches, team, "");

            if (team_matches.empty()) {
                std::cout << "No matches found for: " << team << "\n";
                continue;
            }

            double win_prob = calculateWinProbability(team_matches, team);
            std::cout << "\n" << team << " - Win Probability: "
                      << std::fixed << std::setprecision(1) << win_prob << "%\n";

            displayMatches(team_matches, 5, "Recent Matches (Quicksorted)");

        } else if (cmd == "2" && !team.empty() && !opponent.empty()) {
            auto h2h_matches = Mergesort(all_matches, 0, all_matches.size()-1, team, opponent);

            if (h2h_matches.empty()) {
                std::cout << "No matches between " << team << " and " << opponent << "\n";
                continue;
            }

            double team_win = calculateWinProbability(h2h_matches, team);
            double opponent_win = calculateWinProbability(h2h_matches, opponent);
            double draw = 100.0 - team_win - opponent_win;

            std::cout << "\nHead-to-Head: " << team << " vs " << opponent << "\n";
            std::cout << team << " wins: " << std::fixed << std::setprecision(1) << team_win << "%\n";
            std::cout << opponent << " wins: " << std::fixed << std::setprecision(1) << opponent_win << "%\n";
            std::cout << "Draw probability: " << std::fixed << std::setprecision(1) << draw << "%\n";

            displayMatches(h2h_matches, h2h_matches.size(), "All Matches (Mergesorted)");

        } else if (cmd == "3") {
            displayMatches(all_matches, all_matches.size(), "All Available Matches");
        } else if (cmd == "4") {
            running = false;
            std::cout << "Exiting...\n";
        } else {
            std::cout << "Invalid command. Try again.\n";
        }
    }

    return 0;
}