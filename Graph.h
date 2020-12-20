#include<iostream>
#include<vector>
#include<unordered_map>
#include<set>
#include<memory>
#include<type_traits>
#include<cassert>
#include<algorithm>


template<class weight_t>
class Graph {
public:
    explicit Graph(weight_t max_value): inf_(max_value) {
        zero_ = weight_t();
    }
    Graph() {
        static_assert(std::is_integral<weight_t>::value, "Integral type required");
        inf_ = std::numeric_limits<weight_t>::max();
        zero_ = weight_t();
    }

    template<class T>
    size_t addVertex(std::shared_ptr<T> v);

    void addEdge(size_t v, size_t w, weight_t weight, bool oriented=true);

    std::pair<weight_t, std::vector<size_t>> shortestPath(size_t v, size_t w);

    template <typename T, typename ResultType, typename ...Args, typename CallbackType = ResultType (*)(std::shared_ptr<T>, Args...)>
    ResultType executeVertex(size_t v, CallbackType f, Args ...args) {
        return f(std::dynamic_pointer_cast<Vertex<T>>(v_map_[v])->holder_, args...);
    }

    void remove(size_t i);


protected:
    class IVertex {
    public:
        explicit IVertex(size_t n): number(n) {};
        const size_t number;
        virtual ~IVertex() = default;
    };

    template<class H>
    class Vertex: public IVertex {
    public:
        using HPtr = std::shared_ptr<H>;
        explicit Vertex(HPtr v, int n): IVertex(n), holder_(v){}
        HPtr holder_;
    };

    weight_t inf_, zero_;
    size_t vertex_index_ = 0;
    std::unordered_map<size_t, std::shared_ptr<IVertex>> v_map_;
    std::unordered_map<size_t, std::vector<std::pair<size_t, weight_t>>> graph_;
    std::set<size_t> indexes_;
};

template<class weight_t, class T>
class SingleTypeGraph: public Graph<weight_t> {
public:
    SingleTypeGraph(): Graph<weight_t>(){};

    SingleTypeGraph(const std::vector<std::shared_ptr<T>>& vertexes, const std::vector<std::vector<weight_t>>& matrix);

    using edges_t = std::vector<std::pair<std::pair<std::shared_ptr<T>, std::shared_ptr<T>>, weight_t>>;
    explicit SingleTypeGraph(const edges_t& edges, bool ordered=false);

    size_t addVertex(std::shared_ptr<T> v) {
        return this->Graph<weight_t>::template addVertex<T>(v);
    };
    template <typename ResultType, typename ...Args, typename CallbackType = ResultType (*)(std::shared_ptr<T>, Args...)>
    ResultType executeVertex(size_t v, CallbackType f, Args ...args) {
        return this->Graph<weight_t>::template executeVertex<T, ResultType, Args...>(v, f, args...);
    }

    template <typename ResultType, typename ...Args, typename CallbackType = ResultType (*)(std::shared_ptr<T>, Args...)>
    std::vector<ResultType> applyAll(CallbackType f, Args ...args) {
        std::vector<ResultType> res;
        for (auto i: this->indexes_) {
            res.push_back(executeVertex<ResultType, Args..., CallbackType>(i->second, f, args...));
        }
        return res;
    }

    template <typename ResultType, typename ...Args, typename CallbackType = ResultType (*)(std::shared_ptr<T>, Args...)>
    std::vector<ResultType> apply(const std::vector<size_t>& vertexes, CallbackType f, Args ...args) {
        std::vector<ResultType> res;
        for (auto i: vertexes) {
            res.push_back(executeVertex<ResultType, Args..., CallbackType>(i, f, args...));
        }
        return res;
    }

    std::pair<size_t, size_t> addVertexes(const std::vector<std::shared_ptr<T>>& vertexes) {
        size_t begin = this->vertex_index_;
        std::for_each(vertexes.begin(), vertexes.end(), [&](auto p) {addVertex(p);});
        return std::make_pair(begin, this->vertex_index_);
    }

