/*
Part A - Mystery Caches
*/

#include <stdlib.h>
#include <stdio.h>

#include "support/mystery-cache.h"

/*
 * NOTE: When using access_cache() you do not need to provide a "real" memory
 * addresses. You can use any convenient integer value as a memory address,
 * you should not be able to cause a segmentation fault by providing a memory
 * address out of your programs address space as the argument to access_cache.
 */

/*
   Returns the size (in B) of each block in the cache.
*/
int get_block_size(void) {
  /* YOUR CODE GOES HERE */
access_cache(0);
  int i = 1;
  while (access_cache(i) == TRUE) {
    i++;
  }
  return i;

}
/*
   Returns the size (in B) of the cache.
*/


int get_cache_size(int block_size) {
  /* YOUR CODE GOES HERE */
  int i, j;
  flush_cache();
  for (i = 0; i < 1000000; i+= block_size) {
    access_cache(i);
    for (j = 0; j <= i; j+= block_size)
      if (access_cache(j) == FALSE)
        return i;


  }
  return -1;
}

/*
   Returns the associativity of the cache.
*/
int get_cache_assoc(int size) {
  /* YOUR CODE GOES HERE */
 int i = 0;
  int cache_check = 1;
  int assoc = 0;
  flush_cache();
  access_cache(0);
  while (access_cache(0)) {
    i = size;
    assoc = 0;
    while (i < cache_check) {
      i += size;
      assoc++;
      access_cache(i);
    }
    cache_check += size;
  }

  return assoc;
}

int main(void) {
  int size;
  int assoc;
  int block_size;

  cache_init(0, 0);

  block_size = get_block_size();
  size = get_cache_size(block_size);
  assoc = get_cache_assoc(size);

  printf("Cache block size: %d bytes\n", block_size);
  printf("Cache size: %d bytes\n", size);
  printf("Cache associativity: %d\n", assoc);

  return EXIT_SUCCESS;
}

