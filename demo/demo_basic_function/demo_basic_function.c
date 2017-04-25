/*
 * demo_basic_function.c
 *
 *  Created on: 2017-4-21
 *      Author: ZhaoYun
 */

#include "ut_array.h"
#include "assert.h"

typedef struct {
  int i;
  char c;
  float f;
  double g;
  void *ptr;
}test_t;

static void
ts_iterator(UT_array_handle *ah_test)
{
  int i = 0;
  test_t *ptmp_test;
  UT_ARRAY_ITER(ah_test, i, ptmp_test) {
    printf("[%d] i=%d c=%10c f=%.2f g=%.2f prt=%p\n", i, ptmp_test->i, ptmp_test->c, ptmp_test->f, ptmp_test->g, ptmp_test->ptr);
  }
}

static void
ts_add(UT_array_handle *ah_test)
{
  bool bret;
  int i = 0;
  test_t tmp_test;
  for (i = 0; i < 10; ++i) {

    tmp_test.i = i;
    tmp_test.c = i;
    tmp_test.f = i;
    tmp_test.g = i;
    tmp_test.ptr = (void *)i;

    bret = ut_array_add(ah_test, &tmp_test);
    if (bret == false) {
      printf("ut_array_add fail\n");
    }
  }
}

static int
cmp_func_test_i(const void*a, const void*b)
{
  test_t *pa = (test_t *)a;
  test_t *pb = (test_t *)b;
  // sort from big to small by i
  return (pb->i - pa->i);
}

static void
ts_del(UT_array_handle *ah_test)
{
  bool bret;
  // delete the second item, it's index in array is 1
  int del_item_idx = 1;
  int i = 0;
  test_t *ptmp_test;
  int num = ut_array_num(ah_test);

  for (i = del_item_idx; i < num - 1; ++i) {
    ut_array_cover_1_item(ah_test, i+1, i);
  }
  ut_array_num_set(ah_test, num - 1);
}

int main(int argc, char **argv)
{
  int i;
  int num = 0;
  // 0.initialize
  UT_array_handle *ah_test = NULL;
  ah_test = ut_array_init(sizeof(test_t), 0);
  assert(ah_test != NULL);

  printf("====================1.add function test===========================\n");
  // 1.add function test
  ts_add(ah_test);

  printf("====================2.iterator function test======================\n");
  // 2.iterator function test
  ts_iterator(ah_test);

  printf("====================3.sort function test==========================\n");
  // 3.sort function test
  ut_array_sort(ah_test, cmp_func_test_i);
  // 3.1check the result
  ts_iterator(ah_test);

  printf("====================4.get item number function test===============\n");
  // 4.get item number function test
  num = ut_array_num(ah_test);
  if (num < 0) {
    printf("ut_array_num fail\n");
  }
  printf("ut_array_num=%d\n", num);

  printf("====================5.set item number fucntion test================\n");
  // 5.set item number fucntion test
  --num;
  ut_array_num_set(ah_test, num);

  // 5.1check the result
  printf("ut_array_num=%d\n", num);
  num = ut_array_num(ah_test);
  printf("ut_array_num=%d\n", num);
  ts_iterator(ah_test);

  printf("====================6.delete item function test====================\n");
  // 6.delete item function test
  ts_del(ah_test);
  // 6.1check the result
  num = ut_array_num(ah_test);
  printf("ut_array_num=%d\n", num);
  ts_iterator(ah_test);

  printf("====================7.depth copy function test====================\n");
  UT_array_handle *ah_test_tmp;
  if (!ut_array_copy(&ah_test_tmp, ah_test) ) {
    printf("[E] ut_array_copy fail\n");
    return 1;
  }
  ts_iterator(ah_test_tmp);
  ut_array_free(&ah_test_tmp);

  printf("====================8.find function test====================\n");
  test_t tt;
  memset(&tt, 0, sizeof(test_t));
  tt.i = 7;
  test_t *ptt = (test_t *)ut_array_find(ah_test, (void *)&tt, cmp_func_test_i);
  if (ptt == NULL) {
    printf("[E] ut_array_find fail\n");
  } else {
    printf("ut_array_find %d success\n", tt.i);
  }

  printf("====================9.random access function test====================\n");
  num = ut_array_num(ah_test);
  for (i = 0; i < num; ++i) {
    ptt = (test_t *)GET_ITEM_PTR(ah_test, i);
    printf("[%d] i=%d c=%10c f=%.2f g=%.2f prt=%p\n", i, ptt->i, ptt->c, ptt->f, ptt->g, ptt->ptr);
    ptt->i++;
  }
  ts_iterator(ah_test);

  printf("====================0.match with ut_array_init=====================\n");
  // 0.match with ut_array_init
  ut_array_free(&ah_test);
  return 0;
}

