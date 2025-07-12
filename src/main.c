#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main() {

    FILE *fp = fopen("/home/asim/C-Projects/sensor-sim-project/data/sensor_data.csv", "r");
    double arr[15]; // Declare static array for now.
    int index = 0;

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

            if (row > 5)
                break;
            
            
            // strtok means string tokenizer and strtok splits strings into tokens using delimiters like , in this case.
            char *value = strtok(buffer, ", "); // Returns a pointer to the current token.

            while (value) {

                if (column != 0) {
                    double num_val = atof(value);

                    arr[index] = num_val * 10;
                    index += 1;
                }

                value = strtok(NULL, ", "); // This points to the next token. 
                column++;
            }
        }

        for (int i = 0; i < 15; i++) {
            printf("%.2f\t", arr[i]);
        }

        printf("\n");

        fclose(fp);
    }
}