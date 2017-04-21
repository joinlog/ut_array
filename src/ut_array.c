/*
 * ut_array.c
 *
 *  Created on: 2017-4-21
 *      Author: ZhaoYun
 */

#include "ut_array.h"

////////////////////////////////////////////////////////////////////////////////
UT_array_handle *
ut_array_init(int bytes_per_item, int cap_add_every_time)
{
  UT_array_handle *ah = (UT_array_handle *)calloc(1, sizeof(UT_array_handle ));
  if (ah == NULL) {
    printf("E <%s>init UT_array_handle fail", __FUNCTION__);
    return NULL;
  }

  if (cap_add_every_time == 0) {
    cap_add_every_time = UT_ARRAY_CAP_DEFAULT;
  }

  ah->bytes_per_item = bytes_per_item;
  ah->cap = 0;
  ah->cap_add_every_time = cap_add_every_time;
  ah->nex = 0;
  ah->num = 0;
  ah->pdate = NULL;

  return ah;
}

void
ut_array_free(UT_array_handle **ah)
{
  if (ah == NULL) {
    printf("E <%s> UT_array_handle==NULL fail", __FUNCTION__);
    return;
  }
  free((*ah)->pdate);
  free(*ah);
  *ah = NULL;
}

bool
ut_array_add(UT_array_handle *ah, void *pitem)
{
  if (ah == NULL) {
    printf("E <%s> UT_array_handle==NULL fail", __FUNCTION__);
    return false;
  }
  if (pitem == NULL) {
    printf("E <%s> pitem==NULL fail", __FUNCTION__);
    return false;
  }

  if (ah->pdate == NULL) {
    ah->pdate = calloc(ah->cap_add_every_time, ah->bytes_per_item);
    if (ah->pdate == NULL) {
      return false;
    }
    ah->cap = ah->cap_add_every_time;
    ah->num = 0;
  }

  if (ah->num >= ah->cap) {
    ah->pdate = realloc(ah->pdate, (ah->cap + ah->cap_add_every_time) * ah->bytes_per_item);
    if (ah->pdate == NULL) {
      return false;
    }
    ah->cap += ah->cap_add_every_time;
  }
  memcpy(ah->pdate + ah->bytes_per_item * ah->num, pitem, ah->bytes_per_item);
  ah->num++;
  return true;
}

void
ut_array_sort(UT_array_handle *ah, int (*fun)(const void*, const void*))
{
  if (ah == NULL) {
    printf("E <%s> UT_array_handle==NULL fail", __FUNCTION__);
    return;
  }
  if (fun == NULL) {
    printf("E <%s> sort function==NULL fail", __FUNCTION__);
    return;
  }
  qsort(ah->pdate, ah->num, ah->bytes_per_item, fun);
}

int
ut_array_num(UT_array_handle *ah)
{
  if (ah == NULL) {
    printf("E <%s> UT_array_handle==NULL fail", __FUNCTION__);
    return -1;
  }
  return ah->num;
}

bool
ut_array_num_set(UT_array_handle *ah, int num)
{
  if (ah == NULL) {
    printf("E <%s> UT_array_handle==NULL fail", __FUNCTION__);
    return false;
  }
  if (num < 0 || num > ah->cap) {
    printf("E <%s> num=%d out of array cap=%d fail", __FUNCTION__, num, ah->cap);
    return false;
  }
  ah->num = num;
  return true;
}

/* copy item[from_idx] to item[to_idx] */
bool
ut_array_cover_1_item(UT_array_handle *ah, int from_idx, int to_idx)
{
  if (from_idx < 0 || from_idx >= ah->num) {
    printf("E <%s> from_idx=%d out of array num=%d fail", __FUNCTION__, from_idx, ah->num);
    return false;
  }
  if (to_idx < 0 || to_idx >= ah->num) {
    printf("E <%s> to_idx=%d out of array num=%d fail", __FUNCTION__, to_idx, ah->num);
    return false;
  }
  memcpy(ah->pdate + to_idx * ah->bytes_per_item, ah->pdate + from_idx * ah->bytes_per_item, ah->bytes_per_item);
  return true;
}

////////////////////////////////////////////////////////////////////////////////

