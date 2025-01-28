#include "Scanner.h"
#include "Exceptions.h"

void Scanner::useAbility(Field &field) {
    std::cout << "Current type of attack is SCANNER!" << std::endl;
    std::cout << "Enter the coordinates for ability:" << std::endl;
    std::vector<size_t> coordinates(2);
    std::cin >> coordinates[0] >> coordinates[1];
    if (coordinates[0] < 0 || coordinates[1] < 0 || coordinates[0] >= field.getWidth() || coordinates[1] >= field.getHeight() || std::cin.fail()) {
        throw CoordinatesError("Error: Incorrect coordinates.");
    }
    int flag = 0;
    for (size_t i = coordinates[1]; i < coordinates[1] + 2; i++) {
        for (size_t j = coordinates[0]; j < coordinates[0] + 2; j++) {
            if (i >= field.getHeight() || j >= field.getWidth()) {
                continue;
            }
            if (field.data[i][j]) {
                flag = 1;
                break;
            }
        }
    }
    if (!flag) {
        std::cout << "There is no any ship in this area." << std::endl;
    } else {
        std::cout << "You are lucky! There is a ship here!" << std::endl;
    }
}

AbilityType Scanner::getType() const {
    return AbilityType::SCANNER;
}
