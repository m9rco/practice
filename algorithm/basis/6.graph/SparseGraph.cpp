//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/11
//

#include "SparseGraph.h"
#include "iostream"

int main() {
    int N = 20;
    int M = 100;

    srand(time(nullptr));

    // Sparse Graph
    SparseGraph g1(N, false);
    for (int i = 0; i < M; i++) {
        int a = rand() % N;
        int b = rand() % N;
        g1.addEdge(a, b);
    }

    // O(E)
    for (int v = 0; v < N; v++) {
        cout << v << " : ";
        SparseGraph::adjIterator adj(g1, v);
        for (int w = adj.begin(); !adj.end(); w = adj.next())
            cout << w << " ";
        cout << endl;
    }

    cout << endl;
}