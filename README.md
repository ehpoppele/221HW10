# 221HW10
Partners: Eli Poppele and Jon Takagi

# README
## Contents
1. Files
2. Design
3. Results
4. Other Notes

## Files
### README.md
This file, using .md so that it looks pretty on github. I advise reading this there if you are currently using a text editor.
### cities
Should include a .hh for declarations, a .cc for implementations, and possibly a .o object file. These are largely the same as what we turned in last week, although there was an update to the reorder method to prevent a memory leak error that we didn't catch last time.
### chromosome
Should also have a header .hh, implementation .cc, and object .o that we don't care about. Contains our chromosome class, implemented as described by the assignment.
### deme
Our declarations for the deme class appear in our .hh header file, the implementation is in the .cc, and the .o object may also be floating around in the repository, because it's too easy to just git add all and end up tracking those as well.
### climb_chromosome
This set of files cotains our code for the climb_chromosome class. The header declares a few overrides for methods it inherits from chromosome, while the .cc file contains the implementation for the new mutate function.
### tournament_deme
This set of files contains code for our new tournament_deme class, which inherits from deme. The header has the declarations for the functions we overrode for this new class, while the .cc file contains the implementation for the new constructor and selece_parent methods.
### .tsv files
In this repository, we should have three .tsv files from Moodle: linear.tsv, five.tsv, and challenge.tsv. These were the given sets of cities that we tested our code on. The remaining are the output of our tsp program: ga_baseline.tsv is the output of our genetic algorithm search, while randomized.tsv is the output of the random search implemented last week. local.tsv is the output from running tsp with climb chromosomes, while tournament.tsv is the output when implementing both climb chromosomes and tournament deme. shortest.tsv is the shortest path from whichever algorithm the program most recently used (should be tournament at the time of pushing this).
### tsp
This is our actual main program. It takes the requisite three arguments, a .tsv file, a population size, and a mutation rate (between 0 and 1). There should be a .cc file which contains our implementations; this is pretty much just the framework from Moodle (I believe we didn't change it). There should also be a .o object, as well as a no-extension binary, tsp, which is the main program for this project.

## Design
Implementation of these new classes was fairly simple. We only overrode whatever methods were necessary, and made as few changes as were needed. In climb_chromosome, we simply made each swap, checked the fitness, then swapped back, and then ran through some if statements, and swapped back to whatever order had the highest fitness before returning. For tournament_deme, we randomly filled a tournament with chromosomes by picking one chromosome at random, then addiing that and the following chromosomes successively until the tournament was filled. Our tournament itself is slightyl unsual, but functions fine. We take the last two chromosomes in the tournament vector and have them fight to the death--by which I mean we compare their fitnesses and cut the one with lower fitness from the tournament. The one with the higher fitness is then added back in for another round of mortal combat. At the end, only the chromosome with the highest fitness will remain.

## Results
We found that climb_chromomose was much better than the regular chromosome and produced much better results, especially when the mutation rate was turned up to the maximum. We also found that there wasn't much real progress after only a few hundred, sometimes a thousand, iterations. This seems to be when the mutation has maxed out all the current chromosomes and recombining fails to improve them. For the genetic algorithm to be useful beyond this point, we need to rework recombine or some other methods to produce more useful results. It also appears that the tournament method only made our program worse, as we got stuck in the upper teens of the thousands of units, while with the original parent selection method with climb_chromosome produced results as low as 11-13 thousand units.

## Other Notes
TSP should currently be run with a population size greater than 16, as that is the current tournament size, and errors may occur if a smaller population is used. Compiling should be done using the makefile. At the time of writing, there are no known bugs or memory leaks.
