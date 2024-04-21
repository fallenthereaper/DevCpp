# CMakeList.txt : CMake project for main, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.19.2)

project (main)
set(CMAKE_CXX_STANDARD 17)
add_executable ("main" "src/main.cpp" "src/bank/bank_account.cpp" "src/practice.cpp" "src/practice.h" "src/tictac_game.cpp" "src/tictac_game.h" "src/GameGrid.h" "src/GameGrid.cpp")



# TODO: Add tests and install targets if needed.
