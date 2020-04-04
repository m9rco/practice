//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/5
//

#include "SequenceSearchTree.h"
#include "BinarySearchTree.h"
#include "../../tools.h"


int main() {
    Tools::testSearchTree("BinarySearchTree", BinarySearchTree<string, int>(), "/tmp/bible.txt", "god");
    Tools::testSearchTree("SequenceST", SequenceST<string, int>(), "/tmp/bible.txt", "god");
    return 0;
}