//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/10
//

#ifndef ALGORITHM__151_H
#define ALGORITHM__151_H

#include <algorithm>
#include "deque"
#include "string"
#include "iostream"

using namespace std;

class _151_ReverseWords {

public:
    string reverseWords(string s) {
        int left = 0, right = s.size() - 1;
        // 去掉字符串开头的空白字符
        while (left <= right && s[left] == ' ') ++left;

        // 去掉字符串末尾的空白字符
        while (left <= right && s[right] == ' ') --right;

        deque<string> d;
        string word;

        while (left <= right) {
            char c = s[left];
            if (!word.empty() && c == ' ') {
                // 将单词 push 到队列的头部
                d.push_front(move(word));
                word = "";
            } else if (c != ' ') {
                word += c;
            }
            ++left;
        }
        d.push_front(move(word));

        string ans;
        while (!d.empty()) {
            ans += d.front();
            d.pop_front();
            if (!d.empty()) ans += ' ';
        }
        return ans;
    }
};


#endif //ALGORITHM__151_H
