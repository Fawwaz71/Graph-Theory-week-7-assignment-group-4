#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int r, c;
} Pos;

int dr[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
int dc[8] = {1, 2, 2, 1, -1, -2, -2, -1};

int isValid(int r, int c, int n, int m, int **visited) {
    return (r >= 0 && r < n && c >= 0 && c < m && visited[r][c] == 0);
}

// Hitung berapa banyak langkah valid yang bisa diambil dari posisi (r, c)
int countMoves(int r, int c, int n, int m, int **visited) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (isValid(nr, nc, n, m, visited))
            count++;
    }
    return count;
}

// Urutkan langkah-langkah berdasarkan jumlah langkah lanjutannya (heuristik Warnsdorff)
int nextMoves(int r, int c, int n, int m, int **visited, Pos moves[]) {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int nr = r + dr[i];
        int nc = c + dc[i];
        if (isValid(nr, nc, n, m, visited)) {
            moves[count].r = nr;
            moves[count].c = nc;
            count++;
        }
    }

    // Sort berdasarkan jumlah kemungkinan langkah (ascending)
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (countMoves(moves[i].r, moves[i].c, n, m, visited) >
                countMoves(moves[j].r, moves[j].c, n, m, visited)) {
                Pos temp = moves[i];
                moves[i] = moves[j];
                moves[j] = temp;
            }
        }
    }

    return count;
}

int solveKnightTour(int r, int c, int step, int total, int n, int m, int **visited, Pos *path) {
    path[step].r = r;
    path[step].c = c;
    visited[r][c] = 1;

    if (step + 1 == total)
        return 1;  // semua kotak dikunjungi

    Pos moves[8];
    int count = nextMoves(r, c, n, m, visited, moves);

    for (int i = 0; i < count; i++) {
        if (solveKnightTour(moves[i].r, moves[i].c, step + 1, total, n, m, visited, path))
            return 1;
    }

    visited[r][c] = 0; // backtrack
    return 0;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m); // ukuran papan
    int sr, sc;
    scanf("%d %d", &sr, &sc); // posisi awal kuda

    // alokasi memori
    int **visited = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        visited[i] = calloc(m, sizeof(int));
    }

    Pos *path = malloc(n * m * sizeof(Pos));

    if (solveKnightTour(sr, sc, 0, n * m, n, m, visited, path)) {
        for (int i = 0; i < n * m; i++)
            printf("%d %d\n", path[i].r, path[i].c);
    } else {
        printf("No tour found\n");
    }

    for (int i = 0; i < n; i++)
        free(visited[i]);
    free(visited);
    free(path);

    return 0;
}