#include <fstream>
#include <algorithm>

using namespace std;

#define MAX_MAT 10002
#define MAX_ARRAY 100002

int mat[MAX_MAT][MAX_MAT];

void dfs(int barbars[MAX_ARRAY], int dist[MAX_ARRAY], int visited[MAX_ARRAY],
        int &nr_dist, int n, int xi, int d) {
    visited[xi] = 1;
    for (int i = 1; i <= n; i++) {
        if (visited[i] != 1 && mat[xi][i] != 0) {
            if (barbars[i] == 1) {  // localitatea i este barbara
                nr_dist++;
                dist[nr_dist] = d + mat[xi][i];  // se calculeaza distanta
            } else {
                dfs(barbars, dist, visited, nr_dist, n, i, d + mat[xi][i]);
            }
            visited[i] = 0;
        }
    }
}

int main() {
    ifstream f("fortificatii.in");
    ofstream g("fortificatii.out");

    int barbars[MAX_ARRAY], dist[MAX_ARRAY], visited[MAX_ARRAY], nr_dist;
    int n, m, k, i, b, nr_loc_barb, barbar, xi, yi, ti, mini, maxi, poz_min;

    f >> n >> m >> k >> b;

    for (i = 1; i <= b; i++) {
        f >> barbar;
        barbars[barbar] = 1;
    }

    for (i = 1; i <= m; i++) {
        f >> xi >> yi >> ti;
        nr_loc_barb = 0;
        if (barbars[xi] == 1) {  // xi este localitate barbara
            nr_loc_barb++;
        }
        if (barbars[yi] == 1) {  // yi este localitate barbara
            nr_loc_barb++;
        }
        if (nr_loc_barb <= 1) {
            mat[xi][yi] = ti;
            mat[yi][xi] = ti;
        }
    }

    nr_dist = 0;
    dfs(barbars, dist, visited, nr_dist, n, 1, 0);

    mini = dist[1];
    maxi = dist[1];

    for (i = 2; i <= nr_dist; i++) {
        if (dist[i] < mini) {
            mini = dist[i];
        }
        if (dist[i] > maxi) {
            maxi = dist[i];
        }
    }

    if ((maxi - mini) * nr_dist <= k) {  // le fac pe toate egale cu maximul
        for (i = 1; i <= nr_dist; i++) {  // si dupa iau catul
            k -= (maxi - dist[i]);
        }
        g << maxi + k / nr_dist;
    } else {
        while (k > 0) {
            mini = dist[1];
            poz_min = 1;
            for (i = 2; i <= nr_dist; i++) {
                if (dist[i] < mini) {
                    mini = dist[i];
                    poz_min = i;
                }
            }
            dist[poz_min]++;
            k--;
        }
        mini = dist[1];
        for (i = 2; i <= nr_dist; i++)
             if (dist[i] < mini) {
                mini = dist[i];
             }
        g << mini;
    }

    f.close();
    g.close();

    return 0;
}
