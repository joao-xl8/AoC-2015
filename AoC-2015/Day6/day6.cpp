#include "day6.hpp"
void executeDay6Puzzle() {
    PuzzleSolverDay6 ps{};
    ps.loadInstructions();
    std::cout << ps.resolveSumOfLights() << std::endl;
}
