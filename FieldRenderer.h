#ifndef SEAFIGHT_CONTROLLERS_CPP_FIELDRENDERER_H_
#define SEAFIGHT_CONTROLLERS_CPP_FIELDRENDERER_H_
#include "GameState.h"

enum class CellState{
    NO_SHIP = '~',
    DESTROYED = '0',
    DAMAGED = '1',
    INTACT = '2',
    UNKNOWN = '?'
};

class FieldRenderer {
   public:
    static void render(const GameState& gameState, bool userField);
};

#endif//SEAFIGHT_CONTROLLERS_CPP_FIELDRENDERER_H_
