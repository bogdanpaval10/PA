#include <stdio.h>
#include <iostream>
#include <queue>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_ROBOTS 5
#define MAX_SPACES 5
#define MAX_DIR 4
#define MAX_N_M 1001

struct info {
    int i;  // coordonata i din matrice
    int j;  // coordonata j din matrice
    int d;  // distanta
};

int di[MAX_DIR] = {0, 1, 0, -1};
int dj[MAX_DIR] = {1, 0, -1, 0};

int x[MAX_ROBOTS], nr_robts = 0, nr_miz = 0, mini = -1;
info rob[MAX_ROBOTS][MAX_ROBOTS];
info spaces[MAX_SPACES][MAX_SPACES];

bool ok(int n, int m, int i, int j) {
    if (i > 0 && j > 0 && i <= n && j <= m) {
        return true;
    }
    return false;
}

int lee(int n, int m, int mat[MAX_N_M][MAX_N_M],
        int i_start, int j_start, int i_stop, int j_stop) {
    int i_urm, j_urm, dir, ver = 1, copy_mat[MAX_N_M][MAX_N_M];
    queue < pair<int, int> > q;
    memcpy(copy_mat, mat, MAX_N_M * MAX_N_M * sizeof(int));

    q.push(make_pair(i_start, j_start));

    while (!q.empty() && ver == 1) {
        i_start = q.front().first;
        j_start = q.front().second;

        q.pop();

        for (dir = 0; dir <= 3; dir++) {
            i_urm = i_start + di[dir];
            j_urm = j_start + dj[dir];

            if (i_urm == i_stop && j_urm == j_stop) {
                ver = 0;  // am ajuns la nodul destinatie
            }

            if (ok(n, m, i_urm, j_urm) && (copy_mat[i_urm][j_urm] == 0)) {
                copy_mat[i_urm][j_urm] = copy_mat[i_start][j_start] + 1;
                q.push(make_pair(i_urm, j_urm));
            }
        }
    }
    return copy_mat[i_stop][j_stop];
}


void calculate_dist(int k) {
    int s_rob1 = 0, s_rob2 = 0, s_rob3 = 0, s_rob4 = 0;
    int prev_1, prev_2, prev_3, prev_4, maxi = 0;

    for (int i = 1 ; i <= k ; i ++) {  // i == nr spatiului murdar
        if (x[i] == 1) {  // este robtul 1
            if (s_rob1 == 0) {
                s_rob1 = rob[x[i]][i].d;  // distanta r1 -> s_i
                prev_1 = i;
            } else {
                s_rob1 += spaces[prev_1][i].d;  // distanta s_prev -> s_i
                prev_1 = i;
            }
        }
        if (maxi < s_rob1) {  // salvam drumul maxim
            maxi = s_rob1;
        }
        if (x[i] == 2) {  // este robtul 2
            if (s_rob2 == 0) {
                s_rob2 = rob[x[i]][i].d;  // distanta r2 -> s_i
                prev_2 = i;
            } else {
                s_rob2 += spaces[prev_2][i].d;  // distanta s_prev -> s_i
                prev_2 = i;
            }
        }
        if (maxi < s_rob2) {  // salvam drumul maxim
            maxi = s_rob2;
        }
        if (x[i] == 3) {  // este robtul 3
            if (s_rob3 == 0) {
                s_rob3 = rob[x[i]][i].d;  // distanta r3 -> s_i
                prev_3 = i;
            } else {
                s_rob3 += spaces[prev_3][i].d;  // distanta s_prev -> s_i
                prev_3 = i;
            }
        }
        if (maxi < s_rob3) {  // salvam drumul maxim
            maxi = s_rob3;
        }
        if (x[i] == 4) {  // este robtul 4
            if (s_rob4 == 0) {
                s_rob4 = rob[x[i]][i].d;  // distanta r4 -> s_i
                prev_4 = i;
            } else {
                s_rob4 += spaces[prev_4][i].d;  // distanta s_prev -> s_i
                prev_4 = i;
            }
        }
        if (maxi < s_rob4) {  // salvam drumul maxim
            maxi = s_rob4;
        }
    }


    if (mini == -1) {  // este prima iteratie,
        mini = maxi;  // mini = lungime drum pt prima varianta
    } else {
        if (mini > maxi) {
            mini = maxi;  // salvam varianta cu nr minim de parcurs pt curatare
        }
    }
}


bool solution(int k) {
    return k == nr_miz;
}

void back(int k) {
    for (int i = 1; i <= nr_robts; i++) {
        x[k] = i;  // se formeaza vectorul de permutari de roboti
        if (solution(k)) {
            calculate_dist(k);
        } else {
            back(k + 1);
        }
    }
}

int main() {
    ifstream f("curatare.in");
    ofstream g("curatare.out");

    int n, m, i, j, mat[MAX_N_M][MAX_N_M];
    char c;

    f >> n >> m;

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= m; j++) {
            f >> c;
            if (c == '.') {
                mat[i][j] = 0;
            }
            if (c == 'R') {
                nr_robts++;
                mat[i][j] = -1;
                rob[nr_robts][0].i = i;
                rob[nr_robts][0].j = j;
                rob[nr_robts][0].d = 0;
            }
            if (c == 'S') {
                nr_miz++;
                mat[i][j] = 0;
                spaces[nr_miz][0].i = i;
                spaces[nr_miz][0].j = j;
                spaces[nr_miz][0].d = 0;
            }
            if (c == 'X') {
                mat[i][j] = -1;
            }
        }
    }

    for (i = 1; i <= nr_robts; i++) {  // calculam distantele de la fiecare
        for (j = 1; j <= nr_miz; j++) {  // robot la fiecare spatiu murdar
            int i_start, j_start, i_stop, j_stop;
            rob[i][j].i = spaces[j][0].i;  // salvam pozitiile spatiului la
            rob[i][j].j = spaces[j][0].j;  // care se merge

            i_start = rob[i][0].i;
            j_start = rob[i][0].j;
            i_stop = spaces[j][0].i;
            j_stop = spaces[j][0].j;
            // distanta robt_i -> s_j
            rob[i][j].d = lee(n, m, mat, i_start, j_start, i_stop, j_stop) + 1;
        }
    }

    for (i = 1; i <= nr_miz; i++) {  // calculam distantele de la fiecare
        for (j = 1; j <= nr_miz; j++) {  // spatiu la fiecare spatiu murdar
            if (i != j) {
                int i_strt, j_strt, i_stp, j_stop;
                spaces[i][j].i = spaces[j][0].i;  // salvam pozitiile spatiului
                spaces[i][j].j = spaces[j][0].j;  // la care se merge
                i_strt = spaces[i][0].i;
                j_strt = spaces[i][0].j;
                i_stp = spaces[j][0].i;
                j_stop = spaces[j][0].j;
                // distanta s_i -> s_j
                spaces[i][j].d = lee(n, m, mat, i_strt, j_strt, i_stp, j_stop);
            } else {
                spaces[i][j].i = -1;
                spaces[i][j].j = -1;
                spaces[i][j].d = -1;
            }
        }
    }

    back(1);
    g << mini;

    f.close();
    g.close();

    return 0;
}
