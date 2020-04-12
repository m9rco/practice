//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/11
//

#ifndef ALGORITHM_SPARSEGRAPH_H
#define ALGORITHM_SPARSEGRAPH_H

#include "vector"
#include "cassert"

using namespace std;

// 稀疏图 - 邻接表
class SparseGraph {
private:
    int vertex, edge;
    bool directed;
    vector<vector<int>> g;

public:
    SparseGraph(int n, bool directed) {
        this->vertex = n;
        this->edge = 0;
        this->directed = directed;
        for (int i = 0; i < n; i++) {
            g.emplace_back();
        }
    }

    ~SparseGraph() = default;

    int Vertex() { return vertex; }

    int Edge() { return edge; }

    void addEdge(int v, int w) {
        assert(v >= 0 && v < vertex);
        assert(w >= 0 && w < vertex);

        g[v].push_back(w);
        if (v != w && !directed)
            g[w].push_back(v);

        edge++;
    }

    bool hasEdge(int v, int w) {

        assert(v >= 0 && v < vertex);
        assert(w >= 0 && w < vertex);

        for (int i : g[v]) {
            if (i == w) return true;
        }
        return false;
    }

    class adjIterator {
    private:
        SparseGraph &G;
        int v;
        int index;
    public:
        adjIterator(SparseGraph &graph, int v) : G(graph) {
            this->v = v;
            this->index = 0;
        }

        int begin() {
            index = 0;
            if (G.g[v].size())
                return G.g[v][index];
            return -1;
        }

        int next() {
            index++;
            if (index < G.g[v].size())
                return G.g[v][index];
            return -1;
        }

        bool end() {
            return index >= G.g[v].size();
        }
    };
};


#endif //ALGORITHM_SPARSEGRAPH_H
