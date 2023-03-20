#include <fstream>
using namespace std;

#define MAX_DIM 10001
#define MAX_VECT 20

int mat[MAX_DIM][MAX_DIM];

int main() {
    ifstream f("curse.in");
    ofstream g("curse.out");

    int n, m, a, i, j, grad_zero, count, remaining;
    int curr[MAX_VECT], next[MAX_VECT];
    int visited[MAX_DIM] = {0}, degrees[MAX_DIM];

    f >> n >> m >> a;

    for (i = 1; i <= n; i++) {  // primul antrenament
        f >> curr[i];
    }

    for (i = 2; i <= a; i++) {  // restul antrenamentelor
        for (j = 1; j <= n; j++) {
            f >> next[j];
        }
        count = 1;
        while (curr[count] == next[count]) {  // nr cate elemente sunt comune
            count++;
        }
        mat[curr[count]][next[count]] = 1;

        for (j = 1; j <= n; j++) {
            curr[j] = next[j];
        }
    }

    for (j = 1; j <= m; j++) {
        degrees[j] = 0;
        for (i = 1; i <= m; i++) {
            if (mat[i][j] == 1) {  // calculeaza gradul lui j
                degrees[j]++;
            }
        }
        if (degrees[j] == 0) {
            grad_zero = j;  // salvam nodul cu gradul 0
        }
    }

    g << grad_zero << " ";
    visited[grad_zero] = 1;
    remaining = m - 1;

    while (remaining > 0) {
        for (j = 1; j <= m; j++) {  // sterg muchiile
            if (mat[grad_zero][j] == 1 && visited[j] == 0) {
                degrees[j]--;
            }
        }

        for (i = 1; i <= m; i++) {
            if (degrees[i] == 0 && visited[i] == 0) {
                grad_zero = i;  // are grad 0 si este nevizitat
                visited[i] = 1;
                break;
            }
        }

        g << grad_zero << " ";

       --remaining;
    }

    f.close();
    g.close();

    return 0;
}
