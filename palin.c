#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 201

// Function to check if a character is a standard DNA nucleotide
int is_standard_dna(char c) {
    return c == 'A' || c == 'T' || c == 'C' || c == 'G';
}

// Function to transform a nucleotide according to the pairing rules
char transform_nucleotide(char c) {
    switch (c) {
        case 'A': return 'T';
        case 'T': return 'A';
        case 'C': return 'G';
        case 'G': return 'C';
        default: return c; // Should not reach here
    }
}

// Function to reverse a string
void reverse_string(char *s, int len) {
    for (int i = 0; i < len / 2; i++) {
        char temp = s[i];
        s[i] = s[len - i - 1];
        s[len - i - 1] = temp;
    }
}

// find the reverse of the palindrome in the cleaned_dna using KMP algorithm
// KMP algorithm to find the reverse of the palindrome in the cleaned_dna
void computeLPSArray(char* pat, int M, int* lps) {
    int len = 0;
    lps[0] = 0; // lps[0] is always 0
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

int KMPSearch(char* pat, char* txt) {
    int longest = 0;
    int M = strlen(pat);
    int N = strlen(txt);
    int lps[M];
    computeLPSArray(pat, M, lps);
    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N) {
        //printf("i: %d, j: %d\n", i, j);
            if (j >= N - i - 1) {
                break;
            }
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j > longest) {
            longest = j;
        }
        if (j == M) {
            return M;
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i = i + 1;
            }
        }
    }
    return longest; // pattern not found
}

// Function to compute the prefix function (LPS array) for KMP algorithm
void compute_prefix_function(char* pat, int M, int* lps) {
    int len = 0;
    lps[0] = 0; // lps[0] is always 0
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}


int main() {
    int M, N;
    char S[MAX_LEN];

    // Read inputs
    scanf("%d", &N);
    scanf("%s", &S);
    S[N] = '\0';

    // Find the start of the palindromic sequence
    int start = 0;
    while (start < N && is_standard_dna(S[start])) {
        start++;
    }
    if (start == N) start = 0;

    // Create a new array to store the cleaned DNA sequence
    char cleaned_dna[MAX_LEN];
    int index = 0;
    // Traverse the string S and copy only the standard DNA characters to cleaned_dna
    for (int i = 0; i < N; i++) {
        if (is_standard_dna(S[i])) {
            cleaned_dna[index++] = S[i];
        }
    }
    cleaned_dna[index] = '\0'; // Null-terminate the new array
    printf("cleaned: %s\n", cleaned_dna);
    char pattern[MAX_LEN];
    strcpy(pattern, cleaned_dna+start);
    char reverse_data[MAX_LEN];
    strcpy(reverse_data, pattern);
    for(int i = 0; i < strlen(pattern); i++){
        pattern[i] = transform_nucleotide(pattern[i]);
    }
    //printf("1. %s\n", pattern);
    reverse_string(reverse_data, strlen(reverse_data));
    //printf("2. %s\n", reverse_data);
    int longest = KMPSearch(pattern, reverse_data);
    if (longest >= strlen(pattern)/2){
        longest = strlen(pattern)/2;
    }

    //printf("%d\n", longest);


    char first_half[MAX_LEN];
    strcpy(first_half, cleaned_dna + start);
    first_half[longest] = '\0';

    char second_half[MAX_LEN];
    strcpy(second_half, first_half);
    reverse_string(second_half, strlen(second_half));
    for(int i = 0; i < strlen(second_half); i++){
        second_half[i] = transform_nucleotide(second_half[i]);
    }

    if (longest*2 < 6){
        printf("-1\n");
        printf("Not a Super Smart Sheep\n");
    } else {
        printf("%d\n", longest*2);
        printf("%s %s\n", first_half, second_half);
    }

    return 0;
}