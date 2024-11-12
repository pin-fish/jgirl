#include <stdio.h>
#include <stdbool.h>
#define MAXN 11
#define MAXL 11

// n, l, map and target will not change
int n, l, map[MAXN][MAXN];
char target[MAXL];

#ifdef DEBUG
char path[MAXL];
int endr = -1, endc = -1;
#endif

bool string_match(int index, int dif, int r, int c) {
  // There are too many characters different from target
  if(dif < 0) return false;

  // Run out of the map
  if(r < 0 || r >= n || c < 0 || c >= n) return false;

  // Successfully match target
  if(index == l) return true;
  
#ifdef DEBUG
  path[index] = map[r][c] + '0';
  endr = r;
  endc = c;
#endif

  // The character are different from target, so the quota of dif minus 1
  if(map[r][c] != target[index] - '0') dif--; 

  index++;

  if(string_match(index, dif, r - 1, c)) return true;
  if(string_match(index, dif, r + 1, c)) return true;
  if(string_match(index, dif, r, c - 1)) return true;
  if(string_match(index, dif, r, c + 1)) return true;
  return false;
}

bool valid_map(int dif) {
  // Find all paths started from different elements
  for(int r = 0; r < n; r++) {
    for(int c = 0; c < n; c++) {
      if(string_match(0, dif, r, c)) 
        return true;
    }
  }
  return false;
}

int main() {
  int dif;
  scanf("%d%d%d%s", &n, &l, &dif, &target);
  for(int r = 0; r < n; r++)
    for(int c = 0; c < n; c++) scanf("%d", &map[r][c]);

  if(valid_map(dif)) {
    printf("true");

#ifdef DEBUG
    // The path will be the first valid path as we return immediately after matching is successful
    path[l] = '\0';
    printf(" %s, r is %d, c is %d\n", path, endr, endc);
#endif

  }
  else printf("false");

  return 0;
}