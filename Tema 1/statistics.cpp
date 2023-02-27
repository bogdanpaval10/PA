#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAX_CHAR 2000
#define NR_LETTERS 26

struct info {
    int freq;  // nr de aparitii a literei
    int length;  // lungimea cuvantului
    int old_ind;  // indicele vechi
};

bool cmp(const info &a, const info &b) {
    return (2 * a.freq - a.length) > (2 * b.freq - b.length);
}  // daca 2 * nr_aparitii_litera - lungime_cuvant

int main() {
    ifstream f("statistics.in");
    ofstream g("statistics.out");

    int n, i, j;
    char s[MAX_CHAR];
    f >> n;

    vector<vector<int>> words(n, vector<int>(27));
    // words[0 -> n-1][0] = lungime fiecare cuvant
    // words[0 -> n-1][1 -> 27] = frecventa fiecarei litere

    for (i = 0; i < n; i++) {
        f >> s;
        words[i][0] = strlen(s);  // se pune lungimea cuvantului s
        for (j = 0; j < strlen(s); j++) {
            words[i][s[j] - 96]++;  // se incrementeaza frecventa literei s[j]
        }
    }
    f.close();

    int maxi = 0;  // nr maxim de cuvinte din toata lista
    for (i = 1; i <= NR_LETTERS; i++) {
        // vector pt a face sortarea cuvintelor
        info *ind = (info *)malloc(n * sizeof(info));
        for (j = 0; j < n; j++) {
            ind[j].old_ind = j;  // indicele inainte de sortare
            ind[j].freq = words[j][i];  // nr aparitii a literei de pe pozitia
                                        // i in cuvantul de pe pozitia j
            ind[j].length = words[j][0];  // lungime cuvant de pe pozitia j
        }

        sort(ind, ind + n, cmp);  // sortare descrescatoare

        int nr = 0, nr_let = 0, tot_len = 0;
        j = 0;
        while (j < n) {
            int index = ind[j].old_ind;  // legatura index initial si sortat
            tot_len += words[index][0];  // se adauga lungimea cuvantului
            nr_let += words[index][i];  // se adauga nr de litere dominante
            if (nr_let > tot_len / 2) {  // conditia enuntului
                j++;
                nr++;  // se creste nr cuvintelor concatenate
                continue;
            } else {
                break;
            }
        }
        if (maxi < nr) {
            maxi = nr;
        }
        free(ind);
    }

    if (maxi != 0) {
        g << maxi;
    } else {
        g << "-1";
    }

    g.close();
    return 0;
}
