#include <iostream>
#include <fstream>
#include <string>
// Created by Joshie Land on 4/20/25.
//

#include "Data.h"
class Match {
public:
    int date;
    std::string name;
    std::string away_team;
    int home_score;
    int away_score;

    Match(int date, std::string name, std::string away, int hscore, int ascore)
            : date(date), name(name), away_team(away), home_score(hscore), away_score(ascore) {}

};