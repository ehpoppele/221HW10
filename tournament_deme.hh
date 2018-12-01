#pragma once
#include "chromosome.hh"
#include "cities.hh"
#include <random>
#include "deme.hh"

class TournamentDeme: public Deme {
    
  public:
	TournamentDeme(const Cities* cities_ptr, unsigned pop_size, double mut_rate, int tournament_size);
    
	
	virtual Chromosome* select_parent() override;
    
  protected:
        
	int tournament_size_;

};
