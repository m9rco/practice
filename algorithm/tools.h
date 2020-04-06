//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/4
//

#ifndef ALOGORITHM_TOOLS_H
#define ALOGORITHM_TOOLS_H

#include <iostream>
#include <ctime>
#include <cassert>
#include <sstream>
#include <vector>
#include <fstream>

using namespace std;

namespace FileOps {
    int firstCharacterIndex(const string &s, int start) {
        for (int i = start; i < s.length(); i++)
            if (isalpha(s[i]))
                return i;
        return s.length();
    }

    string lowerS(const string &s) {

        string ret = "";
        for (int i = 0; i < s.length(); i++)
            ret += tolower(s[i]);
        return ret;
    }

    bool readFile(const string &filename, vector<string> &words) {
        string line;
        string contents = "";
        ifstream file(filename);
        if (file.is_open()) {
            while (getline(file, line))
                contents += (line + "\n");
            file.close();
        } else {
            cout << "Can not open " << filename << " !!!" << endl;
            return false;
        }

        int start = firstCharacterIndex(contents, 0);
        for (int i = start + 1; i <= contents.length();) {

            if (i == contents.length() || !isalpha(contents[i])) {
                words.push_back(lowerS(contents.substr(start, i - start)));
                start = firstCharacterIndex(contents, i);
                i = start + 1;
            } else {
                i++;
            }
        }

        return true;
    }
}
namespace Tools {

    int *generateRandomArray(int n, int rangeL, int rangeR) {
        assert(rangeL <= rangeR);
        int *arr = new int[n];
        srand((unsigned) time(nullptr));
        for (int i = 0; i < n; ++i) {
            arr[i] = (int) random() % (rangeR - rangeL + 1) + rangeL;
        }
        return arr;
    }

    template<typename T>
    void printArray(T arr[], int n) {
        for (int i = 0; i < n; ++i) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    template<typename T>
    bool isSorted(T arr[], int n) {
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                return false;
            }
        }
        return true;
    }

    template<typename T>
    void testSort(const string &sortName, void (*sort)(T[], int), T arr[], int n) {
        clock_t startTime = clock();
        sort(arr, n);
        clock_t endTime = clock();
        assert(isSorted(arr, n));
        cout << "\n♻️ " << sortName << " ♻️\n"
             << "───────|───────"
             << "\nspeed  │ " << double(endTime - startTime) / CLOCKS_PER_SEC << "s"
             << "\nnum    │ " << n << ""
             << endl;
        return;
    }

    template<typename T>
    void testSearch(const string &searchName, bool (*search)(T[], int, int), T *arr, int needle, int length) {
        clock_t startTime = clock();
        ostringstream result;
        result << search(arr, needle, length);
        clock_t endTime = clock();
        cout << searchName << " : " << double(endTime - startTime) / CLOCKS_PER_SEC << " s" <<
             " [searched: " << string(result.str()) << "] " << "[needle: " << needle << "]" << endl;
        return;
    }

    template<class searchTree, typename Key>
    void testSearchTree(const string &searchName, searchTree sst, string filename, Key needle) {
        vector<string> words;
        if (FileOps::readFile(filename, words)) {
            clock_t startTime = clock();
            sst = searchTree();
            for (auto &word : words) {
                int *res = sst.search(word);
                if (res == nullptr) {
                    sst.insert(word, 1);
                } else {
                    (*res)++;
                }
            }
            clock_t endTime = clock();
            cout << "\n♻️ " << searchName << " ♻️\n"
                 << "───────|───────"
                 << "\nspeed  │ " << double(endTime - startTime) / CLOCKS_PER_SEC << "s"
                 << "\nneedle │ " << needle << ""
                 << "\nnum    │ " << *sst.search(needle) << ""
                 << endl;
        }
        return;
    }

    int *generateOrderedArray(int n) {
        int *arr = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = i;
        }
        return arr;
    }

    int *generateNearlyOrderedArray(int n, int swapTimes) {
        int *arr = new int[n];
        for (int i = 0; i < n; i++)
            arr[i] = i;

        srand(time(NULL));
        for (int i = 0; i < swapTimes; i++) {
            int posx = rand() % n;
            int posy = rand() % n;
            swap(arr[posx], arr[posy]);
        }

        return arr;
    }


    int *copyIntArray(int a[], int n) {
        int *arr = new int[n];
        copy(a, a + n, arr);
        return arr;
    }
};


#endif //ALOGORITHM_TOOLS_H
