#ifndef SEAFIGHT_CONTROLLERS_CPP_GAMECONTROLLER_H_
#define SEAFIGHT_CONTROLLERS_CPP_GAMECONTROLLER_H_

#include "Game.h"
#include "InputHandler.h"
#include "GameRenderer.h"

template<typename InputHandler, typename RenderType>
class GameController {
   private:
    Game& game;
    GameRenderer<RenderType>& gameRenderer;
    InputHandler inputHandler;
   public:
    GameController(Game& game, GameRenderer<RenderType>& gameRenderer)
        : game(game), gameRenderer(gameRenderer) {}

    int processInput() {
        auto command = inputHandler.getCommand();
        switch (command) {
            case CommandType::LOAD:
                game.loadGame();
                return 1;
            case CommandType::SAVE:
                game.saveGame();
                break;
            case CommandType::USER_FIELD:
                gameRenderer.render(true);
                break;
            case CommandType::ENEMY_FIELD:
                gameRenderer.render(false);
                break;
            case CommandType::CONTINUE:
                std::cout << "Continuation of the game." << std::endl;
                return 1;
            case CommandType::HELP:
                inputHandler.help();
                break;
            case CommandType::QUIT:
                std::cout << "EXITING..." << std::endl;
                exit(0);
            default:
                std::cout << "Unknown command\n";
        }
        return 0;
    }
};


#endif//SEAFIGHT_CONTROLLERS_CPP_GAMECONTROLLER_H_ 
