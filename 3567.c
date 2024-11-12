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
    int M = strlen(pat);
    int N = strlen(txt);
    int lps[M];
    computeLPSArray(pat, M, lps);
    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == M) {
            return i - j; // found pattern at index i - j
        } else if (i < N && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i = i + 1;
            }
        }
    }

    return -1; // pattern not found
}


int main() {
    int M, N;
    char S[MAX_LEN];

    // Read inputs
    scanf("%d %d", &M, &N);
    scanf("%s", S);

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
    // printf("%s\n", cleaned_dna);


    // Extract the palindromic sequence
    char palindrome[MAX_LEN];
    strncpy(palindrome, cleaned_dna + start, M/2);
    palindrome[M/2] = '\0';
    // printf("%s\n", palindrome);

    // Reverse the palindrome
    char reversed_palindrome[MAX_LEN];
    strcpy(reversed_palindrome, palindrome);
    reverse_string(reversed_palindrome, M/2);


    int pos = KMPSearch(reversed_palindrome, cleaned_dna + start + M/2);
    // if (pos != -1) {
    //     printf("Reverse palindrome found at index %d\n", pos);
    // } else {
    //     printf("Reverse palindrome not found\n");
    // }

    int j = start + (M/2) + pos;
    int k = start + M + pos;
    // Modify the second half of the palindrome

    // for (int i = j; i < j + (M/2); i++) {
    //     printf("%c", cleaned_dna[i]);
    // }
    // printf("\n");
    for (int i = j; i < j + (M/2); i++) {
        cleaned_dna[i] = transform_nucleotide(cleaned_dna[i]);
    }
    // for (int i = j; i < j + (M/2); i++) {
    //     printf("%c", cleaned_dna[i]);
    // }
    // printf("\n");

    // Print the modified DNA sequence
    printf("%s\n", cleaned_dna);

    return 0;
}