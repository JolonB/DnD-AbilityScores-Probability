#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int N_DICE = 4;
const int REMOVE_N_WORST_DICE = 1;
const int N_SIDES = 6;

typedef int roll;

int compare_rolls(const void* a, const void* b) {
    roll arg1 = *(const roll*)a;
    roll arg2 = *(const roll*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

void print_stats(roll rolls[], int n_rolls) {
    // TODO
}

void calculate_rolls(void) {
    srand(time(NULL));

    roll rolls[N_DICE];

    for (int i = 0; i < N_DICE; i++) {
        int random_roll = rand() % N_SIDES + 1;
        printf("%d", random_roll);
        rolls[i] = random_roll;
    }

    printf("\n");

    qsort(rolls, N_DICE, sizeof(roll), compare_rolls);

    for (int i = 0; i < N_DICE; i++) {
        printf("%d", rolls[i]);
    }

    printf("\n");

    // Sum only the best rolls
    int total = 0;
    for (int i = REMOVE_N_WORST_DICE; i < N_DICE; i++) {
        total += rolls[i];
    }
    printf("%d", total);
}

void main(void) {
    calculate_rolls();
    return;
}