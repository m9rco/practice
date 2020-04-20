//
// @author m9rco
// @date 2020/4/16
//

#include <algorithm>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

int main() {
    unsigned short T;
    cin >> T;
    assert(1 <= T && T <= 10);
    while (T--) {
        unsigned int N, K;
        cin >> N >> K;

        assert(1 <= N && N <= 500);
        assert(1 <= K && K <= 10);
        assert(1 <= K && K <= N);

        unsigned int Kb[K];
        int i = 0;
        cin >> Kb[i++];

        while (getchar() != '\n') {
            cin >> Kb[i++];
        }
        unsigned int M;
        cin >> M;

        assert(0 <= M && M <= 3000);
        while (M--) {
            unsigned int a, b;
            cin >> a >> b;
            vector<unsigned long> Nt;
        }
    }
}

