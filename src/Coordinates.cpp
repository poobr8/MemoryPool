// Utility class to be used for testing MemoryPool
// This class should hold 8 bytes of memory since there are two integers
class Coordinates {
private:
    int x;
    int y;
public:
    Coordinates() = default;

    Coordinates(int x, int y) {
        this->x = x;
        this->y = y;
    }

    ~Coordinates() = default;

    int getX() {
        return x;
    }

    int getY() {
        return y;
    }

    void setX(int x) {
        this->x = x;
    }

    void setY(int y) {
        this->y = y;
    }
};
