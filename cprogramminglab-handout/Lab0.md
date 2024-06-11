# Introduction

Lab0主要一开始是搭建基础的必要环境，复习一下基础的 C 指针操作，内存管理获取和释放

题目是借助链表实现栈和队列的的基本操作，要说也是可以考成简单的算法题，主要考察基本功XD

## 需求

一开始提供的是链表的结构体

```c
typedef struct ELE {
    /* Pointer to array holding string.
       This array needs to be explicitly allocated and freed */
    char *value;
    struct ELE *next;
} list_ele_t;

/* Queue structure */
typedef struct {
    list_ele_t *head;  /* Linked list of elements */
    /*
      You will need to add more fields to this structure
      to efficiently implement q_size and q_insert_tail
    */
} queue_t;
```
为了实现后续的需求，我们可能需要在链表的定义中追加新的字段

## 模板分析

在提供的代码中，定义的链表元素 ELE 包含两个字段。其中的 value 字段是指向数组的引用

>在 C 中 String 的实现本质上是一个 char 类型的数组 (当然 Java 也是，但是提供了更为高层的 API ，但是 C 没有提供 XD)

代码中也提到了，这个 value char 数组需要被显式地声明和释放

同时为了存储 l 长度的字符，这个 value 数组需要定义 l+1 的长度，其中多出来的一个长度是为了预留给字符串终止符\0的

此外即使**对于相同内容的 string 在这里也应当指向不同的内存对象**，而不是不同的指针相同的内存实体

我们定义：NULL队列是队列的指针指向NULL，而空队列是指队列指针不为NULL，但是head域指针为NULL

# Programming Task

修改 `queue.h` 以及 `queue.c` 中定义的内容来实现需求

## q_new

创建一个新的**空队列**

```c
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)
    {
      return NULL;
    }
    // Empty queue is a queue with basic structure but head points to NULL
    q->head = NULL;
    return q;
}
```

## q_free

清除队列中**所有**所占内存

为了递归地处理每一个节点的value同时燃烧自己全身而退XD，这里新增了一个函数 `free_node`

```c
/* Free all storage used by queue */
void q_free(queue_t *q)
{
  /* How about freeing the list elements and the strings? */
  if (q->head != NULL)
  {
    free_node(q->head);
  }
  /* Free queue structure */
  free(q);
}

/* Free the list elements and the strings*/
void free_node(list_ele_t *node)
{
  if (node == NULL)
  {
    return;
  }
  free(node->value);
  if (node->next != NULL)
  {
    free_node(node->next);
  }
  free(node);
}
```

## q_insert_head

单链表的头插法(模拟入栈push操作)

这里两个要点复习一下：
- 正如之前所说,C中字符串需要多分配一个 Terminator \0 的长度，因此 malloc 的时候应当是 `malloc(strlen(s)+1)` 
- 字符串拷贝可以使用 `strcpy(dest,source)` 

