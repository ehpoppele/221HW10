#pragama once
#include "chromosome.hh"
#include "cities.hh"
#include <random>
#include "deme.hh"
#include <vector>

class TournamentDeme: public Deme {
    TournamentDeme::TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate,int tournament_size) :
        tournament_size_(tournament_size) {
            Deme(cities_ptr, pop_size, mut_rate);
        }
    Chromosome* TournamentDeme::select_parent() {
        std::vector<Chromosome*> tournament({});
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
}
