#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main() {

    FILE *fp = fopen("/home/asim/C-Projects/sensor-sim-project/data/sensor_data.csv", "r");
    double num_val;
    // double arr[15]; // Declare static array for now.

    // Dynamic Memory Allocation declaration
    double *temp_data;
    int capacity = 10;
    int size = 0;

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

                    temp_data[size] = atof(value) * 10;
                    size += 1;

                    printf("Size for each iteration: %d\n", size);
                    printf("Capacity for each iteration: %d\n", capacity);
                    printf("And the value is....%s\n", value);

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

        printf("\n");

        fclose(fp);
    }
}