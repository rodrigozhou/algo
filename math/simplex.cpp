/**
 * Simplex Algorithm
 *
 * max c^T x
 * st. Ax <= b
 *      x >= 0
 */

#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX 256

const double eps = 1e-9;

int n, m;
double tb[MAX][MAX];

int main() {
    scanf("%d %d", &n, &m);

    // objective function
    for (int i = 0; i < n; i++)
        scanf("%lf", &tb[m][i]);

    // constraints
    // sum { tb[i][j] * x_j } <= tb[i][n+m]
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++)
            scanf("%lf", &tb[i][j]);
        scanf("%lf", &tb[i][n+m]);
        tb[i][n+i] = 1;
    }

    while (1) {
        int var_in = -1;
        for (int i = 0; i < n+m; i++) {
            if (tb[m][i] > eps) {
                var_in = i;
                break;
            }
        }
        if (var_in == -1)
            break;
        int row = -1;
        double inc;
        for (int i = 0; i < m; i++) {
            if (tb[i][var_in] > eps &&
                    (row == -1 || tb[i][n+m] / tb[i][var_in] < inc)) {
                inc = tb[i][n+m] / tb[i][var_in];
                row = i;
            }
        }
        if (row == -1) {
            puts("Unbounded");
            break;
        }
        for (int i = 0; i <= m; i++) if (i != row) {
            double c = tb[i][var_in] / tb[row][var_in];
            for (int j = 0; j <= n+m; j++)
                tb[i][j] -= c * tb[row][j];
        }
        double c = tb[row][var_in];
        for (int i = 0; i <= n+m; i++)
            tb[row][i] /= c;
    }
    printf("%lf\n", -tb[m][n+m]);
}
