#ifndef SEAFIGHT__GAME_H_
#define SEAFIGHT__GAME_H_

#include "Field.h"
#include "Manager.h"
#include "AbilityManager.h"

class Game {
   public:
    Game();
    void startGame();
    static void saveGame();
    static void loadGame();

   private:
    static Field userField;
    static Field enemyField;
    static Manager userManager;
    static Manager enemyManager;
    static AbilityManager abilityManager;
    static int currentRound;

    void startRound();
    void setField();
    void setUserShips();
    void setEnemyShips();
    void setNumShips();
    static char getRandomOrientation();
    std::vector<int> getRandomCoordinates();
    void userMove();
    void enemyMove();

};

#endif//SEAFIGHT__GAME_H_
