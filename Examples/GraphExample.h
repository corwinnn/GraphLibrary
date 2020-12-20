#include "Inventory.h"

void graphExample() {
    Graph<int> g; // integer edge weights

    std::shared_ptr<A> p1(new A(5));
    std::shared_ptr<B> p2(new B());
    std::shared_ptr<C> p3(new C());
    std::shared_ptr<D> p4(new D());

    g.addVertex<A>(p1); // returns number of vertex in adding order, so we know it has number 0
    g.addVertex<B>(p2); // returns number of vertex in adding order, so we know it has number 1
    g.addVertex<C>(p3); // returns number of vertex in adding order, so we know it has number 2
    g.addVertex<D>(p4); // returns number of vertex in adding order, so we know it has number 3

    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);

    std::cout << g.shortestPath(0, 3).first << std::endl; // 6

    std::cout << g.executeVertex<A, std::string, int>(0,
                                                      [](std::shared_ptr<A> p, int x) {
                                                            std::string s;
                                                            for (int i = 0; i < x; i++) s += "Hi! ";
                                                            s += "\nI'm A with value " + std::to_string(p->x) + "\n";
                                                            return s;
                                                         },
                                                         3) << std::endl;

    // Hi! Hi! Hi!
    // I'm A with value 5

}
