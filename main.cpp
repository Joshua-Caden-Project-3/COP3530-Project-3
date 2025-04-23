#include "Mergesort.cpp"
#include "Quicksort.cpp"
#include "Data.h"
#include <iostream>
#include <filesystem>
#include <sstream>
namespace fs = std::filesystem;


int main() {
    std::cout << "This program is intended to predict a team's chance of winning!\nInput a digit specifying which command and variables accordingly.\nUse _ for the spaces in a team's name i.e. 2 Real_Madrid Manchester_United.\n1: Team\n2: Team Opponent\n3: Quit" << std::endl;
    FootballData data1;
    std::vector<MatchResult> data;

    for (const auto& entry : fs::directory_iterator("../statsbomb_data")) {
        MatchResult match = FootballData::parseJsonFile(entry.path().string());
        data.push_back(match);
    }
    std::string line;
    std::getline(std::cin, line);
    std::istringstream stream(line);
    std::string num, name, opp;
    stream >> num >> name >> opp;
    double numerator=0, denominator=0;
    if (num == "1") {
        std::vector<MatchResult> mdata = Mergesort(data, 0, data.size() - 1, name, "");
        std::vector<MatchResult> qdata = Quicksort(data, name, "");
        std::cout << "1" << std::endl;
        for (int i = 0; i < mdata.size(); i++) {
            double weight = (i+1) / mdata.size();
            if (mdata[i].home_team == name) {
                if (mdata[i].home_score > mdata[i].away_score) numerator += weight;
                denominator+=weight;
            }
            else if (mdata[i].home_team == opp) {
                if (mdata[i].home_score < mdata[i].away_score) numerator += weight;
                denominator+=weight;
            }
        }
    }
    else if (num == "2") {
        std::vector<MatchResult> mdata = Mergesort(data, 0, data.size() - 1, name, opp);
        std::vector<MatchResult> qdata = Quicksort(data, name, opp);
        for (int i = 0; i < mdata.size(); i++) {
            double weight = (i+1) / mdata.size();
            if (mdata[i].home_team == name && mdata[i].away_team == opp) {
                weight*=2;
                if (mdata[i].home_score > mdata[i].away_score) numerator += weight;
                denominator+=weight;
            }
            else if (mdata[i].home_team == opp && mdata[i].away_team == name) {
                weight*=2;
                if (mdata[i].home_score < mdata[i].away_score) numerator += weight;
                denominator+=weight;
            }
            else if (mdata[i].home_team == opp && mdata[i].away_score > mdata[i].home_score){
                numerator += weight;
                denominator+=weight;
            }
            else if (mdata[i].home_team == name && mdata[i].away_score < mdata[i].home_score){
                numerator += weight;
                denominator+=weight;
            }
        }

    }
    else if (num == "3") {
        std::cout << "Have a great day!" << std::endl;
    }
    return 0;
}