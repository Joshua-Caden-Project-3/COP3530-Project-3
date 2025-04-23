#include <iostream>
#include <sstream>
#include <vector>
#include "Mergesort.cpp"
#include "Quicksort.cpp"


int main() {
    std::cout << "This program is intended to predict a team's chance of winning!\nInput a digit specifying which command and variables accordingly.\nUse _ for the spaces in a team's name i.e. 2 Real_Madrid Manchester_United.\n1: Team\n2: Team Opponent\n3: Quit" << std::endl;
    std::vector<Match> data = {
            Match(20230101, "Real_Madrid", "Barcelona", 2, 1),
            Match(20230201, "Real_Madrid", "Atletico_Madrid", 3, 0),
            Match(20230301, "Barcelona", "Real_Madrid", 1, 1),
            Match(20230401, "Real_Madrid", "Sevilla", 4, 1)
    };
    std::string line;
    std::getline(std::cin, line);
    std::istringstream stream(line);
    std::string num, name, opp;
    stream >> num >> name >> opp;
    double numerator=0, denominator=0;
    if (num == "1") {
        std::cout << "1" << std::endl;
        std::vector<Match> mdata = Mergesort(data, 0, data.size() - 1, name, "");
        std::vector<Match> qdata = Quicksort(data, name, "");
        for (int i = 0; i < mdata.size(); i++) {
            double weight = (i+1) / mdata.size();
            if (mdata[i].name == name) {
                if (mdata[i].home_score > mdata[i].away_score) numerator += weight;
                denominator+=weight;
            }
            else if (mdata[i].name == opp) {
                if (mdata[i].home_score < mdata[i].away_score) numerator += weight;
                denominator+=weight;
            }
        }
    }
    else if (num == "2") {
        std::vector<Match> mdata = Mergesort(data, 0, data.size() - 1, name, opp);
        std::vector<Match> qdata = Quicksort(data, name, opp);
        for (int i = 0; i < mdata.size(); i++) {
            double weight = (i+1) / mdata.size();
            if (mdata[i].name == name && mdata[i].away_team == opp) {
                weight*=2;
                if (mdata[i].home_score > mdata[i].away_score) numerator += weight;
                denominator+=weight;
            }
            else if (mdata[i].name == opp && mdata[i].away_team == name) {
                weight*=2;
                if (mdata[i].home_score < mdata[i].away_score) numerator += weight;
                denominator+=weight;
            }
            else if (mdata[i].name == opp && mdata[i].away_score > mdata[i].home_score){
                numerator += weight;
                denominator+=weight;
            }
            else if (mdata[i].name == name && mdata[i].away_score < mdata[i].home_score){
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