#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define LANE_SIZE 64      // Each lane is 64 bits
#define ROWS 5            // SHA-3 state matrix is 5x5
#define COLUMNS 5
#define STATE_SIZE (ROWS * COLUMNS) // Total number of lanes
#define CAPACITY_LANES 9  // The last 9 lanes (576 bits) represent the capacity portion
#define RATE_LANES (STATE_SIZE - CAPACITY_LANES) // The first 16 lanes (1024 bits) represent the rate portion

// Function to generate a random 64-bit lane with at least one non-zero bit
uint64_t generate_nonzero_lane() {
    uint64_t lane = 0;
    while (lane == 0) {
        lane = ((uint64_t)rand() << 32) | rand(); // Generate a random 64-bit number
    }
    return lane;
}

// Function to initialize the internal state matrix with zeros
void initialize_state(uint64_t state[ROWS][COLUMNS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            state[i][j] = 0;  // Initialize all lanes to zero
        }
    }
}

// Function to fill the rate portion of the state matrix (first 16 lanes) with non-zero lanes
void fill_rate_portion(uint64_t state[ROWS][COLUMNS]) {
    int lanes_filled = 0;
    for (int i = 0; i < ROWS && lanes_filled < RATE_LANES; i++) {
        for (int j = 0; j < COLUMNS && lanes_filled < RATE_LANES; j++) {
            state[i][j] = generate_nonzero_lane();
            lanes_filled++;
        }
    }
}

// Function to check if all capacity lanes are non-zero
int all_capacity_lanes_nonzero(uint64_t state[ROWS][COLUMNS]) {
    int lanes_checked = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLUMNS; j++) {
            if (lanes_checked >= RATE_LANES) {  // Start checking after rate portion
                if (state[i][j] == 0) {
                    return 0;  // Found a zero lane in the capacity portion
                }
            }
            lanes_checked++;
        }
    }
    return 1;  // All capacity lanes are non-zero
}

// Main function to simulate the process
int main() {
    uint64_t state[ROWS][COLUMNS];  // Internal state matrix (5x5)
    srand(time(0));  // Seed random number generator

    initialize_state(state);  // Initialize the state to all zeros

    printf("Initial state: All capacity lanes are zeros.\n");

    int rounds = 0;
    // Simulate rounds of message block absorption
    while (!all_capacity_lanes_nonzero(state)) {
        printf("Round %d: Filling rate portion with non-zero bits...\n", rounds + 1);
        fill_rate_portion(state);  // Fill the rate portion with non-zero bits
        rounds++;
    }

    printf("All capacity lanes became non-zero after %d rounds.\n", rounds);
    
    return 0;
}

