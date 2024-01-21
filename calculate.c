#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const int N_DICE = 4;
const int REMOVE_N_WORST_DICE = 1;
const int N_SIDES = 6;

const int N_ITERATIONS = 1000000;

typedef int roll;

int smallest_to_largest_sort(const void* a, const void* b) {
    roll arg1 = *(const roll*)a;
    roll arg2 = *(const roll*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}

void sort_array(int values[], int n_values) {
    qsort(values, n_values, sizeof(int), smallest_to_largest_sort);
}

double calculate_mean(int values[], int n_values) {
    int sum = 0;
    for (int i = 0; i < n_values; i++) {
        sum += values[i];
    }
    return 1.0 * sum / n_values;
}

double calculate_median(int values[], int n_values) {
    // Array must be sorted first
    if (n_values % 2 == 0) {
        return (values[n_values / 2] + values[n_values / 2 + 1]) / 2.0;
    } else {
        return values[n_values / 2 + 1];
    }
}

int calculate_mode(int values[], int n_values) {
    int n_counted_dice = N_DICE - REMOVE_N_WORST_DICE;
    int min_score = n_counted_dice;
    int max_score = N_SIDES * n_counted_dice;
    int n_unique_possibilities = max_score - min_score + 1; // +1 for inclusive range
    
    int *counts = calloc(sizeof(int), n_unique_possibilities);
    for (int i = 0; i < n_values; i++) {
        int count_index = values[i] - min_score;
        counts[count_index]++;
    }

    int max_count = 0;
    int max_index = 0;
    for (int i = 0; i < n_unique_possibilities; i++) {
        // printf("%d: %d\n", i + min_score, counts[i]);
        if (counts[i] > max_count) {
            max_count = counts[i];
            max_index = i;
        }
    }

    return max_index + min_score;
}

void print_stats(int roll_totals[], int n_iterations) {
    sort_array(roll_totals, n_iterations);
    printf("Mean: %.4f\n", calculate_mean(roll_totals, n_iterations));
    printf("Median: %.4f\n", calculate_median(roll_totals, n_iterations));
    printf("Mode: %d\n", calculate_mode(roll_totals, n_iterations));
}

void calculate_rolls(int roll_totals[], int n_iterations) {
    roll rolls[N_DICE];

    for (int i = 0; i < n_iterations; i++) {
        for (int j = 0; j < N_DICE; j++) {
            int random_roll = rand() % N_SIDES + 1;
            rolls[j] = random_roll;
        }

        sort_array(rolls, N_DICE);
        // Sum only the best rolls
        int total = 0;
        for (int j = REMOVE_N_WORST_DICE; j < N_DICE; j++) {
            total += rolls[j];
        }
        // printf("%d ", total);

        roll_totals[i] = total;
    }
    // printf("\n");
}

void main(void) {
    srand(time(NULL));
    int n_iterations = N_ITERATIONS;

    int *roll_totals = malloc(sizeof(int) * n_iterations);
    calculate_rolls(roll_totals, n_iterations);

    print_stats(roll_totals, n_iterations);
    return;
}