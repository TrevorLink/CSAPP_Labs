/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
  queue_t *q = malloc(sizeof(queue_t));
  if (q == NULL)
  {
    return NULL;
  }
  q->head = NULL;
  q->tail = NULL;
  q->count = 0;
  return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
  if (q == NULL)
  {
    return;
  }
  list_ele_t *curr = q->head;
  while (curr != NULL)
  {
    list_ele_t *tmp = curr->next;
    free(curr->value);
    free(curr);
    curr = tmp;
  }
  free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
  list_ele_t *newh;
  if (q == NULL)
  {
    return false;
  }
  newh = malloc(sizeof(list_ele_t));
  if (newh == NULL)
  {
    return false;
  }
  // 注意C中String需要额外考虑一个终止符\0的长度
  char *newvalue = malloc(strlen(s) + 1);
  if (newvalue == NULL)
  {
    free(newh); // 有借有还，每一次malloc都要养成在分支上free的习惯
    return false;
  }
  strcpy(newvalue, s); // 复制String的内容
  newh->value = newvalue;
  newh->next = q->head;
  q->head = newh;
  q->count++;
  // 初始化队尾指针
  if (q->count == 1)
  {
    q->tail = q->head;
  }
  return true;
}

/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
  /* Remember: It should operate in O(1) time */
  list_ele_t *newtail;
  if (q == NULL)
  {
    return false;
  }
  newtail = malloc(sizeof(list_ele_t));
  if (newtail == NULL)
  {
    return false;
  }
  char *newvalue = malloc(strlen(s) + 1);
  if (newvalue == NULL)
  {
    free(newtail);
    return false;
  }
  strcpy(newvalue, s);
  newtail->value = newvalue;
  newtail->next = NULL;
  q->tail->next = newtail;
  q->tail = newtail;
  q->count++;
  return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
  // Return false if queue is NULL or empty.
  if (q == NULL || q->head == NULL)
  {
    return false;
  }
  if (sp != NULL)
  {
    strncpy(sp, q->head->value, bufsize - 1);
    sp[bufsize - 1] = '\0';
  }
  list_ele_t *temp = q->head;
  q->head = q->head->next;
  free(temp->value);
  free(temp);
  q->count--;
  return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
  if (q == NULL || q->head == NULL)
  {
    return 0;
  }

  /* Remember: It should operate in O(1) time */
  return q->count;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
  /* You need to write the code for this function */
  if (q == NULL || q->head == NULL)
  {
    return;
  }
  list_ele_t *slow = q->head;
  list_ele_t *fast = q->head->next;
  list_ele_t *start = q->head;
  while (fast != NULL)
  {
    list_ele_t *tmp = fast->next;
    fast->next = slow;
    slow = fast;
    fast = tmp;
  }
  // 反转后不要忘记设置tail以及tail的next域
  q->tail = start;
  q->tail->next = NULL;
  q->head = slow;
}
