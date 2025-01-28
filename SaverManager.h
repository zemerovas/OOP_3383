#ifndef SEAFIGHT_GAME_CPP_SAVERMANAGER_H_
#define SEAFIGHT_GAME_CPP_SAVERMANAGER_H_
#include "Manager.h"
#include <fstream>

class SaverManager {
   public:
    static void save(std::ostream& out, const Manager& manager);
    static void load(std::istream& in, Manager& manager);
    explicit SaverManager(const Manager& manager);
   private:
    const Manager& manager;
};

#endif//SEAFIGHT_GAME_CPP_SAVERMANAGER_H_
