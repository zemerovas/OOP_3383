#ifndef SEAFIGHT_GAME_CPP_FILEWRAPPER_H_
#define SEAFIGHT_GAME_CPP_FILEWRAPPER_H_
#include <iostream>
#include <fstream>

class FileWrapper {
   private:
    std::fstream file;
   public:
    FileWrapper(const std::string& filename, std::ios::openmode mode);
    ~FileWrapper();
    std::fstream& get();
};

#endif//SEAFIGHT_GAME_CPP_FILEWRAPPER_H_
