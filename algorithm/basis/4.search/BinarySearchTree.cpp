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
    return 0;
}