#ifndef SEAFIGHT_GAME_CPP_SAVERFIELD_H_
#define SEAFIGHT_GAME_CPP_SAVERFIELD_H_

#include "Field.h"
#include <fstream>

class SaverField {
   public:
    static void save(std::ostream& out, const Field& field);
    static void load(std::istream& in, Field& field);
    explicit SaverField(const Field& field);
   private:
    const Field& field;
};


#endif//SEAFIGHT_GAME_CPP_SAVERFIELD_H_
