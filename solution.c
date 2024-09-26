#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cJSON.h"

long long decode_value(const char *value, int base) {
    long long result = 0;
    int length = strlen(value);
    for (int i = 0; i < length; i++) {
        char digit = value[i];
        int num;
        if (digit >= '0' && digit <= '9') {
            num = digit - '0';
        } else {
            num = digit - 'A' + 10;
        }
        result = result * base + num;
    }
    return result;
}

double lagrange_interpolation(int x[], long long y[], int k) {
    double result = 0;
    for (int i = 0; i < k; i++) {
        double term = y[i];
        for (int j = 0; j < k; j++) {
            if (i != j) {
                term *= (0 - x[j]) / (double)(x[i] - x[j]);
            }
        }
        result += term;
    }
    return result;
}

void parse_json_file(const char *filename, int *x, long long *y, int *n, int *k) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);
    char *data = (char *)malloc(length + 1);
    fread(data, 1, length, file);
    fclose(file);

    cJSON *json = cJSON_Parse(data);
    if (json == NULL) {
        printf("Error parsing JSON\n");
        return;
    }

    cJSON *keys = cJSON_GetObjectItem(json, "keys");
    *n = cJSON_GetObjectItem(keys, "n")->valueint;
    *k = cJSON_GetObjectItem(keys, "k")->valueint;

    for (int i = 1; i <= *n; i++) {
        char index_str[10];
        sprintf(index_str, "%d", i);

        cJSON *root = cJSON_GetObjectItem(json, index_str);
        int base = atoi(cJSON_GetObjectItem(root, "base")->valuestring);
        const char *value = cJSON_GetObjectItem(root, "value")->valuestring;

        x[i - 1] = i;
        y[i - 1] = decode_value(value, base);
    }

    cJSON_Delete(json);
    free(data);
}

int main() {
    int n, k;
    int x[100];
    long long y[100];

    parse_json_file("testcase.json", x, y, &n, &k);

    double constant_term = lagrange_interpolation(x, y, k);

    printf("The constant term c is: %lf\n", constant_term);

    return 0;
}
