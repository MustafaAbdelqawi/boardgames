# Board Games

Small two-player board games written in C++ for the terminal.

## Games

- **Connect Four** - Players choose columns 1-7 and take turns dropping `X` and `O` pieces. The first player to connect four pieces horizontally, vertically, or diagonally wins.
- **Tic-Tac-Toe** - Players take turns placing `X` and `O` on a 3x3 board. The first player to complete a row, column, or diagonal wins.

## Requirements

- A C++ compiler with C++17 support
- A terminal

The games use only the C++ standard library and do not require third-party dependencies.

## Build and Run

From the repository root, compile and run each game separately:

### Connect Four

```bash
g++ -std=c++17 -Wall -Wextra -pedantic connect-four/main.cpp -o connect-four/connect-four
./connect-four/connect-four
```

Enter both player names, then choose a column from `1` to `7` on each turn.

### Tic-Tac-Toe

```bash
g++ -std=c++17 -Wall -Wextra -pedantic tic-tac-toe/main.cpp -o tic-tac-toe/tic-tac-toe
./tic-tac-toe/tic-tac-toe
```

Players choose a board position from `0` to `8`. Positions are numbered left to right and top to bottom:

```text
0 | 1 | 2
--+---+--
3 | 4 | 5
--+---+--
6 | 7 | 8
```

## Project Structure

```text
.
├── connect-four/
│   └── main.cpp
├── tic-tac-toe/
│   └── main.cpp
└── README.md
```

## Notes

These are learning projects designed for local terminal play. Each game manages its own board, input loop, win detection, and draw handling in its `main.cpp` file.
