//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/12
//

#ifndef ALGORITHM_COMPONENTS_H
#define ALGORITHM_COMPONENTS_H


#include <iostream>
#include <cassert>

using namespace std;

template<typename Graph>
class Components {

private:
    Graph &G;
    bool *visited;
    int ccount;
    int *id;

    void dfs(int v) {

        visited[v] = true;
        id[v] = ccount;
        typename Graph::adjIterator adj(G, v);
        for (int i = adj.begin(); !adj.end(); i = adj.next()) {
            if (!visited[i])
                dfs(i);
        }
    }

public:
    Components(Graph &graph) : G(graph) {
        visited = new bool[G.Vertex()];
        id = new int[G.Vertex()];
        ccount = 0;
        for (int i = 0; i < G.Vertex(); i++) {
            visited[i] = false;
            id[i] = -1;
        }

        for (int i = 0; i < G.Vertex(); i++)
            if (!visited[i]) {
                dfs(i);
                ccount++;
            }
    }

    ~Components() {
        delete[] visited;
        delete[] id;
    }

    int count() {
        return ccount;
    }

    bool isConnected(int v, int w) {
        assert(v >= 0 && v < G.V());
        assert(w >= 0 && w < G.V());
        return id[v] == id[w];
    }
};

#endif //ALGORITHM_COMPONENTS_H
