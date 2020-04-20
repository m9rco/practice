//
// @author m9rco
// @date 2020/4/17
//

#include <algorithm>
#include <iostream>
//#include <cassert>
#include <cstring>

using namespace std;

int main() {
    unsigned short T;
    cin >> T;
//    assert(1 <= T && T <= 10);
    while (T--) {
        int N, M;
        cin >> N >> M;
//        assert(1 <= N && N <= 1000);
//        assert(1 <= M && M <= 10000);
        bool visit[1010];
        int map[1010][1010];

        memset(map, 0x3f, sizeof(map));
        memset(visit, 0, sizeof(visit));

        for (int i = 1; i <= N; i++) {
            int W;
            cin >> W;
//            assert(1 <= W && W <= 10000);
            map[0][i] = map[i][0] = min(map[0][i], W);
        }
        while (M--) {
            int a, b, c;
            cin >> a >> b >> c;
            map[a][b] = map[b][a] = min(map[a][b], c);
        }

        int res = 0;
        int dist[1010];
        memset(dist, 0x3f, sizeof(dist));
        for (int i = 0; i <= N; i++) {
            int t = -1;
            for (int j = 0; j <= N; j++) {
                if (!visit[j] && (t == -1 || dist[t] > dist[j])) {
                    t = j;
                }
            }
            if (i != 0 && dist[t] == 0x3f3f3f3f) {
                res = 0x3f3f3f3f;
            }
            if (i != 0) res += dist[t];
            visit[t] = true;
            for (int j = 0; j <= N; j++) {
                dist[j] = min(dist[j], map[t][j]);
            }
        }

        cout << res << endl;
    }
    return 0;
}
