# ChessGame

A simplified chess game built in C++ with a Qt graphical interface, developed as a first-year university project.

> **Authors:** Rayane Othmani & Ali Gabr — April 2023

---

## Overview

ChessGame is a two-player chess application featuring a graphical 8×8 board. It implements a subset of chess pieces with full move validation, turn management, check detection, and multiple game modes.

## Features

- Graphical chessboard rendered with Qt Widgets
- Implemented pieces: **King**, **Queen**, **Bishop**
- Full move validation per piece (including path obstruction checks)
- Check detection — prevents moves that leave your king in check
- Turn-based system (White moves first)
- Piece highlighting to show valid moves
- Multiple game modes via an in-game menu:
    - **New Game** — standard starting positions
    - **Only Kings** — minimal board with kings only
    - **Choose Starting Positions** — custom placement
- RAII-based move simulation (`MoveGuard`) for safe check validation
- Unit tests with **GoogleTest**

## Tech Stack

| Tool           | Purpose       |
| -------------- | ------------- |
| C++17          | Core language |
| Qt 6 (Widgets) | GUI framework |
| CMake          | Build system  |
| GoogleTest     | Unit testing  |
| gcov           | Code coverage |

## Project Structure

```
ChessGame/
├── main.cpp              # Application entry point
├── ChessWindow.h/cpp     # View layer — board rendering & user interaction
├── Piece.h/cpp           # Model layer — piece classes and move logic
├── MoveGuard.h/cpp       # RAII guard for temporary move simulation
├── Test.cpp              # GoogleTest unit tests
├── CMakeLists.txt        # Build configuration
├── googletest/           # GoogleTest library (bundled)
└── include/              # Course utilities and third-party headers
```

## Architecture

The project follows a model/view separation:

- **`model` namespace** — `Piece` (abstract base), `King`, `Queen`, `Bishop`. Each piece implements `validMove()` polymorphically.
- **`view` namespace** — `ChessWindow` manages the Qt board, handles click events, and orchestrates game state.
- **`MoveGuard`** — a RAII class that temporarily repositions a piece on the board to test whether a move results in check, then automatically restores the original position on destruction.

## Building

### Prerequisites

- Qt 6 (Widgets component)
- CMake ≥ 3.10
- A C++17-compatible compiler (GCC, Clang, or MSVC)

### Steps

```bash
mkdir build && cd build
cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt/lib/cmake
cmake --build .
```

> **Note:** Update `CMAKE_PREFIX_PATH` in `CMakeLists.txt` (or pass it on the command line) to point to your local Qt installation.

### Running Tests

The test target is built alongside the main executable. Run the output binary with the `--gtest_filter` flag, or simply execute it to run all tests:

```bash
./ProjetTest --gtest_also_run_disabled_tests
```

## Known Limitations

- Image assets currently require local file paths — moving to Qt resource files (`.qrc`) would make the build fully portable
- `King::s_kingCount` is a static counter that does not reset between games within the same session
