#include <iostream>
// Created by Joshua Austin Land on 4/22/25.
// Currently, Mergesort takes in a vector or list and creates a subset of all instances
// that match with team name.
template <typename T>
void Merge(T& subset, T& Lsort, T& Rsort, const std::string& home_team, const std::string& opponent = "") {
    auto L = Lsort.begin();
    auto R = Rsort.begin();

    while (L != Lsort.end() && R != Rsort.end()) {
        if (L->date < R->date) {
            subset.push_back(*L);
            L++;
        }
        else {
            subset.push_back(*R);
            R++;
        }
    }
    while (L != Lsort.end()) {
        subset.push_back(*L);
        L++;
    }
    while (R != Rsort.end()) {
        subset.push_back(*R);
        R++;
    }
}
