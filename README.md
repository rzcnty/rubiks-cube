
# Rubik's Cube IDA* Solver

A command-line application that solves a standard 3x3x3 Rubik's Cube using the **Iterative Deepening A\* (IDA\*)** search algorithm. It is written in C language. 

## Table of Contents
- [About The Project](#about-the-project)
- [Technical Details](#technical-details)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation & Compilation](#installation--compilation)
- [Usage](#usage)
  - [Input Format](#input-format)
- [Limitations](#limitations)

## About The Project

The main goal of this project is to solve a famous problem with a large state space: the Rubik's Cube, using IDA, a classic AI search algorithm.

## Technical Details

- **Language:** C
- **Compiler:** GCC
- **Build System:** Make
- **Core Algorithm:** Iterative Deepening A\* (IDA\*)
- **Heuristic Function:** `h(n) = Number of misplaced stickers / 8` (to be admissible)

## Getting Started

Follow these steps to get a local copy up and running on your preferred operating system.

### Prerequisites

You will need a C compiler (like GCC) and the `make` build tool.

- On Debian/Ubuntu:
  ```bash
  sudo apt-get install build-essential
  ```
- On Fedora:
 ```bash
  sudo dnf5 group install "development-tools"
  sudo dnf5 group install "c-development" 
  ```

- On Windows:

1. [Install WSL](https://docs.microsoft.com/en-us/windows/wsl/install) by following the official Microsoft guide. I kindly recommend choosing Ubuntu as your distribution.

2. Once installed, open your Ubuntu terminal.

3. Install the necessary build tools:

``` bash
sudo apt-get update
sudo apt-get install build-essential
```

4. You can now proceed with the standard compilation steps inside your WSL terminal.

### Installation & Compilation

1. Clone the repository to your local machine:

```bash
git clone https://github.com/rzcnty/rubiks-cube.git
```

2. Navigate to the project's directory:

``` bash
cd rubiks-cube
```

3. Compile the project using the provided Makefile:

``` bash
make
```

This will create a rubik_solver executable in that directory.

## Usage

To run the solver, execute the binary from the project directory:

``` bash
./rubik_solver
```

The program will then prompt you to enter the cube's current state as a 54-character string.

### Input Format

The input is a single, 54-character string representing the colors of each sticker on the cube.

**Color Codes:**

- '0': White
- '1': Orange
- '2': Green
- '3': Red
- '4': Blue
- '5': Yellow

**Face Input Order:**

1. Up
2. Left
3. Front
4. Right
5. Back
6. Down

For each face, read the 9 colors row by row, from left to right.

Example (for a solved cube): 
000000000111111111222222222333333333444444444555555555

## Limitations

The solver uses a "Misplaced Tiles" heuristic for now. While effective for simple cases, it is not strong enough to prune the search tree efficiently for scrambles beyond 7-8 moves. After all, solve times increase exponentially with complexity. This limitation is a direct trade-off for the simplicity of the heuristic function. Future development will focus on integrating a stronger heuristic to enable the solver to tackle more complex, deeply scrambled cubes.
