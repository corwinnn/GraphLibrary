# GraphLibrary
GraphLibrary - библиотека для создания графов, у которых вершинами могут являться сложные классы, а весами ребер выступать аддитивные линейно упорядоченные классы.

## class Graph<weight_t>
Общий класс для графов с разными типами вершин. weight_t - тип весов ребер.

### Graph()
Конструктор без параметров. Работает только для [интегральных](https://en.cppreference.com/w/cpp/types/is_integral) классов. Внутри конструктора инициализируется 0 типа(дефолтный конструктор weight_t) и максимум типа из numeric_limits.

### Graph(weight_t max_value)
Работает для всех типов, передается максимум типа(значение, превышающее вес любого пути в графе) как параметр.

### size_t addVertex(std::shared_ptr<T> v)
Добавляет в граф вершину, возвращает ее номер. Номера выдаются в порядке добавления.

### void addEdge(size_t v, size_t w, weight_t weight, bool oriented=true)
Добавляет в граф ребро между вершинами v и w(должны быть добавлены ранее в граф) с весом weight.

### void remove(size_t i)
Удаляет вершину и все связанные с ней ребра.

### ResultType executeVertex(size_t v, CallbackType f, Args ...args)
Применяет функцию f(std::shared_ptr<T>, Args...) к объекту класса в вершине. Функция обязана первым аргументом иметь std::shared_ptr<T>.


### Пример использования класса:
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
