#include "Game.h"
#include "GameController.h"
#include "InputHandler.h"
#include "Exceptions.h"
#include "GameState.h"
#include <limits>
#include <random>

Field Game::userField;
Field Game::enemyField;
Manager Game::userManager;
Manager Game::enemyManager;
AbilityManager Game::abilityManager;
int Game::currentRound;


Game::Game() {
    std::cout <<  "Welcome to Sea Fight!" << std::endl;
    std::cout << "Do you want to load the game? (y/n): ";
    char loadOption;
    std::cin >> loadOption;
    if (loadOption == 'y') {
        loadGame();
        startRound();
    } else {
        startGame();
    }
}

void Game::startGame() {
    std::cout << "Let's start the game!:)" << std::endl;
    currentRound = 0;
    setField();
    setNumShips();
    setUserShips();
    enemyField = Field(userField.getWidth(), userField.getHeight());
    enemyManager = Manager(userManager.getNumShips(), userManager.getSizeShips());
    setEnemyShips();
    startRound();
}

void Game::setField() {
    int width, height;
    while (true) {
        std::cout << "Enter the width and height of the field with space:" << std::endl;
            std::cin >> width >> height;
            try {
                userField = Field(width, height);
                break;
            }
            catch (PositiveIntError &e) {
                std::cout << e.what() << "Height and width must be of positive integer type. Try again." << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
    }
}

void Game::setNumShips() {
    int numOfShips, sizeShip;
    int maxNumOfShips = ((userField.getWidth() + userField.getWidth() % 2) / 2) * ((userField.getHeight() + (userField.getHeight() % 2)) / 2);
    while (true) {
        std::cout << "Enter the number of ships:" << std::endl;
        std::cin >> numOfShips;
        try {
            if (numOfShips <= 0 || std::cin.fail()) {
                throw PositiveIntError("Error: The user entered an invalid value for the number of ships.\n");
            }
            if (numOfShips > maxNumOfShips) {
                throw ManyShipsError("Error: The user entered too many ships to place on the board.\n");
            }
            break;
        }
        catch (PositiveIntError &e) {
            std::cout << e.what() << "Please enter a positive integer value. Try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (ManyShipsError &e) {
            std::cout << e.what() << "You have entered too many ships. They do not fit on the field.\nPlease enter a fewer value. Try again." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::vector<int> sizeShips(numOfShips);
    int shipIndex = 0;
    while (shipIndex < numOfShips) {
        std::cout << "Enter the size of ship " << shipIndex+1 << ":" << std::endl;
        std::cin >> sizeShip;
        try {
            if (std::cin.fail() || sizeShip < 1 || sizeShip > 4) {
                throw PositiveIntError("Error: an invalid value for the ship size.\n");
            }
            sizeShips[shipIndex] = sizeShip;
            shipIndex++;
        }
        catch (PositiveIntError &e) {
            std::cout << e.what() << "You entered an invalid value for the ship size. Please use integer from 1 to 4." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    userManager = Manager(numOfShips, sizeShips);
}

void Game::setUserShips() {
    std::cout << "Let's set the ships on the field" << std::endl;
    std::vector <int> coordinates(2);
    int count = 0;
    char orient = 'h';
    while (count < userManager.getNumShips()) {
        std::cout << "If you don't see any space for the ship enter '99' '99' for EXIT." << std::endl;
        std::cout << "Please choose x and y coordinates for ship " << count + 1 << " with space: " << std::endl;
        std::cin >> coordinates[0] >> coordinates[1];
        try {
            if (coordinates[0] == 99 && coordinates[1] == 99) {
                std::cout << "Exiting the program..." << std::endl;
                exit(0);
            }
            else if (userManager.getShip(count).getLength() > 1) {
                std::cout << "Also choose an orientation for this ship: " << std::endl;
                std::cin >> orient;
            }
            userField.setShip(userManager.getShip(count), coordinates, orient);
            count++;
            userField.showField();
        }
        catch (OrientationError &e) {
            std::cout << e.what() << "Please use 'h' for horizontal and 'v' for vertical orientation." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (CoordinatesError &e) {
            std::cout << e.what() << "You entered incorrect coordinates. Please change them and try again" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (ShipError &e) {
            std::cout << e.what() << "You can't put the ship here. Please enter other coordinates" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    std::cout << "All ships were successfully set on the field!" << std::endl;
    userField.showField();
}

void Game::setEnemyShips() {
    int count = 0, attempts = 0, attemptsMax = 20;
    while (count < enemyManager.getNumShips()) {
        std::vector<int> coordinates = getRandomCoordinates();
        char orientation = getRandomOrientation();
        try {
            enemyField.setShip(enemyManager.getShip(count), coordinates, orientation);
            attempts = 0;
            count++;
        }
        catch (ShipError &e) {
            if (attempts >= attemptsMax) {
                enemyManager.reduceShips();
                enemyManager.popSizeShip();
                enemyManager.eraseShip(count);
                count++;
                attempts = 0;
            } else {
                attempts++;
            }
        }
    }
    std::cout << "All enemy's ships were successfully set on the field!" << std::endl;
}

char Game::getRandomOrientation() {
    std::minstd_rand generator;
    generator.seed(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 1);
    return dist(generator) == 0 ? 'h' : 'v';
}

std::vector<int> Game::getRandomCoordinates() {
    std::minstd_rand generator;
    generator.seed(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, userField.getWidth()-1);
    int randomX = dist(generator);
    int randomY = dist(generator);
    return {randomX, randomY};
}

void Game::startRound() {
    currentRound++;
    std::cout << "Starting a new round!" << std::endl << "It's round number: " << currentRound << std::endl;
    while (true) {
        userMove();
        if (enemyManager.getRemainingNumShips() <= 0) {
            std::cout << "Congratulations! You won the round!" << std::endl;
            enemyField = Field(userField.getWidth(), userField.getHeight());
            enemyManager = Manager(userManager.getNumShips(), userManager.getSizeShips());
            setEnemyShips();
            startRound();
            break;
        }
        enemyMove();
        if (userManager.getRemainingNumShips() <= 0) {
            std::cout << "You lost the round! Starting a new game..." << std::endl;
            startGame();
            return;
        }
    }
}

void Game::userMove() {
    if (abilityManager.checkAbility()) {
        std::cout << "Do you want to use an ability? (y/n): ";
        char applyAbility;
        std::cin >> applyAbility;
        if (applyAbility == 'y') {
            try {
                abilityManager.getAbilityFromQueue(enemyField);
                if (enemyField.needsToReduceShips) {
                    enemyField.needsToReduceShips = false;
                    std::cout << "Bonus! You have one more random ability!" << std::endl;
                    abilityManager.addAbility();
                    enemyManager.reduceShips();
                }
            } catch (NoAbilityError &e) {
                std::cout << e.what() << std::endl;
            } catch (CoordinatesError &e) {
                std::cout << e.what()
                          << "You missed your ability. Please enter the correct values next time!"
                          << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        }
    }
    std::vector<int> coordinates(2);
    while (true) {
        std::cout << "Enter coordinates for attack:" << std::endl;
        std::cin >> coordinates[0] >> coordinates[1];
        try {
            if (enemyField.attack(coordinates) == 2 || enemyField.needsToReduceShips) {
                std::cout << "Bonus! You have one more random ability!" << std::endl;
                abilityManager.addAbility();
                enemyManager.reduceShips();
                enemyField.data[coordinates[1]][coordinates[0]] = 0;
                enemyField.needsToReduceShips = false;
            }
            break;
        } catch (CoordinatesError &e) {
            std::cout << e.what() << "You entered incorrect coordinates for attack. Please change them and try again" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    GameState gameState(userField, enemyField, userManager, enemyManager, abilityManager, currentRound);
    GameRenderer<FieldRenderer> gameRenderer(gameState);
    GameController<InputHandler, FieldRenderer> gameController(*this, gameRenderer);
    while (true) {
        if (gameController.processInput()) break;
    }
}



void Game::enemyMove() {
    std::cout << "Enemy's turn!" << std::endl;
    std::vector <int> coordinates = getRandomCoordinates();
    if (userField.attack(coordinates) == 2) {
        userManager.reduceShips();
    }
}

void Game::saveGame() {
    try {
        GameState state(userField, enemyField, userManager, enemyManager, abilityManager, currentRound);
        state.saveToFile("save_game.txt");
        std::cout << "Game saved successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Fail" << e.what() << std::endl;
    }
}

void Game::loadGame() {
    try {
        GameState state(userField, enemyField, userManager, enemyManager, abilityManager, currentRound);
        abilityManager = AbilityManager(false);
        state.loadFromFile("save_game.txt");
        userField = state.userFieldState;
        enemyField = state.enemyFieldState;
        userManager = state.userManagerState;
        enemyManager = state.enemyManagerState;
        abilityManager.setAbilityQueue(state.abilityState);
        currentRound = state.currentRoundState;
    } catch (const std::exception& e) {
        std::cerr << "Failed to load game: " << e.what() << std::endl;
    }
}


