//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/4
//

#ifndef ALOGORITHM_BINARYSEARCH_H
#define ALOGORITHM_BINARYSEARCH_H

namespace BinarySearch {

    template<typename T>
    bool iterativeSearch(T *haystack, int needle, int length) {
        int left = 0, mid = 0, right = length - 1;
        while (left <= right) {
//            int mid = (left + right) / 2;
            mid = left + (right - left) / 2;
            if (haystack[mid] == needle) {
                return true;
            }
            if (haystack[mid] > needle) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return false;
    }

    template<typename T>
    bool __recursiveSearch(T *haystack, int needle, int left, int right) {
        int mid = left + (right - left) / 2;
        if (left >= right) {
            return false;
        }
        if (haystack[mid] == needle) {
            return true;
        }
        if (haystack[mid] > needle) {
            return __recursiveSearch(haystack, needle, left, mid - 1);
        } else {
            return __recursiveSearch(haystack, needle, mid + 1, right);
        }
    }

    template<typename T>
    bool recursiveSearch(T *haystack, int needle, int length) {
        int left = 0, right = length - 1;
        return __recursiveSearch(haystack, needle, left, right);
    }
};

#endif //ALOGORITHM_BINARYSEARCH_H
