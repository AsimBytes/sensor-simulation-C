#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct Threshold {
    int min_valid_temp;
    int max_valid_temp;
};

int read_csv(const char *file_path, double **temp_arr, struct Threshold thres) {
    FILE *fp = fopen(file_path, "r");

    if (!fp)
        printf("Cannot open the selected file.\n");

    
    int capacity = 10; // Define the initial size of array
    int size = 0;
    double temp_reading = 0; // Stores the scaled values of temperature

    *temp_arr = (double*)malloc(capacity * sizeof(double));

    if (temp_arr == NULL) {
        printf("Memory allocation failed.\n");
    }

    
    char buffer[1024];
    int row = 0;
    int column = 0;

    while (fgets(buffer, 1024, fp)) {
        column = 0;
        row++;

        if (row == 1)
            continue;

        char *sensor_readings = strtok(buffer, ",");

        while (sensor_readings) {
            if (column != 0) {
                if (size == capacity) {
                    capacity *= 2;
                    *temp_arr = realloc(*temp_arr, capacity * sizeof(double));

                    if (*temp_arr == NULL) {
                        printf("Reallocation failed.\n");
                        fclose(fp);
                        return size;
                    }
                }

                temp_reading = atof(sensor_readings) * 10;

                if (temp_reading >= thres.min_valid_temp && temp_reading <= thres.max_valid_temp) {
                    (*temp_arr)[size] = temp_reading;
                    size++;
                }
            }
            sensor_readings = strtok(NULL, ",");
            column++;
        }
    }

    // Clean up any unused memory space in array
    *temp_arr = realloc(*temp_arr, size * sizeof(double));

    fclose(fp);

    return size;
}

void get_thresholds(double *high_temp, double *low_temp) {
    printf("\nEnter threshold for maximum temperature: ");
    scanf("%lf", high_temp);

    printf("\nEnter threshold for minimum temperature: ");
    scanf("%lf", low_temp);
}

void simulate_readings(double temp_readings[], int size, double high_temp, double low_temp) {
    for (int i = 0; i < size; i++) {
        printf("Simulated Reading: %.2f\n", *(temp_readings + i));

        if (*(temp_readings + i) > high_temp) {
            printf("ALERT: High temperature detected at index %d: %.2f\n", i, *(temp_readings + i));
        }

        if (*(temp_readings + i) < low_temp) {
            printf("ALERT: Low temperature detected at index %d: %.2f\n", i, *(temp_readings + i));
        }

        sleep(1);
    }
}

void compute_stats(double temp_readings[], int size) {
    double sum = 0;

    double max = *temp_readings;
    double min = *temp_readings;
    sum += *temp_readings;

    for (int i = 1; i < size; i++) {
        if (*(temp_readings + i) > max)
            max = *(temp_readings + i);

        if (*(temp_readings + i) < min)
            min = *(temp_readings + i);

        sum += *(temp_readings + i);
    }

    double avg = sum / size;
    
    printf("\nMaximum Temperature: %.2f\n", max);
    printf("\nMinimum Temperature: %.2f\n", min);
    printf("\nAverage Temperature: %.2f\n", avg);
    printf("\n");
}


int main() {
    struct Threshold thres = {-10, 59};
    double *temp_data = NULL;
    const char *file_path = "/home/asim/C-Projects/sensor-sim-project/data/sensor_data.csv";
    double high_temp;
    double low_temp;

    int num_of_readings = read_csv(file_path, &temp_data, thres);
    get_thresholds(&high_temp, &low_temp);
    simulate_readings(temp_data, num_of_readings, high_temp, low_temp);
    compute_stats(temp_data, num_of_readings);
    free(temp_data);

    return 0;
}