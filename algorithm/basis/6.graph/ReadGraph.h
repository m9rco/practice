//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/12
//

#ifndef ALGORITHM_READGRAPH_H
#define ALGORITHM_READGRAPH_H


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

template<typename Graph>
class ReadGraph {

public:
    ReadGraph(Graph &graph, const string &filename) {

        ifstream file(filename);
        string line;
        int V, E;

        assert(file.is_open());
        assert(getline(file, line));
        stringstream ss(line);
        ss >> V >> E;

        assert(V == graph.Vertex());

        for (int i = 0; i < E; i++) {

            assert(getline(file, line));
            stringstream ss(line);

            int a, b;
            ss >> a >> b;
            assert(a >= 0 && a < V);
            assert(b >= 0 && b < V);
            graph.addEdge(a, b);
        }
    }
};


#endif //ALGORITHM_READGRAPH_H
