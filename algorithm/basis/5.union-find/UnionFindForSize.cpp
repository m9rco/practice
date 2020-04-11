//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/11
//

#include "UnionFindForSize.h"
#include "../../tools.h"

int main() {
    int n = 100000;

    Tools::testUnionFind("union find for size", UnionFindSize(n), n);
    return 0;
}