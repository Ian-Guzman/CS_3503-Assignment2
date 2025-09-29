#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>


void oct_to_bin(const char *oct, char *out);
void oct_to_hex(const char *oct, char *out);
void hex_to_bin(const char *hex, char *out);
void to_sign_magnitude(int32_t n, char *out);
void to_ones_complement(int32_t n, char *out);
void to_twos_complement(int32_t n, char *out);

int main()
{
    FILE *file = fopen("a2_test.txt", "r");
    if (!file)
    {
        printf("Error: Could not open test file\n");
        return 1;
    }

    char line[256];
    int total = 0, passed = 0;

    while (fgets(line, sizeof(line), file))
    {
        //skip comments, blank, and short lines
        if (line[0] == '#' || line[0] == '\n' || strlen(line) < 2)
        {
            continue;
        }

        char func[32], arg1[128], expected[256];
        int count = sscanf(line, "%31s %127s %255s", func, arg1, expected);

        //skip if line doesn't parse into 3 parts
        if (count != 3)
        {
            continue;
        }

        char output[256];
        total++;

        if (strcmp(func, "oct_to_bin") == 0)
        {
            oct_to_bin(arg1, output);
        }
        else if (strcmp(func, "oct_to_hex") == 0)
        {
            oct_to_hex(arg1, output);
        }
        else if (strcmp(func, "hex_to_bin") == 0)
        {
            hex_to_bin(arg1, output);
        }
        else if (strcmp(func, "to_sign_magnitude") == 0) 
        {
            int32_t n = atoi(arg1);
            to_sign_magnitude(n, output);
        }
        else if (strcmp(func, "to_ones_complement") == 0) 
        {
            int32_t n = atoi(arg1);
            to_ones_complement(n, output);
        }
        else if (strcmp(func, "to_twos_complement") == 0) 
        {
            int32_t n = atoi(arg1);
            to_twos_complement(n, output);
        }
        else
        {
            printf("Unknown function: %s\n", func);
            continue;
        }

        if (strcmp(output, expected) == 0)
        {
            printf("Test %d: %s(%s) -> Expected: \"%s\", Got: \"%s\" [PASS]\n", 
                total, func, arg1, expected, output);
            passed++;
        }
        else
        {
            printf("Test %d: %s(%s) -> Expected: \"%s\", Got: \"%s\" [FAIL]\n", 
                total, func, arg1, expected, output);
        }
    }
    fclose(file);
    printf("\nSummary: %d/%d tests passed\n", passed, total);
    return 0;
    
}