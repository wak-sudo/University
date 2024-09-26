/*
 * Binary search with linearly placed tree levels.
 *
 * Intel® Core™ i5-6600 CPU @ 3.30GHz
 *
 * $ ./binsearch -S 0x5bab3de5da7882ff -n 23 -t 24 -v 0
 * Time elapsed: 7.616777 seconds.
 * $ ./binsearch -S 0x5bab3de5da7882ff -n 23 -t 24 -v 1
 * Time elapsed: 2.884369 seconds.
 */
#include "binsearch.h"

bool binsearch0(T *arr, long size, T x) {
  do {
    size >>= 1;
    T y = arr[size];
    if (y == x)
      return true;
    if (y < x)
      arr += size + 1;
  } while (size > 0);
  return false;
}

inline int log2c(int n)
{
  int result = 0;
  while(n >> 1)
  {
    n >>= 1;
    result++;
  }
  return result;
}

void linearizeHelp(T *dst, T *src, int l, int r, int maxLevel, int dstIndex) {
  int mid = l + (r-l)/2;
  dst[dstIndex] = src[mid];
  if(maxLevel - 1 != 0)
  {
    linearizeHelp(dst, src, l, mid-1, maxLevel-1, (dstIndex+1)*2 - 1);
    linearizeHelp(dst, src, mid+1, r, maxLevel-1, (dstIndex+1)*2);
  }  
}

void linearize(T *dst, T *src, long size) {
  if(size == 0) return;
  linearizeHelp(dst, src, 0, size-1, log2c(size+1), 0);
}

bool binsearch1(T *arr, long size, T x) {
  int i = 0;
  while(i < size)
  {
    if(arr[i] == x) return true;
    else if(x < arr[i]) i = 2*i+1;
    else i = 2*(i+1);
  }
  return false;
}
