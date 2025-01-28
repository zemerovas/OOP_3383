#ifndef SEAFIGHT_CONTROLLERS_CPP_RENDERER_H_
#define SEAFIGHT_CONTROLLERS_CPP_RENDERER_H_

#include "Game.h"
#include "FieldRenderer.h"

template <typename RenderType>
class GameRenderer {
   public:
    const GameState& gameState;
    RenderType rendererType;

    explicit GameRenderer(const GameState& gameState) : gameState(gameState) {}

    void render(bool isUserField) {
        rendererType.render(gameState, isUserField);
    }
};

#endif//SEAFIGHT_CONTROLLERS_CPP_RENDERER_H_
