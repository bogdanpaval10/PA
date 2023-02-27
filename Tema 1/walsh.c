#include <stdio.h>
#include <stdlib.h>


int walsh(int n, int x, int y, int nr) {
    if (x == 1) {  // pe prima linie
        if (y == 1 || y == 2) {  // prima sau a doua coloana
            return nr;
        }
    }
    if (x == 2) {  // a doua linie
        if (y == 1) {  // prima coloana
            return nr;
        }
        if (y == 2) {  // a doua coloana
            return nr + 1;
        }
    }

    if (x <= n / 2 && y <= n / 2) {  // este in stanga sus
        return walsh(n / 2, x, y, nr);
    }
    if (x <= n / 2 && y > n / 2) {  // este in dreapta sus
        return walsh(n / 2, x, y - (n / 2), nr);
    }
    if (x > n / 2 && y <= n / 2) {  // este in stanga jos
        return walsh(n / 2, x - (n / 2) , y, nr);
    }
    if (x > n / 2 && y > n / 2) {  // este in dreapta jos
        return walsh(n / 2, x - (n / 2) , y - (n / 2), nr + 1);
    }
}

int main() {
	FILE *f = fopen("walsh.in", "r");
    FILE *g = fopen("walsh.out", "w");

    int n, k, i, x, y;
    fscanf(f, "%d %d", &n, &k);

    for (i = 0; i < k; i++) {
        fscanf(f, "%d %d", &x, &y);  // se citesc perechile x, y
        if (walsh(n, x, y, 0) % 2 == 0) {  // este nr par, nu trebuie negat=> 0
            fprintf(g, "0\n");
        } else {  // daca este impar, trebuie negat => 1
            fprintf(g, "1\n");
        }
    }

    fclose(f);
    fclose(g);

	return 0;
}
