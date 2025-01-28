cmake_minimum_required(VERSION 3.10)
project(seaFight)

set(CMAKE_CXX_STANDARD 17)

add_executable(seaFight
        main.cpp
        Ship.cpp
        Manager.cpp
        Field.cpp
        AbilityFactory.cpp
        AbilityManager.cpp
        Damage.cpp
        DoubleDamage.cpp
        Scanner.cpp
        Game.cpp
        GameState.cpp
        FileWrapper.cpp
        SaverField.cpp
        SaverManager.cpp
        SaverAbility.cpp
        InputHandler.cpp
        GameController.cpp
        GameRenderer.cpp
        FieldRenderer.cpp
)
