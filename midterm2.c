#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// Helper function to check if two characters are k shifts apart
bool is_valid_shift(char original, char encrypted, int k) {
    // Calculate the backward shift using the key k
    char shifted = original - k;
    if (shifted < 'a') {
        shifted += 26;
    }
    return shifted == encrypted;
}

// Function to determine the smallest key
int find_smallest_key(const char *original, const char *encrypted) {
    int lenA = strlen(original);
    int lenB = strlen(encrypted);
    
    // Iterate through possible keys
    for (int k = 0; k <= 25; k++) {
        int j = 0;  // Pointer for the original string
        
        // Iterate through the encrypted string
        for (int i = 0; i < lenB; i++) {
            // If the current character matches after shifting, move to the next in original
            if (j < lenA && (original[j] == encrypted[i] || is_valid_shift(original[j], encrypted[i], k))) {
                j++;  // Move to the next character in the original string
            }
        }
        //printf("k = %d, ", k);
        //printf("j = %d\n", j);
        
        // If all characters in the original string are matched
        if (j == lenA) {
            return k;
        }
    }
    
    // If no valid key was found, return -1
    return -1;
}

int main() {
    char original[1005], encrypted[1005];
    
    // Input the original and encrypted messages
    scanf("%s", original);
    scanf("%s", encrypted);
    
    // Find and print the smallest key
    int result = find_smallest_key(original, encrypted);
    printf("%d\n", result);
    
    return 0;
}
