//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/11
//

#include "DenseGraph.h"
#include "iostream"

int main() {
    int N = 20;
    int M = 100;

    srand(time(nullptr));
    // Dense Graph
    DenseGraph g2(N, false);
    for (int i = 0; i < M; i++) {
        int a = rand() % N;
        int b = rand() % N;
        g2.addEdge(a, b);
    }

    // O(V^2)
    for (int v = 0; v < N; v++) {
        cout << v << " : ";
        DenseGraph::adjIterator adj(g2, v);
        for (int w = adj.begin(); !adj.end(); w = adj.next())
            cout << w << " ";
        cout << endl;
    }
}