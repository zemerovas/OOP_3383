#include "GameState.h"
#include "FileWrapper.h"
#include "SaverField.h"
#include "SaverManager.h"
#include "SaverAbility.h"

std::istream &operator>>(std::istream &in, GameState &state) {
    in >> state.currentRoundState;
    SaverField::load(in, state.userFieldState);
    SaverField::load(in, state.enemyFieldState);
    SaverManager::load(in, state.userManagerState);
    SaverManager::load(in, state.enemyManagerState);
    SaverAbility::load(in, state.abilityState);
    return in;
}

std::ostream &operator<<(std::ostream &out, const GameState &state) {
    out << state.currentRoundState << std::endl;
    SaverField::save(out, state.userFieldState);
    SaverField::save(out, state.enemyFieldState);
    SaverManager::save(out, state.userManagerState);
    SaverManager::save(out, state.enemyManagerState);
    auto abilityQueueCopy = state.abilityState;
    SaverAbility::save(out, abilityQueueCopy);
    return out;
}

GameState::GameState(Field& uf, Field&  ef, Manager& um, Manager& em, AbilityManager& am, int cr)
    : userFieldState(uf), enemyFieldState(ef), userManagerState(um), enemyManagerState(em), abilityState(am.getAbilityQueue()), currentRoundState(cr) {}

void GameState::saveToFile(const std::string &filename) const {
    try {
        FileWrapper fileWrapper(filename, std::ios::out | std::ios::binary);
        std::fstream& file = fileWrapper.get();
        file << *this;
        std::cout << "Game successfully saved to " << filename << std::endl;
    } catch (const std::exception& e) {
    std::cerr << "Failed to save game: " << e.what() << std::endl;
    throw;
    }
}

void GameState::loadFromFile(const std::string &filename) {
    try {
        FileWrapper fileWrapper(filename, std::ios::in);
        std::fstream& file = fileWrapper.get();
        file >> *this;
        std::cout << "Game successfully loaded from " << filename << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Failed to load game: " << e.what() << std::endl;
    }
}
