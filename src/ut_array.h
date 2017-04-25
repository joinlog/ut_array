/*
 * ut_array.h
 *
 *  Created on: 2017-4-21
 *      Author: ZhaoYun
 */

#ifndef UT_ARRAY_H_
#define UT_ARRAY_H_

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"

/*if your compile tool not support C99, the header file stdbool.h may not exist.
 * so you SHOULD define these below:
 * #define bool  int
 * #define true  1
 * #define false 0
 * */
#include "stdbool.h"

////////////////////////////////////////////////////////////////////////////////
#define UT_ARRAY_CAP_DEFAULT 32
////////////////////////////////////////////////////////////////////////////////

typedef struct UT_array_handle {
  int num;
  int cap;
  int cap_add_every_time;
  int nex;
  int bytes_per_item;
  void *pdata;
}UT_array_handle;

////////////////////////////////////////////////////////////////////////////////
#define UT_ARRAY_ITER(ah, idx, pitem)                                          \
for((*(char**)(&(pitem)))=(char *)((ah)->pdata), (idx)=0;                     \
    (idx) < (ah)->num;                                                         \
    ++(idx), (*(char**)(&(pitem)))=(char *)((ah)->pdata+idx*(ah)->bytes_per_item) )

#define GET_ITEM_PTR(ah, idx) ( ((idx) < 0 || (idx) >= (ah)->num) ? NULL : (void *)((char *)((ah)->pdata) + (idx) * (ah)->bytes_per_item) )

UT_array_handle *
ut_array_init(int bytes_per_item, int cap_add_every_time);
bool
ut_array_copy(UT_array_handle **dst, UT_array_handle *src);
void
ut_array_free(UT_array_handle **ah);
bool
ut_array_add(UT_array_handle *ah, void *pitem);
void
ut_array_sort(UT_array_handle *ah, int (*fun)(const void*, const void*));
void *
ut_array_find(UT_array_handle *ah, const void *pdst, int (*fun)(const void*, const void*));
int
ut_array_num(const UT_array_handle *ah);
bool
ut_array_num_set(UT_array_handle *ah, int num);
bool
ut_array_cover_1_item(UT_array_handle *ah, int from_idx, int to_idx);
////////////////////////////////////////////////////////////////////////////////





#endif /* UT_ARRAY_H_ */