    weight_t cost() {
        weight_t ans = 0;
        for (auto v: this->graph_) {
            for (auto e: v.second) {
                ans += e.second;
            }
        }
        return ans;
    }
};

template<class weight_t, class T>
SingleTypeGraph<weight_t, T>::SingleTypeGraph(const std::vector<std::shared_ptr<T>> &vertexes,
                                              const std::vector<std::vector<weight_t>> &matrix): Graph<weight_t>() {
    size_t n = vertexes.size();
    static_assert(n == matrix.size(), "Matrix length and width should match vector length");
    for_each(matrix.begin(), matrix.end(), [&](auto& x) {static_assert(n == x.size(),
                                                                       "Matrix length and width should match vector length");});

    addVertexes(vertexes);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            this->addEdge(i, j, false);
        }
    }

}

template<class weight_t, class T>
SingleTypeGraph<weight_t, T>::SingleTypeGraph(const SingleTypeGraph::edges_t &edges, bool ordered): Graph<weight_t>() {
    std::unordered_map<std::shared_ptr<T>, size_t> vertex2num;
    for(const auto& el: edges) {
        size_t left, right;
        auto it = vertex2num.find(el.first.first);
        if (it == vertex2num.end()) {
            left = this->addVertex(el.first.first);
        } else {
            left = it->second;
        }
        it = vertex2num.find(el.first.second);
        if (it == vertex2num.end()) {
            right = this->addVertex(el.first.second);
        } else {
            right = it->second;
        }
        this->addEdge(left, right, el.second, ordered);
    }
}


template<class weight_t>
template<class T>
size_t Graph<weight_t>::addVertex(std::shared_ptr<T> v) {
    std::shared_ptr<IVertex> ptr(new Vertex<T>(v, vertex_index_));
    v_map_[vertex_index_] = ptr;
    indexes_.insert(vertex_index_);
    return vertex_index_++;
}

template<class weight_t>
void Graph<weight_t>::addEdge(size_t v, size_t w, weight_t weight, bool oriented) {
    graph_[v].emplace_back(w, weight);
    if (!oriented) {
        graph_[w].emplace_back(v, weight);
    }
}

template<class weight_t>
std::pair<weight_t, std::vector<size_t>> Graph<weight_t>::shortestPath(size_t start, size_t finish) {
    size_t n = indexes_.size();
    std::unordered_map<size_t, weight_t> distance, parents;
    std::unordered_map<size_t, bool> used;
    for_each(indexes_.begin(), indexes_.end(),[&](auto ind) {distance[ind] = inf_;});
    distance[start] = zero_;
    for (size_t i = 0; i < n; i++) {
        int v = -1;
        for (auto ind: indexes_) {
            if (!used[ind] && (v == -1 || distance[ind] < distance[v])) {
                v = ind;
            }
        }
        if (distance[v] == inf_) {
            break;
        }
        used[v] = true;

        for (auto& el: graph_[v]) {
            int to = el.first;
            weight_t weight = el.second;
            if (distance[v] + weight < distance[to]) {
                distance[to] = distance[v] + weight;
                parents[to] = v;
            }
        }
    }
    std::vector<size_t> path;
    for (int v=finish; v!=start; v=parents[v])
        path.push_back(v);
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return std::make_pair(distance[finish], path);
}

template<class weight_t>
void Graph<weight_t>::remove(size_t i) {
    auto it_v_map_ = v_map_.find(i);
    if (it_v_map_ != v_map_.end()) {
        v_map_.erase(it_v_map_);
    }

    auto it_indexes_ = indexes_.find(i);
    if (it_indexes_ != indexes_.end()) {
        indexes_.erase(it_indexes_);
    }

    auto it_graph_ = graph_.find(i);
    if (it_graph_ != graph_.end()) {
        graph_.erase(it_graph_);
    }

    for (auto& v: graph_) {
        for (auto it=(v->second).begin(); it != (v->second).end();) {
            if ((*it).first == i) {
                it = (v->second).erase(it);
            } else {
                ++it;
            }
        }
    }
}
