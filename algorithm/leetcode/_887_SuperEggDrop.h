//
// @author m9rco
// @email <pushaowei0727@gmail.com>
// @date 2020/4/11
//

#ifndef ALGORITHM__887_SUPEREGGDROP_H
#define ALGORITHM__887_SUPEREGGDROP_H

#include "unordered_map"
#include "algorithm"
#include "vector"

using namespace std;

class _887_SuperEggDrop {
private:
    unordered_map<int, int> memo;

public:
    int superEggDrop(int K, int N) {
        if (memo.find(N * 100 + K) == memo.end()) {
            int ans;
            if (N == 0) ans = 0;
            else if (K == 1) ans = N;
            else {
                int lo = 1, hi = N;
                while (lo + 1 < hi) {
                    int x = (lo + hi) / 2;
                    int t1 = superEggDrop(K - 1, x - 1);
                    int t2 = superEggDrop(K, N - x);

                    if (t1 < t2) lo = x;
                    else if (t1 > t2) hi = x;
                    else lo = hi = x;
                }

                ans = 1 + min(max(superEggDrop(K - 1, lo - 1), superEggDrop(K, N - lo)),
                              max(superEggDrop(K - 1, hi - 1), superEggDrop(K, N - hi)));
            }

            memo[N * 100 + K] = ans;
        }

        return memo[N * 100 + K];
    }

    int superEggDrop2(int K, int N) {
        if (N == 1) {
            return 1;
        }
        vector<vector<int>> f(N + 1, vector<int>(K + 1));
        for (int i = 1; i <= K; ++i) {
            f[1][i] = 1;
        }
        int ans = -1;
        for (int i = 2; i <= N; ++i) {
            for (int j = 1; j <= K; ++j) {
                f[i][j] = 1 + f[i - 1][j - 1] + f[i - 1][j];
            }
            if (f[i][K] >= N) {
                ans = i;
                break;
            }
        }
        return ans;
    }
};

#endif //ALGORITHM__887_SUPEREGGDROP_H
