#include "Inventory.h"

void stringEdges() {

    SingleTypeGraph<std::string, int> g("zzzzzzzzzzzzzzzzzzzzzzzzzzzzz");

    std::shared_ptr<int> p1(new int(5));
    std::shared_ptr<int> p2(new int(4));
    std::shared_ptr<int> p3(new int(2));
    std::shared_ptr<int> p4(new int(52));
    std::shared_ptr<int> p5(new int(3));

    using edges_t = std::vector<std::pair<std::pair<std::shared_ptr<int>, std::shared_ptr<int>>, std::string>>;
    edges_t edges{
            std::make_pair(std::make_pair(p1, p2), "a"),
            std::make_pair(std::make_pair(p2, p3), "b"),
            std::make_pair(std::make_pair(p3, p4), "c"),
            std::make_pair(std::make_pair(p4, p5), "d"),
            std::make_pair(std::make_pair(p3, p5), "abrakadabra"),
    };

    g.constructFromEdges(edges);

    std::cout << g.shortestPath(0,4).first << std::endl; // ababrakadabra
}
