# simulator-elevator

A simple elevator simulation project built with C++ and SFML. The program visually simulates the movement of an elevator across multiple floors, with passengers boarding and exiting based on their assigned destination floors.

## 🚀 Features

- Elevator moving between 5 floors (0–4)
- Passengers with specific origin and destination floors
- Maximum elevator capacity: 8 people
- Elevator stops only when someone needs to enter or exit
- Request queue system
- Visual representation of passengers on each floor and inside the elevator
- Buttons for calling the elevator and selecting destination floors

## 🔧 Requirements

- C++17 (or later)
- SFML 2.5.1+
- Font file `arial.ttf` (must be placed in the executable directory)

## ▶️ How to Run

1. Compile the project using a C++17-compatible compiler with SFML linked.
2. Place the `arial.ttf` font in the same directory as the executable.
3. Run the application.

### Example compilation (Linux/macOS):
```bash
g++ -std=c++17 main.cpp -o elevator_sim -lsfml-graphics -lsfml-window -lsfml-system
