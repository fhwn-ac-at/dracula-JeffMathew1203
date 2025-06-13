# Snakes and Ladders Monte Carlo Simulation

This project simulates the board game "Snakes and Ladders" with randomly generated boards and performs Monte Carlo analyses. It is written in C and uses a modular design.

## Features

- Random generation of snakes and ladders based on configuration
- Flexible board size and dice face count
- Simulation of any number of games (Monte Carlo)
- Statistical evaluation: average rolls, shortest winning path, usage of snakes/ladders
- Colored console output of the board (snakes = red, ladders = yellow)
- Error handling for unsolvable or problematic boards

## Project Structure

```
.
├── include/        # Header files (.h)
├── src/            # Source code (.c)
├── obj/            # Object files (created during build)
├── config.txt      # Example configuration file
├── Makefile        # Build system
└── README.md       # This file
```

## Compilation

Requirement: `clang` or `gcc` and `make` must be installed.

```sh
make
```

This creates the executable `snakes`.

## Execution

Run the program with the configuration file:

```sh
./snakes config.txt
```

The program reads the settings from the configuration file and displays the board along with simulation results.

## Configuration File (config.txt)

The file must contain the following values (one per line):

```
<rows> <cols> <die_faces>
<num_ladders>
<num_snakes>
<num_simulations>
```

### Example:

```
20 20 6
5
4
555
```

## Sample Output

The board is displayed in color with all snakes (red) and ladders (yellow). After the simulation, statistics such as average rolls, shortest winning path, and usage of snakes/ladders are displayed.

## Notes

- The program checks whether the goal is reachable. In the case of unsolvable boards or infinite loops, an error message is shown.
- The number of simulations is taken exclusively from the configuration file.
- Colors work in most Unix terminals.

Enjoy simulating!

