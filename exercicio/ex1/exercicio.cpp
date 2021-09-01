#include <memory>
#include <iostream>

class Coord {
    private:
        int x, y;
    
    public:
        /**
         * Coordinate object
         *
         * @param new_x - x value coordinate
         * @param new_y - y value coordinate
         */
        Coord(int new_x, int new_y) {
            x = new_x;
            y = new_y;
        }
};

class Cube {
    private:
        int x, y, z;
    public:
        /**
         * Cube object
         *
         * @param new_x - x value length
         * @param new_y - y value length
         * @param new_z - z value length
         */
        Cube(int new_x, int new_y, int new_z) {
            x = new_x;
            y = new_y;
            z = new_z;
        }
        
        /**
         * Prints volume
         *
         * @returns volume
         */
        int printVolume() {
            int volume = x * y * z;
            std::cout << volume << "\n";
            return volume;
        }

};

/**
 * Main class
 */
int main() {
    std::unique_ptr<Coord> coord (new Coord(50, 10));
    std::unique_ptr<Cube> cube (new Cube(10, 20, 30));
    
    cube->printVolume();

    return 0;
}
