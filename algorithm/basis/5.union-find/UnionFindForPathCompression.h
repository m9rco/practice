//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/11
//

#ifndef ALGORITHM_UNIONFINDFORPATHCOMPRESSION_H
#define ALGORITHM_UNIONFINDFORPATHCOMPRESSION_H

#include "cassert"


class UnionFindForPathCompression {
private:
    int *parent;
    int *rank;
    int count;

public:
    UnionFindForPathCompression(int count) {
        parent = new int[count];
        rank = new int[count];
        this->count = count;
        for (int i = 0; i < count; i++) {
            parent[i] = i;
            rank[i] = 1;
        }
    }

    ~UnionFindForPathCompression() {
        delete[] parent;
        delete[] rank;
    }

    int size() {
        return count;
    }

    bool isConnected(int p, int q) {
        return find(p) == find(q);
    }

    int find(int p) {

        assert(p >= 0 && p < count);

        // path compression 1
        while (p != parent[p]) {
            parent[p] = parent[parent[p]];
            p = parent[p];
        }
        return p;

        // path compression 2
//            if( p != parent[p] )
//                parent[p] = find( parent[p] );
//            return parent[p];
    }

    void unionElements(int p, int q) {

        int pRoot = find(p);
        int qRoot = find(q);

        if (pRoot == qRoot)
            return;

        if (rank[pRoot] < rank[qRoot])
            parent[pRoot] = qRoot;
        else if (rank[qRoot] < rank[pRoot])
            parent[qRoot] = pRoot;
        else { // rank[pRoot] == rank[qRoot]
            parent[pRoot] = qRoot;
            rank[qRoot]++;
        }

    }
};


#endif //ALGORITHM_UNIONFINDFORPATHCOMPRESSION_H
