#pragma once

#include "chromosome.hh"

class ClimbChromosome : public Chromosome
{
	public:
        //I think we need to explicitly write the constructor for this case? testing agrees
        ClimbChromosome(const Cities* cities)
        : Chromosome(cities)
        {}

        // Need to explicitly write the virtual destructor even though we're not changing it
        virtual ~ClimbChromosome() = default;

        virtual void mutate() override;
        
        virtual ClimbChromosome* clone() const override
        {
            return new ClimbChromosome(*this);
        }
        
};       