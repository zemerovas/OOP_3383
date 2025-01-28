#include "FileWrapper.h"

FileWrapper::FileWrapper(const std::string& filename, std::ios::openmode mode) {
    file.open(filename, mode);
    if (!file) {
        throw std::ios_base::failure("Error: Could not open file " + filename);
    }
}

FileWrapper::~FileWrapper() {
    if (file.is_open()) {
        file.close();
    }
}

std::fstream& FileWrapper::get() {
    return file;
}
