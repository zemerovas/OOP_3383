#ifndef SEAFIGHT_GAME_CPP_GAMESTATE_H_
#define SEAFIGHT_GAME_CPP_GAMESTATE_H_

#include "AbilityManager.h"
#include "Field.h"
#include "Manager.h"
#include <string>
#include <utility>

class GameState {
   public:
    GameState(Field&  uf, Field&  ef, Manager& um, Manager& em, AbilityManager& am, int cr);
    GameState() = default;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
    friend std::ostream& operator<<(std::ostream& out, const GameState& state);
    friend std::istream& operator>>(std::istream& in, GameState& state);
    Field userFieldState;
    Field enemyFieldState;
    Manager userManagerState;
    Manager enemyManagerState;
    std::queue<std::shared_ptr<IAbility>>& abilityState;
    int currentRoundState;

};

#endif//SEAFIGHT_GAME_CPP_GAMESTATE_H_
