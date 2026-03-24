#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "input_utils.h"

static int readLineRaw(char* outBuffer, size_t outSize) {
    if (outSize < 2 || outSize > (size_t)INT_MAX) {
        return 0;
    }

    if (fgets(outBuffer, (int)outSize, stdin) == NULL) {
        return 0;
    }

    size_t len = strlen(outBuffer);
    if (len > 0 && outBuffer[len - 1] == '\n') {
        outBuffer[len - 1] = '\0';
    } else {
        int ch;
        do {
            ch = getchar();
        } while (ch != '\n' && ch != EOF);
    }

    return 1;
}

int readLine(const char* prompt, char* outBuffer, size_t outSize) {
    if (prompt != NULL) {
        printf("%s", prompt);
    }

    if (outBuffer == NULL || outSize == 0) {
        return 0;
    }

    if (!readLineRaw(outBuffer, outSize)) {
        printf("Input error. Please try again.\n");
        return 0;
    }

    if (outBuffer[0] == '\0') {
        printf("Input cannot be empty.\n");
        return 0;
    }

    return 1;
}

int readInt(const char* prompt, int* outValue) {
    char buffer[128];
    char* endPtr;
    long parsed;

    if (prompt != NULL) {
        printf("%s", prompt);
    }

    if (outValue == NULL) {
        return 0;
    }

    if (!readLineRaw(buffer, sizeof(buffer))) {
        printf("Input error. Please try again.\n");
        return 0;
    }

    parsed = strtol(buffer, &endPtr, 10);
    if (endPtr == buffer || *endPtr != '\0') {
        printf("Invalid input. Enter a valid integer.\n");
        return 0;
    }
    if (parsed < (long)INT_MIN || parsed > (long)INT_MAX) {
        printf("Invalid input. Integer is out of range.\n");
        return 0;
    }

    *outValue = (int)parsed;
    return 1;
}

int readPositiveInt(const char* prompt, int* outValue) {
    if (!readInt(prompt, outValue)) {
        return 0;
    }
    if (*outValue <= 0) {
        printf("Invalid input. Enter a value greater than 0.\n");
        return 0;
    }
    return 1;
}

int readNonNegativeInt(const char* prompt, int* outValue) {
    if (!readInt(prompt, outValue)) {
        return 0;
    }
    if (*outValue < 0) {
        printf("Invalid input. Enter a non-negative value.\n");
        return 0;
    }
    return 1;
}

int readFloat(const char* prompt, float* outValue) {
    char buffer[128];
    char* endPtr;
    float parsed;

    if (prompt != NULL) {
        printf("%s", prompt);
    }

    if (outValue == NULL) {
        return 0;
    }

    if (!readLineRaw(buffer, sizeof(buffer))) {
        printf("Input error. Please try again.\n");
        return 0;
    }

    parsed = strtof(buffer, &endPtr);
    if (endPtr == buffer || *endPtr != '\0') {
        printf("Invalid input. Enter a valid number.\n");
        return 0;
    }
    if (!isfinite(parsed)) {
        printf("Invalid input. Number must be finite.\n");
        return 0;
    }

    *outValue = parsed;
    return 1;
}

int readNonNegativeFloat(const char* prompt, float* outValue) {
    if (!readFloat(prompt, outValue)) {
        return 0;
    }
    if (*outValue < 0.0f) {
        printf("Invalid input. Enter a non-negative value.\n");
        return 0;
    }
    return 1;
}
