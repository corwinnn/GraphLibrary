#include "Inventory.h"

class Star {
public:
    explicit Star(int beauty): beauty(beauty){};
    int getCost() const {
        return beauty;
    }
    int beauty;
};

void composite() {

    SuperGraph<int> orionConstellation;
    SuperGraph<int> geminiConstellation;
    SuperGraph<int> leoConstellation;
    SuperGraph<int> cassiopeiaConstellation;

    orionConstellation.addVertex<Star>(std::shared_ptr<Star> (new Star(1)));
    orionConstellation.addVertex<Star>(std::shared_ptr<Star> (new Star(2)));
    orionConstellation.addVertex<Star>(std::shared_ptr<Star> (new Star(13)));
    orionConstellation.addVertex<Star>(std::shared_ptr<Star> (new Star(5)));
    orionConstellation.addVertex<Star>(std::shared_ptr<Star> (new Star(17)));

    geminiConstellation.addVertex<Star>(std::shared_ptr<Star> (new Star(1)));
    geminiConstellation.addVertex<Star>(std::shared_ptr<Star> (new Star(2)));

    leoConstellation.addVertex<Star>(std::shared_ptr<Star> (new Star(1)));
    leoConstellation.addVertex<Star>(std::shared_ptr<Star> (new Star(8)));
    leoConstellation.addVertex<Star>(std::shared_ptr<Star> (new Star(11)));

    cassiopeiaConstellation.addVertex<Star>(std::shared_ptr<Star> (new Star(1)));
    cassiopeiaConstellation.addVertex<Star>(std::shared_ptr<Star> (new Star(4)));

    SuperGraph<int> milkyWayGalaxy;
    SuperGraph<int> andromedaGalaxy;

    milkyWayGalaxy.addVertex<SuperGraph<int>>(std::make_shared<SuperGraph<int>>(orionConstellation));
    milkyWayGalaxy.addVertex<SuperGraph<int>>(std::make_shared<SuperGraph<int>>(geminiConstellation));

    andromedaGalaxy.addVertex<SuperGraph<int>>(std::make_shared<SuperGraph<int>>(leoConstellation));
    andromedaGalaxy.addVertex<SuperGraph<int>>(std::make_shared<SuperGraph<int>>(cassiopeiaConstellation));

    SuperGraph<int> Universe;

    Universe.addVertex<SuperGraph<int>>(std::make_shared<SuperGraph<int>>(milkyWayGalaxy));
    Universe.addVertex<SuperGraph<int>>(std::make_shared<SuperGraph<int>>(andromedaGalaxy));

    std::cout << "Universe beauty: " << Universe.getCost() << std::endl; // 66
}
