//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/11
//

#ifndef ALGORITHM_DENSEGRAPH_H
#define ALGORITHM_DENSEGRAPH_H

#include "vector"
#include "cassert"

using namespace std;

// 稠密图 - 邻接矩阵
class DenseGraph {
private:
    int vertex, edge;
    bool directed;
    vector<vector<bool>> g;

public:
    DenseGraph(int vertex, bool directed) {
        this->vertex = vertex;
        this->edge = 0;
        this->directed = directed;
        for (int i = 0; i < vertex; i++) {
            g.emplace_back(vertex, false);
        }
    }

    ~DenseGraph() = default;

    int Vertex() { return vertex; }

    int Edge() { return edge; }

    void addEdge(int v, int w) {
        assert(v >= 0 && v < vertex);
        assert(w >= 0 && w < vertex);
        if (hasEdge(v, w)) {
            return;
        }
        g[v][w] = true;
        if (!directed) {
            g[w][v] = true;
        }

        edge++;
    }

    bool hasEdge(int v, int w) {
        assert(v >= 0 && v < vertex);
        assert(w >= 0 && w < vertex);
        return g[v][w];
    }

    class adjIterator {
    private:
        DenseGraph &G;
        int v;
        int index;
    public:
        adjIterator(DenseGraph &graph, int v) : G(graph) {
            this->v = v;
            this->index = -1;
        }

        int begin() {

            index = -1;
            return next();
        }

        int next() {
            for (index += 1; index < G.Vertex(); index++)
                if (G.g[v][index])
                    return index;
            return -1;
        }

        bool end() {
            return index >= G.Vertex();
        }
    };
};


#endif //ALGORITHM_DENSEGRAPH_H
