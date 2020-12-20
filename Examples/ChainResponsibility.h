#include "Inventory.h"

class Level {
public:
    explicit Level(int skill, int bonus): skill(skill), bonus(bonus){};
    bool check(int& hero) const {
        if (hero < skill) {
            return false;
        }
        hero += bonus;
        return true;
    }
private:
    int skill;
    int bonus;
};

void chainResponsibility() {

    SingleTypeGraph<int, Level> g;

    std::shared_ptr<Level> p1(new Level(1, 1));
    std::shared_ptr<Level> p2(new Level(2, 1));
    std::shared_ptr<Level> p3(new Level(3, 2));
    std::shared_ptr<Level> p4(new Level(10, 5));
    std::shared_ptr<Level> p5(new Level(17, 2));

    using edges_t = std::vector<std::pair<std::pair<std::shared_ptr<Level>, std::shared_ptr<Level>>, int>>;
    edges_t edges{
            std::make_pair(std::make_pair(p1, p2), 1),
            std::make_pair(std::make_pair(p2, p3), 1),
            std::make_pair(std::make_pair(p3, p4), 1),
            std::make_pair(std::make_pair(p4, p5), 1),
    };

    g.constructFromEdges(edges);

    size_t v = 0, w = 4;
    std::cout << "Level at the end, beginning from 1: " << g.applyChain(v, w, 1,
                                               [](std::shared_ptr<Level> p,
                                                       int& x){return p->check(x);}) << std::endl; // 5

    std::cout << "Level at the end, beginning from 5: " << g.applyChain(v, w, 5,
                                               [](std::shared_ptr<Level> p,
                                                       int& x){return p->check(x);}) << std::endl; // 9

    std::cout << "Level at the end, beginning from 8: " << g.applyChain(v, w, 8,
                                               [](std::shared_ptr<Level> p,
                                                       int& x){return p->check(x);}) << std::endl; // 19
}
