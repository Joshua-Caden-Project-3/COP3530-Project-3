#include "Merge.cpp"
// Created by Joshua Austin Land on 4/12/25.
// Currently, Mergesort takes in a vector or list and creates a subset of all instances
// that match with team name.

template <typename T>
T Mergesort(const T& data, int left, int right, const std::string& home_team, const std::string& opponent = "") {
    T subset; // This will be subset of the data that is usable for our formula
    int mid = left+(right-left)/2;
    T Lsort = Mergesort<T>(data, left, mid,  home_team, opponent);
    T Rsort = Mergesort<T>(data,mid+1, right, home_team, opponent);
    Merge<T>(subset, Lsort, Rsort, home_team, opponent);
    return subset;
}

