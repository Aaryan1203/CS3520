## Overview
This project is a 2D simulation of a world inhabited by ants and doodlebugs, representing preys and predators respectively. The simulation is conducted on a grid of cells, where each cell can be occupied by one critter at a time. The world is enclosed by glass walls, and critters can bounce off these walls. The simulation progresses in time-steps, with each critter performing specific actions based on predefined rules.

## Critters
Ants

### There are four types of ants:
#### Queen Ants (Q): The queen ant is the founder of the colony and lays eggs to produce other ants.
#### Worker Ants (w): Female ants that perform various tasks within the colony.
#### Male Ants (o): Male ants that mate with the queen ant.
#### Reproductive Ants: New queen ants that go on to start their own colonies.
#### Doodlebugs (X): Doodlebugs are predators that hunt and eat ants. They follow specific movement and breeding rules to survive and reproduce.


## Simulation Rules
#### Ant Behavior

### Move:
Queen ants stay stationary until they have founded the colony and produced offspring.
After founding the colony, queen ants move like other ants.
Ants move randomly to one of the 8-adjacent cells unless the cell is occupied or leads to a collision with the wall.
The doodlebugs move in a clockwise direction unless they see an ant. If so, they will break their clockwise movement to eat the ant
Ant's will evade doodlebugs half of the time to ensure they live longer

### Breed:
Queens breed if they survive 30 time-steps after mating.
Offspring are created in empty cells within the 16-neighborhood of the queen.
If no empty cells are available, breeding does not occur.
Queens die if they cannot breed within 90 time-steps.
Doodlebugs breed after surviving for 10 time-steps, spawning new doodlebugs in the 16-neighborhood.
Doodlebugs only breed 50% of the time

### Starve:
Ants that do not move for 5 time-steps die of starvation.
Queen ants do not starve.
Doodlebugs that do not eat an ant within 20 time-steps die of starvation.

### Simulation Termination
The simulation runs until one species is eliminated or a cyclic pattern emerges.
The program stops automatically when either condition is met, or can be terminated manually if a cyclic pattern is observed.

### User Input
The user can specify the initial number of doodlebugs, queen ants, and male and female ants (default: 15 doodlebugs, 50 ants, and 2 queens).
