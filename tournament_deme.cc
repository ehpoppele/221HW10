#include "tournament_deme.hh"
#include "chromosome.hh"
#include "cities.hh"
#include "deme.hh"

#include <vector>
#include <random>
#include <random>
#include <chrono>


TournamentDeme::TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate, int tournament_size) :
    Deme(cities_ptr, pop_size, mut_rate) 
    {
        tournament_size_ = tournament_size;
    }
        
Chromosome* TournamentDeme::select_parent() 
{
    //we need to fill tournament with some random population stuff, can't just leave it empty
    std::vector<Chromosome*> tournament({});
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<int> distribution(0, pop_.size());
    unsigned int rand_index = distribution(rng);
    for (int i = 0; i < tournament_size_; i++) {//size loop in stuff from pop, pick at random
        tournament.push_back(pop_.at((rand_index + i) % pop_.size()));
    }
    Chromosome* chrom1;
    Chromosome* chrom2;
    while(tournament.size() > 1) {
        chrom1 = tournament.back();
        tournament.pop_back();
        chrom2 = tournament.back();
        tournament.pop_back();
        if(chrom1 -> get_fitness() > chrom2 -> get_fitness()) {
            tournament.push_back(chrom1);
        } else {
            tournament.push_back(chrom2);
        }
    }
        return tournament.back();
}

