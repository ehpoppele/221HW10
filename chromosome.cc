/*
 * Implementation for Chromosome class
 */

#include <algorithm>
#include <cassert>
#include <random>
#include <chrono>
#include <cmath>

#include "chromosome.hh"

//////////////////////////////////////////////////////////////////////////////
// Generate a completely random permutation from a list of cities
Chromosome::Chromosome(const Cities* cities_ptr)
  : cities_ptr_(cities_ptr),
    order_(cities_ptr -> random_permutation(cities_ptr->size()))
{
  assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Clean up as necessary
Chromosome::~Chromosome()
{
    assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Perform a single mutation on this chromosome
//Works by selecting two numbers at random within the range of the chromosome's
//order, then making sure those are two different numbers, then swapping them
//through a placeholder value.
void
Chromosome::mutate()
{
    //set up our rng
    unsigned int range = order_.size() - 1;
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<int> distribution(0, range);
    //assign two random values
    unsigned int rand_1 = distribution(rng);
    unsigned int rand_2 = distribution(rng);
    while (rand_1 == rand_2)//reassign until they're different
    {
        rand_2 = distribution(rng);
    }
    unsigned int holder = order_.at(rand_2);
    order_[rand_2] = order_.at(rand_1);
    order_[rand_1] = holder;
    assert(is_valid());
}

//////////////////////////////////////////////////////////////////////////////
// Return a pair of offsprings by recombining with another chromosome
// Note: this method allocates memory for the new offsprings
//This method is fairly self-explanatory and simple, I hope
std::pair<Chromosome*, Chromosome*>
Chromosome::recombine(const Chromosome* other)
{
  assert(is_valid());
  assert(other->is_valid());

  // need to include size() because create_crossover_child takes [b, e):
  std::uniform_int_distribution<int> dist(0, order_.size());

  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine rng(seed);
  auto r1 = dist(rng);
  auto r2 = dist(rng);
  auto [b, e] = std::minmax(r1, r2);

  // Make children:
  auto child1 = create_crossover_child(this, other, b, e);
  auto child2 = create_crossover_child(other, this, b, e);

  return std::make_pair(child1, child2);
}

//////////////////////////////////////////////////////////////////////////////
// For an ordered set of parents, return a child using the ordered crossover.
// The child will have the same values as p1 in the range [b,e),
// and all the other values in the same order as in p2.
Chromosome*
Chromosome::create_crossover_child(const Chromosome* p1, const Chromosome* p2,
                                   unsigned b, unsigned e) const
{
  const unsigned len = p1->order_.size();
  assert(len == p2->order_.size());
  Chromosome* child = p1->clone();

  // We iterate over both parents separately, copying from parent1 if the
  // value is within [b,e) and from parent2 otherwise
  unsigned i = 0, j = 0;

  for ( ; i < len && j < len; ++i) {
    if (i >= b and i < e) {
      child->order_[i] = p1->order_[i];
    }
    else { // Increment j as long as its value is in the [b,e) range of p1
      while (p1->is_in_range(p2->order_[j], b, e)) {
        ++j;
      }
      assert(j < len);
      child->order_[i] = p2->order_[j];
      j++;
    }
  }

  assert(child->is_valid());
  return child;
}

// Return a positive fitness value, with higher numbers representing
// fitter solutions (shorter total-city traversal path).
//This is a very rough implementation; needs to be fixed
double Chromosome::get_fitness() const
{
    double constant = 1000;//Used for fit func, figure out most optimal constant later
    double dist = cities_ptr_->total_path_distance(order_);
    double power = 4;//also fiddling with this
    double fit = std::pow((constant/dist), power);
    return fit;
  // Add your implementation here
}

// A chromsome is valid if it has no repeated values in its permutation,
// as well as no indices above the range (length) of the chromosome.
// We implement this check with a sort, which is a bit inefficient, but simple
bool
Chromosome::is_valid() const
{
  auto order_copy = order_;
  std::sort (order_copy.begin(), order_copy.end());
  for (unsigned int i = 0; i<order_copy.size(); i++)
  {
      if(order_copy.at(i) != i)
      {
          return false;
      }
  }
  return true;
}

// Find whether a certain value appears in a given range of the chromosome.
// Returns true if value is within the specified the range specified
// [begin, end) and false otherwise.
bool Chromosome::is_in_range(unsigned value, unsigned begin, unsigned end) const
{
    for (unsigned int i = begin; i < end; i++)
    {
        if (order_.at(i) == value)
        {
            return true;
        }
    }
    return false;//If we get to the end without finding it
}
