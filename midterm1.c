#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//#define MAX_LAMPS 20971

int main() {
    int N, k, M;
    int lit_count = 0;          // Number of currently lit lamps
    int lit_front = 0;          // The index of the earliest lit lamp

    // Input
    scanf("%d", &N);
    int t[N];
    int state[N];
    for (int i = 0; i < N; i++) {
        state[i] = 0;   // Initialize all lamps to be unlit
    }
    int lit_lamps[N];   // Keep track of the lit lamps' indices
    for (int i = 0; i < N; i++) {
        scanf("%d", &t[i]);
    }
    scanf("%d", &k);
    scanf("%d", &M);

    int current_position = k;

    while (true) {
        // Light the current lamp if it's not lit
        if (state[current_position] == 0) {
            state[current_position] = 1;
            lit_lamps[lit_count++] = current_position;
        }

        // If the number of lit lamps exceeds M, extinguish the earliest lit lamp
        if (lit_count > M) {
            state[lit_lamps[lit_front]] = 0; // Extinguish the earliest lit lamp
            lit_front++;
        }

        // Check stop condition:
        // We need at least one lit lamp on both sides of current_position
        bool has_left_lit = false, has_right_lit = false;

        for (int i = 0; i < current_position; i++) {
            if (state[i] == 1) {
                has_left_lit = true;
                break;
            }
        }
        for (int i = current_position + 1; i < N; i++) {
            if (state[i] == 1) {
                has_right_lit = true;
                break;
            }
        }

        if (has_left_lit && has_right_lit) {
            printf("%d\n", current_position);
            break;
        }

        // Move to the next position as per the transition array t
        current_position = t[current_position];
    }

    return 0;
}