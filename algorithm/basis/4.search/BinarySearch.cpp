//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/4
//

#include "BinarySearch.h"
#include "../../tools.h"

int main() {
    int length = 10000000;
    int *arr = Tools::generateOrderedArray(length);

    Tools::testSearch("iterativeSearch", BinarySearch::iterativeSearch, arr, 777, length);
    Tools::testSearch("recursiveSearch", BinarySearch::recursiveSearch, arr, 777, length);
    delete (arr);
    return 0;
}