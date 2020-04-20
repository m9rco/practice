//
// @author m9rco
// @date 2020/4/16
//

//#include <cassert>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n, m, p = 0;
    cin >> n >> m;
//    assert(n < 1000);
//    assert(m < 1000);
    int tap[1001], a[1001];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        tap[i] = 0;
    }
    int mm;
    for (int i = 0; i < n; i++) {
        mm = 2147483647;
        for (int j = 0; j < m; j++) {
            if (tap[j] < mm) {
                mm = tap[j];
                p = j;
            }
        }
        tap[p] += a[i];
    }
    mm = 2147483647;
    for (int i = 0; i < m; i++) {
        if (tap[i] < mm) {
            mm = tap[i];
        }
    }
    cout << mm + 1 << endl;
    return 0;
}