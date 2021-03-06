/*
 * API file for Travelling-Salesperson Cities class and utilities
 */

#pragma once

#include <vector>
#include <iostream>


// Representation of an ordering of cities
class Cities {

public:
    // A pair of integral coordinates for each city
    using coord_t = std::pair<int, int>;

    // An ordering of the cities in cities_t. Each value represents a unique index
    // into the current city ordering.
    using permutation_t = std::vector<unsigned int>;

    // Given a permutation, return a new Cities object where the order of the
    // cities reflects the original order of this class after reordering with
    // the given ordering. So for example, the ordering { 1, 0 } simply swaps
    // the first two elements (coordinates) in the new Cities object.
    Cities reorder(const permutation_t& ordering) const;

    // For a given permutation of the cities in this object,
    // compute how long (distance) it would take to traverse all the cities in the
    // order of the permutation, and then returning to the first city.
    // The distance between any two cities is computed as the Euclidean
    // distance on a plane between their coordinates.
    double total_path_distance(const permutation_t& ordering) const;

    //Returns a random permutation of integers from 0 to len-1
    permutation_t random_permutation(unsigned len) const;

    //helper for tsp
    //number of cities in the list
    int size() const;
    
    //Helper function that returns the elements of a cities object
    std::vector<coord_t> get_elements() const;

    friend std::istream& operator >> (std::istream& in, Cities& cities_ls);
    friend std::ostream& operator << (std::ostream& os, Cities& cities_ls);
private:
    //vector list of coordinates of cities
    std::vector<coord_t> city_elements_;

    //helper method for finding total distance
    //finds distance between two cities
    double dist_between(coord_t city_a, coord_t city_b) const;

};
