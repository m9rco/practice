//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/12
//

#include "Components.h"
#include "DenseGraph.h"
#include "SparseGraph.h"
#include "ReadGraph.h"

int main() {
    string filename = "/tmp/testG1.txt";

    SparseGraph g1(13, false);
    (ReadGraph<SparseGraph>(g1, filename));
    Components<SparseGraph> component1(g1);
    cout << "TestG1.txt, Component Count: " << component1.count() << endl;
    g1.show();

    cout << endl;
    DenseGraph g2(13, false);
    (ReadGraph<DenseGraph>(g2, filename));
    Components<DenseGraph> component2(g2);
    cout << "TestG1.txt, Component Count: " << component2.count() << endl;
    g2.show();
}