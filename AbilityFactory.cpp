#include "AbilityFactory.h"

std::shared_ptr<IAbility> AbilityFactory::createAbility(AbilityType type) {
        switch (type) {
            case ::AbilityType::DOUBLE_DAMAGE:
                return std::make_shared<DoubleDamage>();
            case ::AbilityType::SCANNER:
                return std::make_shared<Scanner>();
            case ::AbilityType::DAMAGE:
                return std::make_shared<Damage>();
            default:
                throw std::invalid_argument("Unknown ability type");
        }
}
