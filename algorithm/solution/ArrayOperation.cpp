//
// @author m9rco
// @date 2020/4/17
//


//#include <algorithm>
#include <iostream>
#include <cassert>

using namespace std;

int main() {
    unsigned short t;
    cin >> t;
    assert(1 <= t && t <= 1000);
    while (t--) {
        unsigned short n;
        cin >> n;
        assert(1 <= n && n <= 100);
        int l = 0, r = 0, res = 0;
        for (int i = 0; i < n; i++) {
            int an;
            cin >> an;
            assert(1 <= an && an <= 1e9);
            if (an % 3 == 0) {
                res++;
            } else if (an % 3 == 1) {
                l++;
            } else {
                r++;
            }
        }
        if (l <= r) {
            res += l;
            r -= l;
            res += r / 3;
        } else {
            res += r;
            l -= r;
            res += l / 3;
        }
        cout << res << endl;
    }
    return 0;
}

