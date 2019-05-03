struct Tile {
    bool explored; // has the player already seen this tile ?
    unsigned int scent; // amount of player scent on this tile
    Tile() : explored(false),scent(0) {}
};
 
class Map : public Persistent {
public :
    int width,height;
    unsigned int currentScentValue;
    unsigned int getScent(int x, int y) const;
 
    Map(int width, int height);
    virtual ~Map();
    bool isWall(int x, int y) const;
	bool isInFov(int x, int y) const;
    bool isExplored(int x, int y) const;
    bool canWalk(int x, int y) const;
    void computeFov();
    void render() const;

	void load(TCODZip &zip);
	void save(TCODZip &zip);
 	void init(bool withActors);
protected :
    Tile *tiles;
    TCODMap *map;
    long seed;
    TCODRandom *rng;
    friend class BspListener;
 
    void dig(int x1, int y1, int x2, int y2);
    void createRoom(bool first, int x1, int y1, int x2, int y2,bool withActors);
    void addMonster(int x, int y);
    void addItem(int x, int y);
};