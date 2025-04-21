#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Configuration structure to hold simulation parameters
typedef struct {
    char* output_file;  // Output file path
    int points;         // Number of points on the string
    int cycles;         // Number of wave cycles to simulate
    int samples;        // Samples per cycle
} Config;

// Function declarations
Config parse_arguments(int argc, char **argv);
void initialise_vector(double vector[], int size, double initial);
void print_vector(double vector[], int size);
void update_positions(double* positions, int points, double time);
int generate_timestamps(double* time_stamps, int time_steps, double step_size);
double driver(double time);
void print_header(FILE* out_file, int points);

int main(int argc, char **argv)
{
    // Parse command line arguments
    Config config = parse_arguments(argc, argv);
    
    // Calculate derived parameters
    int time_steps = config.cycles * config.samples + 1; // total timesteps
    double step_size = 1.0 / config.samples;

    // Allocate and initialize time stamps
    double* time_stamps = (double*) malloc(time_steps * sizeof(double));
    initialise_vector(time_stamps, time_steps, 0.0);
    generate_timestamps(time_stamps, time_steps, step_size);

    // Allocate and initialize positions array
    double* positions = (double*) malloc(config.points * sizeof(double));
    initialise_vector(positions, config.points, 0.0);

    // Open output file
    FILE* out_file = fopen(config.output_file, "w");
    if (out_file == NULL) {
        fprintf(stderr, "ERROR: Could not open output file %s\n", config.output_file);
        exit(EXIT_FAILURE);
    }
    
    // Write file header
    print_header(out_file, config.points);

    // Main simulation loop
    for (int i = 0; i < time_steps; i++) {
        update_positions(positions, config.points, time_stamps[i]);
        
        fprintf(out_file, "%d, %lf", i, time_stamps[i]);
        for (int j = 0; j < config.points; j++) {
            fprintf(out_file, ", %lf", positions[j]);
        }
        fprintf(out_file, "\n");
    }

    // Clean up
    free(time_stamps);
    free(positions);
    fclose(out_file);

    return EXIT_SUCCESS;
}

// Parses command line arguments and returns a Config structure
Config parse_arguments(int argc, char **argv) {
    Config config;
    
    if (argc != 5) {
        fprintf(stderr, "ERROR: Incorrect number of arguments!\n");
        fprintf(stderr, "Usage: %s [output_file] [points] [cycles] [samples]\n", argv[0]);
        fprintf(stderr, "  output_file: Path to output CSV file\n");
        fprintf(stderr, "  points:      Number of points on the string (integer > 0)\n");
        fprintf(stderr, "  cycles:      Number of wave cycles to simulate (integer > 0)\n");
        fprintf(stderr, "  samples:     Samples per cycle (integer > 0)\n");
        exit(EXIT_FAILURE);
    }
    
    config.output_file = argv[1];
    config.points = atoi(argv[2]);
    config.cycles = atoi(argv[3]);
    config.samples = atoi(argv[4]);
    
    // Validate parameters
    if (config.points <= 0 || config.cycles <= 0 || config.samples <= 0) {
        fprintf(stderr, "ERROR: All numerical parameters must be positive integers\n");
        exit(EXIT_FAILURE);
    }
    
    return config;
}

// Prints a header to the output file
void print_header(FILE* out_file, int points) {
    fprintf(out_file, "#, time");
    for (int j = 0; j < points; j++) {
        fprintf(out_file, ", y[%d]", j);
    }
    fprintf(out_file, "\n");
}

// Defines a simple harmonic oscillator as the driving force
double driver(double time) {
    return sin(time * 2.0 * M_PI);
}

// Updates the positions of the string points
void update_positions(double* positions, int points, double time) {
    double* new_positions = (double*) malloc(points * sizeof(double));
    
    new_positions[0] = driver(time);
    for (int i = 1; i < points; i++) {
        new_positions[i] = positions[i-1];
    }
    
    for (int i = 0; i < points; i++) {
        positions[i] = new_positions[i];
    }
    
    free(new_positions);
}

// Generates timestamps for the simulation
int generate_timestamps(double* timestamps, int time_steps, double step_size) {
    for (int i = 0; i < time_steps; i++) {
        timestamps[i] = i * step_size;
    }    
    return time_steps;
}

// Initializes a vector with a given value
void initialise_vector(double vector[], int size, double initial) {
    for (int i = 0; i < size; i++) {
        vector[i] = initial;
    }
}

// Prints a vector (for debugging)
void print_vector(double vector[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d, %lf\n", i, vector[i]);
    }
}