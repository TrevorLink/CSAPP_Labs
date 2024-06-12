# Introduction

Lab0主要一开始是搭建基础的必要环境，复习一下基础的 C 指针操作，内存管理获取和释放

题目是借助链表实现栈和队列的的基本操作，要说也是可以考成简单的算法题，主要考察基本功XD

## 基础环境设置

Lab0这里需要使用 Unix 环境来跑测试，如果是 Win 环境会缺失部分只有 Unix 上才有的函数头文件，因此 make 的时候会报错

这里直接使用 Docker 跑一个 Lab 专用的实验环境

[Docker File 在这里](../Dockerfile)

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
为了实现后续题目的需求，我们可能需要在链表的定义中追加新的字段

## 模板分析

在提供的代码中，定义的链表元素 ELE 包含两个字段。其中的 value 字段是指向数组的引用

>在 C 中 String 的实现本质上是一个 char 类型的数组 (当然 Java 也是，但是提供了更为高层的 API ，但是 C 没有提供 XD)

代码中也提到了，这个 value char 数组需要被显式地声明和释放

同时为了存储 l 长度的字符，这个 value 数组需要定义 l+1 的长度，其中多出来的一个长度是为了预留给字符串终止符\0的

此外即使**对于相同内容的 string 在这里也应当指向不同的内存对象**，而不是不同的指针相同的内存实体

我们定义：NULL队列是队列的指针指向NULL，而空队列是指队列指针不为NULL，但是head域指针为NULL


# 调试测试

## Makefile

默认的 Makefile 其实已经足够

但是在直接输入 `make` 的时候报错，说是在 `harness.h` `report.h` 等和实验主要内容不相关的代码中出现了 `Multiple Definition`

因此修改 `report.h` 内容，在这些变量前加 `extern` 关键字（没有出现上面的错误当然可以不加）

```c
/* Maximum number of megabytes that application can use (0 = unlimited) */
extern int mblimit;

/* Maximum number of seconds that application can use.  (0 = unlimited)  */
extern int timelimit;

/* Optional function to call when fatal error encountered */
extern void (*fatal_fun)();

/* Never resets */
extern size_t peak_bytes;

/* Resettable */
extern size_t last_peak_bytes;

/* Instantaneous */
extern size_t current_bytes;
```

同样修改 `harness.h` 内容
```c
/* Probability of malloc failing, expressed as percent */
extern int fail_probability;
```

# Programming Task Hints

修改和追加 `queue.h` 以及 `queue.c` 中定义的部分内容来实现需求

部分提示如下

## q_new

创建一个新的**空队列**

注意在这里需要进行队列有关全部字段的初始化，想想应该如何处理？有哪些字段需要在这里初始化？

## q_free

清除队列中**所有**所占内存

不能使用递归进行清除，因为在测试用例中会进行 1,000,000 个元素的情景，递归清除亲测会造成栈溢出XD

## q_insert_head

单链表的头插法(模拟入栈push操作)

这里两个要点：
- 正如之前所说,C中字符串需要多分配一个 Terminator \0 的长度，因此 malloc 的时候应当是 `malloc(strlen(s)+1)` 
- 字符串拷贝可以使用 `strcpy(dest,source)` 

## q_insert_tail

单链表的尾插法(模拟入队列操作)

需要注意代码实现**需要达成 O(1) 的时间复杂度**

可以追加额外字段来实现

## q_remove_head

函数接收一个字符串的指针，进行头部删除操作的时候，需要将删除节点的 value 内容拷贝一份到传入的指针 sp 所指的字符串中

函数的另外一个参数 bufsize 指定了需要拷贝的缓冲区长度，最长是 bufsize-1 个字符长度

可以使用 `strncpy(dest,source,len)` 这个函数

注意拷贝完成后的字符串在末尾仍需要包含\0终止符,应该如何实现这个需求?

## q_size

返回链表长度

需要注意代码实现**需要达成 O(1) 的时间复杂度**

可以追加额外字段来实现

## q_reverse

实现链表翻转

需要注意代码中不能进行任何直接/间接的 malloc/free 等对内存操作的函数调用

间接是指像是调用上面的 `q_insert_tail`,`q_remove_head` 这种，都是不被允许的

亲测如果直接/间接调用会被测试案例检测出来然后终止测试🤣