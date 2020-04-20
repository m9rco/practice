//
// @author m9rco
// @date 2020/4/16
//

#include <algorithm>
#include <iostream>

using namespace std;


int main() {
    long p = 23333;
    long q = 10007;
    long n = p * q;
    long phi = (p - 1) * (q - 1);

    long e, c;
    scanf("%ld %ld", &e, &c); // NOLINT(cert-err34-c)


    long old_s = 1, s = 0;
    long old_t = 0, t = 1;
    long old_r = e, r = phi;

    long d = 0;
    if (r == 0) {
        d = 1;
    } else {
        while (r != 0) {
            long qa = old_r / r;
            long oold_r, oold_s, oold_t;
            oold_r = old_r;
            old_r = r;
            r = oold_r - qa * r;

            oold_s = old_s;
            old_s = s;
            s = oold_s - qa * s;

            oold_t = old_t;
            old_t = t;
            t = oold_t - qa * s;
        }
        d = old_s;
    }

    if (d < 0) {
        d = phi + d;
    }
    unsigned long res = 1;

    while (d != 0) {
        if (1 == (d & 1)) { // NOLINT(hicpp-signed-bitwise)
            res = (res * c) % n;
        }
        d >>= 1; // NOLINT(hicpp-signed-bitwise)
        c = (c * c) % n;
    }
    cout << res << endl;
}

