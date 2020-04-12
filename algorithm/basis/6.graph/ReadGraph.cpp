//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/12
//

#include "DenseGraph.h"
#include "SparseGraph.h"
#include "ReadGraph.h"

int main() {
    string filename = "/tmp/testG1.txt";

    SparseGraph g1(13, false);
    (ReadGraph<SparseGraph>(g1, filename));
    g1.show();

    cout << endl;
    DenseGraph g2(13, false);
    (ReadGraph<DenseGraph>(g2, filename));
    g2.show();
}