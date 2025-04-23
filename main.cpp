#include "Mergesort.cpp"
#include "Quicksort.cpp"
#include "Data.h"
#include <iostream>
#include <filesystem>
#include <sstream>
namespace fs = std::filesystem;


int main() {
    bool loop = true;
    std::vector<MatchResult> data;
    for (const auto& entry : fs::directory_iterator("../statsbomb_data")) {
        MatchResult match = FootballData::parseJsonFile(entry.path().string());
        data.push_back(match);
    }
    while (loop) {
        std::cout << "This program is intended to predict a team's chance of winning!\nInput a digit specifying which command and variables accordingly.\nUse _ for the spaces in a team's name i.e. 2 Real_Madrid Manchester_United.\n1: Team\n2: Team Opponent\n3: Quit" << std::endl;
        std::string line;
        std::getline(std::cin, line);
        std::istringstream stream(line);
        std::string num, name, opp;
        stream >> num >> name >> opp;
        double numerator=0, denominator=0;
        if (num == "1" && name.length() > 0) {
            std::vector<MatchResult> mdata = Mergesort(data, 0, data.size() - 1, name, "");
            for (int i = 0; i < mdata.size(); i++) {
                double weight = (i + 1) / mdata.size();
                if (mdata[i].home_team == name) {
                    if (mdata[i].home_score > mdata[i].away_score) numerator += weight;
                    denominator += weight;
                } else if (mdata[i].home_team == opp) {
                    if (mdata[i].home_score < mdata[i].away_score) numerator += weight;
                    denominator += weight;
                }
            }
            if (mdata.size() > 0) {
                std::cout << name << "s chance of winning is around " << numerator / denominator << "%." << std::endl;
            }
        } else if (num == "2" && name.length() > 0 && opp.length() > 0) {
            std::vector<MatchResult> qdata = Quicksort(data, name, opp);
            for (int i = 0; i < qdata.size(); i++) {
                double weight = (i + 1) / qdata.size();
                if (qdata[i].home_team == name && qdata[i].away_team == opp) {
                    weight *= 2;
                    if (qdata[i].home_score > qdata[i].away_score) numerator += weight;
                    denominator += weight;
                } else if (qdata[i].home_team == opp && qdata[i].away_team == name) {
                    weight *= 2;
                    if (qdata[i].home_score < qdata[i].away_score) numerator += weight;
                    denominator += weight;
                } else if (qdata[i].home_team == opp && qdata[i].away_score > qdata[i].home_score) {
                    numerator += weight;
                    denominator += weight;
                } else if (qdata[i].home_team == name && qdata[i].away_score < qdata[i].home_score) {
                    numerator += weight;
                    denominator += weight;
                }
            }
            if (qdata.size() > 0) {
                std::cout << name << "s chance of beating " << opp << " is around " << numerator / denominator << "%."
                          << std::endl;
            }
        } else if (num == "3") {
            loop = false;
            std::cout << "Have a great day!" << std::endl;
        }
        else {
            std::cout << "We didn't quite understand your input.\n1 Team_Name\n2 Team_Name Opponent_Name\n3" << std::endl;
        }
    }
    return 0;
}