#include "FieldRenderer.h"
#include <iomanip>

void FieldRenderer::render(const GameState& gameState, bool userField) {
    std::cout << std::setw(7) << " ";
    for (size_t j = 0; j < gameState.userFieldState.getWidth(); j++) {
        std::cout << std::setw(4) << j << '.';
    }
    std::cout << std::endl;
    if (userField) {
        for (size_t i = 0; i < gameState.userFieldState.getHeight(); i++) {
            std::cout << std::setw(5) << i << '.';
            for (size_t j = 0; j < gameState.userFieldState.getWidth(); j++) {
                if (!gameState.userFieldState.allPtr[i][j].shipPtr) {
                    std::cout << std::setw(5) << static_cast<char> (CellState::NO_SHIP);
                }
                else {
                    int segIndex = gameState.userFieldState.allPtr[i][j].indSeg;
                    if (gameState.userFieldState.allPtr[i][j].shipPtr->shipBody[segIndex] == SegState::INTACT) {
                        std::cout << std::setw(5) << static_cast<char> (CellState::INTACT);
                    }
                    else if (gameState.userFieldState.allPtr[i][j].shipPtr->shipBody[segIndex] == SegState::DAMAGED) {
                        std::cout << std::setw(5) << static_cast<char> (CellState::DAMAGED);
                    }
                    else {
                        std::cout << std::setw(5) << static_cast<char> (CellState::DESTROYED);
                    }
                }
            }
            std::cout << std::endl;
        }
    }
    else {
        for (size_t i = 0; i < gameState.enemyFieldState.getHeight(); i++) {
            std::cout << std::setw(5) << i << '.';
            for (size_t j = 0; j < gameState.enemyFieldState.getWidth(); j++) {
                if (gameState.enemyFieldState.allPtr[i][j].shipPtr) {
                    int segIndex = gameState.enemyFieldState.allPtr[i][j].indSeg;
                    if (gameState.enemyFieldState.allPtr[i][j].shipPtr->shipBody[segIndex] == SegState::DAMAGED) {
                        std::cout << std::setw(5) << static_cast<char> (CellState::DAMAGED);
                    }
                    else if (gameState.enemyFieldState.allPtr[i][j].shipPtr->shipBody[segIndex] == SegState::DESTROYED) {
                        std::cout << std::setw(5) << static_cast<char> (CellState::DESTROYED);
                    }
                    else {
                        std::cout << std::setw(5) << static_cast<char> (CellState::UNKNOWN);
                    }
                }
                else {
                    if (gameState.enemyFieldState.allPtr[i][j].gotHit) {
                        std::cout << std::setw(5) << static_cast<char> (CellState::NO_SHIP);
                    }
                    else {
                        std::cout << std::setw(5) << static_cast<char> (CellState::UNKNOWN);
                    }
                }
            }
            std::cout << std::endl;
        }
    }
}
