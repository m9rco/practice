//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/11
//

#ifndef ALGORITHM_UNIONFINDSIZE_H
#define ALGORITHM_UNIONFINDSIZE_H

#include "cassert"

class UnionFindSize {
private:
    int *parent;
    int *sz; // sz[i]表示以i为根的集合中元素个数
    int count;

public:
    UnionFindSize(int count) {
        parent = new int[count];
        sz = new int[count];
        this->count = count;
        for (int i = 0; i < count; i++) {
            parent[i] = i;
            sz[i] = 1;
        }
    }

    ~UnionFindSize() {
        delete[] parent;
        delete[] sz;
    }

    int size() {
        return count;
    }

    bool isConnected(int p, int q) {
        return find(p) == find(q);
    }

    int find(int p) {
        assert(p >= 0 && p < count);
        while (p != parent[p])
            p = parent[p];
        return p;
    }

    void unionElements(int p, int q) {
        int pRoot = find(p);
        int qRoot = find(q);

        if (pRoot == qRoot)
            return;

        if (sz[pRoot] < sz[qRoot]) {
            parent[pRoot] = qRoot;
            sz[qRoot] += sz[pRoot];
        } else {   // sz[pRoot] >= sz[qRoot]
            parent[qRoot] = pRoot;
            sz[pRoot] += sz[qRoot];
        }
    }
};


#endif //ALGORITHM_UNIONFINDSIZE_H
