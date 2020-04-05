//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/4
//
#include "BinarySearchTree.h"
#include "../../tools.h"
#include <string>

/**
 * 二分搜索树
 *
 * 通常用于一种查找表的结构 （字典）
 *
 *      id|name
 *      ---|---
 *      0|marco
 *      1|jack
 *
 * @return
 */
int main() {
    Tools::testSearchTree("BinarySearchTree", BinarySearchTree<string, int>(), "/tmp/bible.txt", "god");

    BinarySearchTree<int, string> sst = BinarySearchTree<int, string>();
    char as[1];

    for (int i = 32; i <= 126; i++) {
        sprintf(as, "%c", i);
        int *res = reinterpret_cast<int *>(sst.search(i));
        if (res == nullptr) {
            sst.insert(i, as);
        } else {
            (*res)++;
        }
    }

    sst.remove(98);

    cout << "\npreOrder" << endl;
    sst.preOrder();

    cout << "\nmiddleOrder" << endl;
    sst.middleOrder();

    cout << "\npostOrder" << endl;
    sst.postOrder();

    cout << "\nlevelOrder" << endl;
    sst.levelOrder();

    return 0;
}