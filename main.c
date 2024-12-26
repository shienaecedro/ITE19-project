#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if the Roman numeral is valid
int isValidRomanNumeral(char *str) {
    int i;
    for (i = 0; str[i] != '\0'; i++) {
        if ((str[i] == 'I' || str[i] == 'V' || str[i] == 'X' || str[i] == 'L' || str[i] == 'C' || str[i] == 'D' || str[i] == 'M')) {
            return 1;
        }
    }
    return 0;
}

// Function to get the decimal value of a single Roman numeral character
int romanToDecimalChar(char c) {
    switch (c) {
        case 'I': return 1;
        case 'V': return 5;
        case 'X': return 10;
        case 'L': return 50;
        case 'C': return 100;
        case 'D': return 500;
        case 'M': return 1000;
        default: return 0;
    }
}

// Function to convert a Roman numeral string to a decimal integer
int romanToDecimal(char *str) {
    int total = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        int currentVal = romanToDecimalChar(str[i]);
        int nextVal = romanToDecimalChar(str[i + 1]);

        if (currentVal < nextVal) {
            total -= currentVal;
        } else {
            total += currentVal;
        }
    }
    return total;
}

// Function to perform the arithmetic operation
int performOperation(int value1, int value2, char operator) {
    switch (operator) {
        case '+': return value1 + value2;
        case '-': return value1 - value2;
        case '*': return value1 * value2;
        case '/':
            if (value2 != 0) {
                return value1 / value2;
            } else {
                printf("Error: Cannot divide by zero.\n");
                return 0;
            }
        default: return 0;
    }
}

void outputFile(const char *words) {
    FILE *file;

    file = fopen("output.txt", "a");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return;
    }
    fprintf(file, "%s\n", words);
    fclose(file);
}

// Function to convert decimal number to words
void decimalToWords(int num, char *words) {
    // Arrays for number to words conversion
    char *units[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char *teens[] = {"", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    char *tens[] = {"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
    char *hundred = "hundred";
    char *thousand = "thousand";
    char *million = "million";

    words[0] = '\0'; // Initialize the words array to an empty string

    if (num < 0) {
        strcat(words, "negative ");
        num = -num;
    }
    if (num >= 1000000) {
        strcat(words, units[num / 1000000]);
        strcat(words, " ");
        strcat(words, million);
        strcat(words, " ");
        num %= 1000000;
    }
    if (num >= 100000) {
        strcat(words, tens[num / 100000]);
        strcat(words, " ");
        strcat(words, thousand);
        strcat(words, " ");
        num %= 100000;
    }
    if (num >= 20000) {
        strcat(words, tens[num / 10000]);
        strcat(words, " ");
        strcat(words, thousand);
        strcat(words, " ");
        num %= 10000;
    }
    if (num >= 1000) {
        strcat(words, units[num / 1000]);
        strcat(words, " ");
        strcat(words, thousand);
        strcat(words, " ");
        num %= 1000;
    }
    if (num >= 100) {
        strcat(words, units[num / 100]);
        strcat(words, " ");
        strcat(words, hundred);
        strcat(words, " ");
        num %= 100;
    }
    if (num >= 20) {
        strcat(words, tens[num / 10]);
        strcat(words, " ");
        num %= 10;
    } else if (num >= 11 && num <= 19) {
        strcat(words, teens[num - 10]);
        return;
    }
    if (num > 0 || (num == 0 && words[0] == '\0')) {
        strcat(words, units[num]);
    }
}

// Function to read a line from the file and process it
void readFromFile(char *line) {
    char roman1[50], roman2[50];
    char operator;
    int result, value1, value2;
    char words[256];

    if (sscanf(line, "%s %c %s", roman1, &operator, roman2) == 3) {
        if (isValidRomanNumeral(roman1) && isValidRomanNumeral(roman2)) {
            value1 = romanToDecimal(roman1); // Convert the first Roman numeral to decimal
            value2 = romanToDecimal(roman2); // Convert the second Roman numeral to decimal
            result = performOperation(value1, value2, operator);
            decimalToWords(result, words);
            outputFile(words);
        } else {
            printf("Error: Invalid Roman Numeral.\n");
        }
    } else {
        printf("Error: Invalid line format\n");
    }

}

int main() {
    FILE *file;
    char line[256];

    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error: Could not open file.\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) {
        readFromFile(line);
    }

    printf("Successful!");

    fclose(file);
    return 0;
}
