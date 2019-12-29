#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "params.h"
#include "bm.h"
// qsortのための比較関数
int str_len_cmp_r(const void * a, const void * b) {
    return (int)strlen(*(char**)b) - (int)strlen(*(char**)a);
}

void solve(char * t, char** s, int n, Params* p) {
  // 文字列の長さでソートしたら精度が上がる
  qsort(s, (size_t)n , sizeof(char*), str_len_cmp_r);

  int t_length = (int)strlen(t);

  // s[i]をそれぞれ見ていって, tのある部分とマッチしたらそこを書き換え.
  for (int i = 0; i < p->bm_search_limit_length; i++) {
    int s_length = (int)strlen(s[i]);
    char * match = bm_search(t, t_length, s[i], s_length);
    if (match == NULL) {
      continue;
    }
    for (int j = 0; j < s_length; j++) {
      match[j] = s[i][j];
    }
  }

  // xが残っていたら取り合えずaに置き換え
  for (int i = 0; i < t_length; i ++) {
    if (t[i] == 'x') {
      t[i] = 'a';
    }
  }
}