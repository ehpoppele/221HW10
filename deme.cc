/*
 * Declarations for Deme class to evolve a genetic algorithm for the
 * travelling-salesperson problem.  A deme is a population of individuals.
 */
#include <algorithm>
#include <cmath>
#include <cassert>
#include "chromosome.hh"
#include "climb_chromosome.hh"
#include "deme.hh"
#include <random>
#include <chrono>

// Generate a Deme of the specified size with all-random chromosomes.
// Also receives a mutation rate in the range [0-1].
Deme::Deme(const Cities* cities_ptr, unsigned pop_size, double mut_rate)
{
    mut_rate_ = mut_rate;
    pop_=std::vector<Chromosome*>();
    for(unsigned i = 0; i < pop_size; i++ ) {
	ClimbChromosome* new_chrom = new ClimbChromosome(cities_ptr);
	pop_.push_back(new_chrom);
    }
}

// Clean up as necessary
Deme::~Deme()
{
    //pop_ is a vector which should be a smart data type, but for some reason this is necessary
    for (auto chrom : pop_)
    {
        delete chrom;
    }
    // deme member variables:
    // mut_rate is a primitive, don't need to delete it
    // default_random_engine is a mystery.

    // Add your implementation here
}

// Evolve a single generation of new chromosomes, as follows:
// We select pop_size/2 pairs of chromosomes (using the select() method below).
// Each chromosome in the pair can be randomly selected for mutation, with
// probability mut_rate, in which case it calls the chromosome mutate() method.
// Then, the pair is recombined once (using the recombine() method) to generate
// a new pair of chromosomes, which are stored in the Deme.
// After we've generated pop_size new chromosomes, we delete all the old ones.
void Deme::compute_next_generation()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator (seed);
    unsigned int generation_size = pop_.size() / 2;
    std::vector<Chromosome*> children_vec({});
    for(unsigned int i = 0; i < generation_size; i++ ) {
    	auto father = select_parent();
    	double mut_roll = std::generate_canonical<double,std::numeric_limits<double>::digits>(generator);
        // mut_roll is a random in [0,1)
    	if(mut_roll < mut_rate_) {
    	    father -> mutate();
    	}
    	auto mother = select_parent();
    	mut_roll = std::generate_canonical<double,std::numeric_limits<double>::digits>(generator);
    	if(mut_roll < mut_rate_) {
    	    mother -> mutate();
    	}
    	auto children = father -> recombine(mother);
    	children_vec.push_back(children.first);
    	children_vec.push_back(children.second);
    }
    for (auto chrom : pop_)
    {
        delete chrom;
    }
    pop_ = children_vec;
}

// Return a copy of the chromosome with the highest fitness.
const Chromosome* Deme::get_best() const
{
    return *std::max_element(pop_.begin(), pop_.end(),
            [] (Chromosome* a, Chromosome* b)
    {
	return a->get_fitness() > b->get_fitness();
    }
            );
}

// Randomly select a chromosome in the population based on fitness and
// return a pointer to that chromosome.
Chromosome* Deme::select_parent()
{
  // Figure out what the total sum of fitness in pop_ is:
  const double total_fitness = std::accumulate(pop_.cbegin(), pop_.cend(), 0.,
      [](double sum, auto cp){ return sum + cp->get_fitness(); });

  // Pick a random fitness sum value to stop the wheel at:
  static std::uniform_real_distribution<> dist(0.0, 1);
  const double threshold = total_fitness * dist(generator_);

  // Now, find the first chromosome whose partial sum of fitness exceeds threshold:
  double fit_sum = 0.; // Total fitness so far

  const auto it = std::find_if(pop_.cbegin(), pop_.cend(), [&](auto cp) {
        fit_sum += cp->get_fitness();
        return fit_sum >= threshold;
   });
  assert(it != pop_.cend());

  return *it;
}
