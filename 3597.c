#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAXN 61
#define MAXL 11

int n, l, map[MAXN][MAXN];
char target[MAXL];

const int power_of_2[MAXL] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

#ifdef DEBUG
char path[MAXL];
char correct_path[MAXL];
#endif

int min(int a, int b) {
  return (a < b) ? a : b;
}

void string_match(int index, int dif, int r, int c, int *min_dif) {
  // dif is too large and it is no way to become min_dif
  if(dif > *min_dif) return;

  // Run out of the map
  if(r < 0 || r >= n || c < 0 || c >= n) return;

  // Successfully match target
  if(index == l) {
    *min_dif = min(*min_dif, dif);

#ifdef DEBUG
    if(*min_dif == dif) strncpy(correct_path, path, l);
#endif

    return;
  }
  
#ifdef DEBUG
  path[index] = map[r][c] + '0';
#endif

  // If the character is different from the target, then the corresponding position need to become 1
  if(map[r][c] != target[index] - '0') dif += power_of_2[l - index - 1]; 
  index++;

  string_match(index, dif, r - 1, c, min_dif);
  string_match(index, dif, r + 1, c, min_dif);
  string_match(index, dif, r, c - 1, min_dif);
  string_match(index, dif, r, c + 1, min_dif); 
  return;
}

int path_go_through() {
  int min_dif = 1024; // min_dif of a valid path is at most 32767 (1111111111)
  
  // Find all paths started from different elements
  for(int r = 0; r < n; r++) 
    for(int c = 0; c < n; c++) 
      string_match(0, 0, r, c, &min_dif);
    
  return min_dif;
}

int main() {
  scanf("%d%d%s", &n, &l, &target);
  for(int r = 0; r < n; r++)
    for(int c = 0; c < n; c++) scanf("%d", &map[r][c]);

  printf("%d\n", path_go_through());
    
#ifdef DEBUG
    // The path will be the first valid path as we return immediately after matching is successful
    correct_path[l] = '\0';
    printf("%s\n", correct_path);
#endif
  return 0;
}