#include "climb_chromosome.hh"
#include <random>
#include <chrono>
#include <cassert>
#include <algorithm>

void ClimbChromosome::mutate()
{
    //set up our rng
    unsigned int range = order_.size() - 1;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<int> distribution(0, range);
    unsigned int index_p = distribution(rng);//Select our random city index
    unsigned int size = order_.size();
    double fit_base = get_fitness();
    std::swap(order_[index_p], order_[(index_p - 1)%size]);//first swap
    double fit_left = get_fitness();
    std::swap(order_[index_p], order_[(index_p - 1)%size]);//undo swap
    std::swap(order_[index_p], order_[(index_p + 1)%size]);//swap with p+1
    double fit_right = get_fitness();
    //then check which fitness is greatest, revert to that order, and return
    if (fit_right > fit_left)
    {
        if (fit_right > fit_base) 
        {
            assert(is_valid());
            return;
        } else {
            std::swap(order_[index_p], order_[(index_p + 1)%size]);//swap back to original
            assert(is_valid());
            return;
        }
    } else {
        if (fit_left > fit_base)
        {
            std::swap(order_[index_p], order_[(index_p + 1)%size]);//swap back to original
            std::swap(order_[index_p], order_[(index_p - 1)%size]);//swap to left
            assert(is_valid());
            return;
        } else {
            std::swap(order_[index_p], order_[(index_p + 1)%size]);//swap back to original
            assert(is_valid());
            return;
        }
    }
        
}

    

