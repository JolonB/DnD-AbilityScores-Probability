#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef int roll;

const int DEFAULT_N_ITERATIONS = 1000;
const int DEFAULT_N_DICE = 4;
const int DEFAULT_N_SIDES = 6;
const int DEFAULT_REMOVE_N_WORST_DICE = 1;

int n_iterations = DEFAULT_N_ITERATIONS;
int n_dice = DEFAULT_N_DICE;
int n_sides = DEFAULT_N_SIDES;
int remove_n_worst_dice = DEFAULT_REMOVE_N_WORST_DICE;
bool print_distribution = false;
bool print_rolls = false;

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
    int n_counted_dice = n_dice - remove_n_worst_dice;
    int min_score = n_counted_dice;
    int max_score = n_sides * n_counted_dice;
    int n_unique_possibilities = max_score - min_score + 1; // +1 for inclusive range
    
    int *counts = calloc(sizeof(int), n_unique_possibilities);
    for (int i = 0; i < n_values; i++) {
        int count_index = values[i] - min_score;
        counts[count_index]++;
    }

    int max_count = 0;
    int max_index = 0;
    for (int i = 0; i < n_unique_possibilities; i++) {
        if (print_distribution) {
            printf("%d: %d\n", i + min_score, counts[i]);
        }
        if (counts[i] > max_count) {
            max_count = counts[i];
            max_index = i;
        }
    }

    return max_index + min_score;
}

void print_stats(int roll_totals[], int n_iterations) {
    sort_array(roll_totals, n_iterations);
    double mean = calculate_mean(roll_totals, n_iterations);
    double median = calculate_median(roll_totals, n_iterations);
    int mode = calculate_mode(roll_totals, n_iterations);
    printf("Mean: %.4f\nMedian: %.4f\nMode: %d\n", mean, median, mode);
}

void calculate_rolls(int roll_totals[], int n_iterations) {
    roll rolls[n_dice];

    for (int i = 0; i < n_iterations; i++) {
        for (int j = 0; j < n_dice; j++) {
            int random_roll = rand() % n_sides + 1;
            rolls[j] = random_roll;
            if (print_rolls) {
                printf("%d ", random_roll);
            }
        }
        if (print_rolls) {
            printf("\n");
        }

        sort_array(rolls, n_dice);
        // Sum only the best rolls
        int total = 0;
        for (int j = remove_n_worst_dice; j < n_dice; j++) {
            total += rolls[j];
        }
        // printf("%d ", total);

        roll_totals[i] = total;
    }
    // printf("\n");
}

void print_help(void) {
    printf(
        "Dungeons and Dragons Ability Score Probability\n"
        "Calculate the average ability score from rolling 4d6 and removing the worst one. "
        "Or do any number of dice to see what happens.\n\n"
        "usage: program [-dp] [-i n_iter] [-n n_dice] [-s n_sides] [-r n_removed]\n"
        "Options:\n"
        "\t-i\tNumber of iterations to calculate over (default is %d)\n"
        "\t-n\tThe number of dice to roll (default is %d)\n"
        "\t-s\tThe number of sides of the dice (default is %d)\n"
        "\t-r\tThe number of the worst scoring dice to remove (default is %d)\n"
        "\t-d\tPrint the distribution of rolls\n"
        "\t-p\tPrint the rolls for each iteration\n"
        "\t-h\tDisplay this help message\n",
        DEFAULT_N_ITERATIONS, DEFAULT_N_DICE, DEFAULT_N_SIDES, DEFAULT_REMOVE_N_WORST_DICE
    );
}

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "i:n:s:r:dph?")) != -1) {
        switch (opt) {
            case 'i': n_iterations = atoi(optarg); break;
            case 'n': n_dice = atoi(optarg); break;
            case 's': n_sides = atoi(optarg); break;
            case 'r': remove_n_worst_dice = atoi(optarg); break;
            case 'd': print_distribution = true; break;
            case 'p': print_rolls = true; break;
            case 'h':
            case '?':
            default:
                print_help();
                return 0;
        }
    }

    srand(time(NULL));

    int *roll_totals = malloc(sizeof(int) * n_iterations);
    calculate_rolls(roll_totals, n_iterations);

    print_stats(roll_totals, n_iterations);

    return 0;
}
