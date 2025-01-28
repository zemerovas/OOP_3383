#include "SaverField.h"
#include <sstream>

void SaverField::save(std::ostream& out, const Field& field) {
    out << field.getWidth() << " " << field.getHeight() << std::endl;
    int countShips = 0;
    for (int i = 0; i < field.getHeight(); ++i) {
        for (int j = 0; j < field.getWidth(); ++j) {
            const Cell& cell = field.allPtr[i][j];
            if (cell.shipPtr != nullptr) {
                countShips++;
                out << i << " " << j << " ";
                const Ship& ship = *(cell.shipPtr);
                out << ship.getLength() << " " << ship.getIntOrient() << " ";
                out << static_cast<int>(ship.shipBody[cell.indSeg]) << " ";
                out << cell.indSeg << " ";
                out << static_cast<int> (cell.gotHit);
                out << std::endl;
            }
        }
    }
    out << "__FIELD_END__" << std::endl;
}


void SaverField::load(std::istream& in, Field& field) {
    int width, height;
    in >> width >> height;
    field = Field(width, height);
    int y, x, shipLength, shipIntOrient, segState, indSeg, gotHit;
    std::string line;
    std::getline(in, line);
    while (line != "__FIELD_END__") {
        std::istringstream iss(line);
        while (iss >> y >> x >> shipLength >> shipIntOrient >> segState >> indSeg >> gotHit) {
            Orientation shipOrient = (shipIntOrient == 0) ? Orientation::HORIZONTAL : Orientation::VERTICAL;
            Ship* ship = new Ship(shipLength, shipOrient);
            ship->shipBody[indSeg] = static_cast<SegState>(segState);
            Cell& cell = field.allPtr[y][x];
            cell.indSeg = indSeg;
            cell.shipPtr = ship;
            field.data[y][x] = 1;
            cell.gotHit = static_cast<bool>(gotHit);
        }
        std::getline(in, line);
    }
}


SaverField::SaverField(const Field &field) : field(field) {}
