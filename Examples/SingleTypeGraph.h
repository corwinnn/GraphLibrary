#include "Inventory.h"


void singleTypeGraphExample() {
    SingleTypeGraph<int, A> g_from_matrix; // integer edge weights, class A in vertexes
    SingleTypeGraph<int, A> g_from_edges;

    std::shared_ptr<A> p1(new A(1));
    std::shared_ptr<A> p2(new A(2));
    std::shared_ptr<A> p3(new A(3));
    std::shared_ptr<A> p4(new A(4));
    std::shared_ptr<A> p5(new A(5));

    std::vector<std::shared_ptr<A>> vertexes{p1, p2, p3, p4, p5};
    int m = std::numeric_limits<int>::max();
    std::vector<std::vector<int>> matrix{
            {m, 9, m, 4, m},
            {9, m, 4, m, 1},
            {m, 4, m, m, 2},
            {4, m, m, m, 3},
            {m, 1, 2, 3, m}
    };

    using edges_t = std::vector<std::pair<std::pair<std::shared_ptr<A>, std::shared_ptr<A>>, int>>;
    edges_t edges{
            std::make_pair(std::make_pair(p1, p2), 9),
            std::make_pair(std::make_pair(p2, p3), 4),
            std::make_pair(std::make_pair(p1, p4), 4),
            std::make_pair(std::make_pair(p5, p4), 3),
            std::make_pair(std::make_pair(p2, p5), 1),
            std::make_pair(std::make_pair(p3, p5), 2),
    };


    g_from_matrix.constructFromMatrix(vertexes, matrix);
    g_from_edges.constructFromEdges(edges);

    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            assert(g_from_matrix.shortestPath(i, j).first == g_from_edges.shortestPath(i, j).first);

    g_from_edges.applyAll<int, int>([](std::shared_ptr<A> p, int a) {p->foo(a); return 0;},17);
    // I'm A with x, a:1 17
    // I'm A with x, a:2 17
    // I'm A with x, a:3 17
    // I'm A with x, a:4 17
    // I'm A with x, a:5 17
}
