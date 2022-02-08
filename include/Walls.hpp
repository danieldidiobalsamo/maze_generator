#ifndef WALLS_HPP
#define WALLS_HPP

class Walls {
private:
    bool _westWall;
    bool _eastWall;
    bool _northWall;
    bool _southWall;

public:
    Walls();
    Walls(const bool built);
    ~Walls();

    bool hasWestWall();
    bool hasEastWall();
    bool hasNorthWall();
    bool hasSouthWall();

    void setWestWall(const bool built);
    void setEastWall(const bool built);
    void setNorthWall(const bool built);
    void setSouthWall(const bool built);
};

#endif