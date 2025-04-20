🐍 Snake Game — Modern Qt Edition
A modern take on the classic Snake game built using C++ and Qt 6 (or Qt 5). Features include a clean dark UI, score tracking, and a restart prompt after game over. Designed with simplicity and modern styling in mind.



🚀 Features
✅ Real-time snake movement with keyboard controls

🎯 Food spawning logic with no overlap

🧠 Score system: +5 points per food eaten

💀 Game Over detection (walls & self-collision)

🔁 Play Again / Exit dialog

🌙 Modern dark-themed UI

🛠️ Requirements
Qt 6 or Qt 5 (Widgets module)

C++17 compiler

CMake ≥ 3.14

📦 Build Instructions
Clone the repo
bash
Copy
Edit
git clone https://github.com/Abdul-Rafay2005/snake-qt-game.git
cd snake-qt-game
Build with CMake
bash
Copy
Edit
mkdir build
cd build
cmake ..
make
./SnakeGame
🎮 Controls

Key	Action
↑	Move Up
↓	Move Down
←	Move Left
→	Move Right
📁 Project Structure
objectivec
Copy
Edit
.
├── CMakeLists.txt
├── main.cpp
├── game.h
├── game.cpp
├── build/          
└── README.md
📌 TODO Ideas
 Add main menu with start/pause buttons

 Add sound effects

 Add difficulty/speed levels

 Save high scores

 Touch or mouse control support

💡 Tips
Want to use Qt Creator? Just open the project folder and build using the IDE.

Use Qt5::Widgets in CMakeLists.txt if you're on Qt 5.

📃 License
MIT License — do whatever you want, just credit if you find it useful 🙂
