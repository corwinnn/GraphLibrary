# GraphLibrary
GraphLibrary - библиотека для создания графов, у которых вершинами могут являться сложные классы, а весами ребер выступать аддитивные линейно упорядоченные классы.

## ```class Graph<weight_t>```
Общий класс для графов с разными типами вершин. weight_t - тип весов ребер.

### ```Graph()```
Конструктор без параметров. Работает только для [интегральных](https://en.cppreference.com/w/cpp/types/is_integral) типов весов ребер. Внутри конструктора инициализируется 0 данного типа(дефолтный конструктор weight_t) и максимум типа из numeric_limits.

### ```Graph(weight_t max_value)```
Работает для всех типов, передается максимум типа(значение, превышающее вес любого пути в графе) как параметр. 

### ```size_t addVertex(std::shared_ptr<T> v)```
Добавляет в граф вершину, возвращает ее номер. Номера выдаются в порядке добавления.

### ```void addEdge(size_t v, size_t w, weight_t weight, bool oriented=true)```
Добавляет в граф ребро между вершинами v и w(вершины должны быть предварительно добавлены в граф) с весом weight.

### ```void remove(size_t i)```
Удаляет вершину и все связанные с ней ребра.

### ```ResultType executeVertex(size_t v, CallbackType f, Args ...args)```
Применяет функцию f(std::shared_ptr<T>, Args...) к объекту класса в вершине. Функция обязана первым аргументом иметь std::shared_ptr<T>.


### [Пример](Examples/GraphExample.h) использования класса:
```c++
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
```

## ```class SingleTypeGraph<weight_t, T>```
Класс для графов с одинаковыми типами вершин. weight_t - тип весов ребер, T - тип вершин графа. Является наследником ```Graph```.

### ```void constructFromMatrix(const std::vector<std::shared_ptr<T>>& vertexes, const std::vector<std::vector<weight_t>>& matrix)```
Инициализирует вершины и ребра по матрице смежности. Чтобы отметить отсутствие ребра, нужно указать в качестве веса максимальный вес для ребер в матрице.

### ```void constructFromEdges(const edges_t& edges, bool oriented=false)```
Инициализирует вершины и ребра по списку ребер.

### ```std::vector<ResultType> applyAll(CallbackType f, Args ...args)```
Требования аналогичны требованиям ```executeVertex``` базового класса. Итерация по всем вершинам с выполнением действия.

### ```std::vector<ResultType> apply(const std::vector<size_t>& vertexes, CallbackType f, Args ...args)```
Аналогично предыдущему методу, но применение только к выбранным вершинам.

### ```std::pair<size_t, size_t> addVertexes(const std::vector<std::shared_ptr<T>>& vertexes)```
Добавление вектора вершин. Возвращает номер начала и конца(не включая) индексации новых вершин.

### ```ResultType applyChain(size_t start, size_t finish,  ResultType start_value, CallbackType f, Args ...args)```
Применение действий по цепочке, изменяя результат в каждой вершине. Берется цепочка вершин кратчайшего пути между ```start``` и ```финиш```.
По цепочке применяется функция сигнатуры ```std::shared_ptr<T>, ResultType&, Args...``` -> ```bool```, которая может изменять внутри себя переданный параметр.
Когда функция возвращает ```false```, цепочка возвращает текущий результат


### [Пример](Examples/SingleTypeGraphExample.h) использования класса:
```c++
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
```


### [Пример](Examples/ChainResponsibility.h) использования цепочки ответственности:
```c++
class Level {
public:
    explicit Level(int level, int bonus): level(level), bonus(bonus){};
    bool check(int& hero) const {
        if (hero < level) {
            return false;
        }
        hero += bonus;
        return true;
    }
private:
    int level;
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
```




