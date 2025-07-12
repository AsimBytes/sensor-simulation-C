#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MIN_VALID_TEMP -10
#define MAX_VALID_TEMP 59


int main() {

    FILE *fp = fopen("/home/asim/C-Projects/sensor-sim-project/data/sensor_data.csv", "r");
    double num_val;
    // double arr[15]; // Declare static array for now.

    // Dynamic Memory Allocation declaration
    double *temp_data;
    int capacity = 10;
    int size = 0;
    
    // For average calculation
    double sum = 0;

    temp_data = (double*)malloc(capacity * sizeof(double));

    if (temp_data == NULL) {
        printf("Memory allocation failed.\n");
        exit(0);
    }

    if (!fp) 
        printf("Cant open file\n");
    else {
        char buffer[1024];
        
        int row = 0;
        int column = 0;

        while(fgets(buffer, 1024, fp)) {
            column = 0;
            row++;

            if (row == 1)
                continue;
            
            // strtok means string tokenizer and strtok splits strings into tokens using delimiters like , in this case.
            char *value = strtok(buffer, ", "); // Returns a pointer to the current token.

            while (value) {

                if (column != 0) {
                    if (size == capacity) {
                        capacity *= 2;
                        temp_data = realloc(temp_data, capacity * sizeof(double));
                    }

                    num_val = atof(value) * 10;

                    if (num_val >= MIN_VALID_TEMP && num_val <= MAX_VALID_TEMP) {
                        temp_data[size] = num_val;
                        size += 1;
                    }

                    // arr[index] = num_val * 10;
                    // index += 1;
                }

                value = strtok(NULL, ", "); // This points to the next token. 
                column++;
            }
        }

        temp_data = realloc(temp_data, size * sizeof(double)); // Reallocate the memory to free up unused space.

        for (int i = 0; i < size; i++) {
            printf("%.2f\t", temp_data[i]);
        }

        double max = temp_data[0];
        double min = temp_data[0];
        sum += temp_data[0];

        for (int i = 1; i < size; i++) {
            if (temp_data[i] > max)
                max = temp_data[i];

            if (temp_data[i] < min)
                min = temp_data[i];

            sum += temp_data[i];
        }

        double avg = sum / size;
        
        printf("\nMaximum Temperature: %.2f\n", max);
        printf("\nMinimum Temperature: %.2f\n", min);
        printf("\nAverage Temperature: %.2f\n", avg);
        printf("\n");

        fclose(fp);
    }
}