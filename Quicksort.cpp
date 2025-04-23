#include <iostream>
//
// Created by Joshua Austin Land on 4/20/25.
// It currently supports checking for team name and
// returning a subset using a data structure of type T. T cannot be a vector
template <typename T>
T Quicksort(const T& data, const std::string& home_team, const std::string& opponent = "") {
    auto pivot = data[0];
    T right, subset; // This will be subset of the data that is usable for our formula
    for (int i=0; i < data.size(); i++) {
        if (data[i].home_team != home_team && data[i].away_team != home_team) continue;
        if (data[i].date < pivot.date) {
            subset.push_back(data[i]);
        }
        else {
            right.push_back(data[i]);
        }
    }
    subset = Quicksort(subset, home_team, opponent);
    right = Quicksort(right, home_team, opponent);
    if (pivot.home_team == home_team || pivot.away_team == home_team) {
        subset.push_back(pivot);
    }
    subset.insert(subset.end(), right.begin(), right.end());
    return subset;
}