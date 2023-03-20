#include <iostream>
#include <fstream>
using namespace std;

#define TOTAL_LEN 1000000
#define MAX_MAT 1002

int mat[MAX_MAT][MAX_MAT], queue_x[TOTAL_LEN], queue_y[TOTAL_LEN], len;
char direction[TOTAL_LEN];

void vertical(int x, int y, int steps) {
    int copy_x = x - 1;  // se merge in jos
    while (mat[copy_x][y] != -1) {  // nu este perete
        if (mat[copy_x][y] == -2) {  // este spatiu liber
            mat[copy_x][y] = steps;
            len++;
            queue_x[len] = copy_x;  // se adauga in coada
            queue_y[len] = y;
            direction[len] = 'V';  // se salveaza orientarea
        }
        copy_x--;
    }

    copy_x = x + 1;  // se merge in sus
    while (mat[copy_x][y] != -1) {
         if (mat[copy_x][y] == -2) {
            mat[copy_x][y] = steps;
            len++;
            queue_x[len] = copy_x;
            queue_y[len] = y;
            direction[len] = 'V';
         }
        copy_x++;
    }
}


void horizontally(int x, int y, int steps) {
    int copy_y = y - 1;  // se merge la stanga
    while (mat[x][copy_y] != -1) {  // nu este perete
        if (mat[x][copy_y] == -2) {  // este spatiu liber
            mat[x][copy_y] = steps;
            len++;
            queue_x[len] = x;  // se adauga in coada
            queue_y[len] = copy_y;
            direction[len] = 'O';  // se salveaza orientarea
        }
        copy_y--;
    }

    copy_y = y + 1;  // se merge la dreapta
    while (mat[x][copy_y] != -1) {
        if (mat[x][copy_y] == -2) {
            mat[x][copy_y] = steps;
            len++;
            queue_x[len] = x;
            queue_y[len] = copy_y;
            direction[len] = 'O';
        }
        copy_y++;
    }
}


int main() {
    ifstream f("beamdrone.in");
    ofstream g("beamdrone.out");

    int n, m, i, j, xi, yi, xf, yf, x, y;
    char c;

    f >> n >> m;
    f >> xi >> yi >> xf >> yf;
    xi++;
    yi++;
    xf++;
    yf++;

    for (i = 1; i <= n; i++) {  // citire si construire matrice
        for (j = 1; j <= m; j++) {
            f >> c;
            switch (c) {
              case '.':
                mat[i][j] = -2;  // daca este ".", pun -2 in matrice
                break;
              case 'W':
                mat[i][j] = -1;  // daca este "W", pun -1 in matrice
                break;
            }
        }
    }

    for (i = 0; i <= n + 1; i++) {  // bordare matrice pe linii
        mat[i][0] = -1;
        mat[i][m + 1] = -1;
    }

    for (j = 0; j <= m + 1; j++) {  // bordare matrice pe coloane
       mat[0][j] = -1;
       mat[n + 1][j] = -1;
    }

    mat[xi][yi] = 0;
    vertical(xi, yi, 0);
    horizontally(xi, yi, 0);

    i = 1;
    while (i <= len) {  // inca mai am elemente de expandat in coada
        for (j = i; j <= len; j++) {
            x = queue_x[j];
            y = queue_y[j];
            if (direction[j] == 'V') {
                horizontally(x, y, mat[x][y] + 1);
            } else {
                vertical(x, y, mat[x][y] + 1);
            }
            if (mat[xf][yf] != -2) {
                g << mat[xf][yf];
                return 0;
            }
        }
        i = len + 1;
    }

    f.close();
    g.close();

    return 0;
}
