# Introduction

目标是修改 bits.c 的内容，以便它通过 btest 中的所有测试，并且不违反任何代码准则。

代码规范基于 `dlc` 文件 (Data Lab Compiler)

Lab材料说明如下:

| 文件名         | 说明                                             |
| -------------- | ------------------------------------------------ |
| Makefile       | 构建 btest、fshow 和 ishow                       |
| bits.c         | 本次Lab的核心实现                           |
| bits.h         | 头文件                                           |
| btest.c        | btest 主程序                                     |
| btest.h        | 用于构建 btest                                   |
| decl.c         | 用于构建 btest                                   |
| tests.c        | 用于构建 btest                                   |
| tests-header.c | 用于构建 btest                                   |
| dlc*           | 规则检查编译器的二进制文件（data lab 编译器）    |
| driver.pl*     | 使用 btest 和 dlc 来为 bits.c 自动评分的驱动程序 |
| Driverhdrs.pm  | 头文件，用于可选的“击败教授”比赛                 |
| fshow.c        | 实用代码，用于检查浮点表示                       |
| ishow.c        | 实用代码，用于检查整数表示                       |

## dlc代码规范

开始之前，请仔细阅读 `bits.c` 文件中的说明

说明中给出了代码规则，如果想获得全部分数，需要严格遵守规范

`dlc` 是一个可执行文件，我们可以通过 `./dlc` 来检查 `bits.c` 是否符合编码规范

如果没有显示就说明没有问题，否则会显示哪里出了问题

通过 `./dlc -e bits.c` 参数来打印每个函数使用的运算符数目

## btest自动化测试

```sh
make btest
```
每次更新了实现的内容都要 `make clean` & `make btest`,这一点和 Lab0 基本一致

我们可以通过 `btest -h` 查看帮助参数文档

```sh
./btest -h
./btest [-hg] [-r <n>] [-f <name> [-1|-2|-3 <val>]*] [-T <time limit>]
    -1 <val>   指定第一个函数参数
    -2 <val>   指定第二个函数参数
    -3 <val>   指定第三个函数参数
    -f <name>  只测试指定名称的函数
    -g         格式化输出评分，不包含错误信息
    -h         打印该信息
    -r <n>     给所有问题统一的权重 n
    -T <lim>   设置超时限制为 lim
```

## ishow工具类

 ishow 和 fshow 程序，分别帮助我们破译整数和浮点表示
 
 每个都以一个十进制或十六进制数作为参数

 想要使用它们需要先 `make` 一下

 使用案例:
 
 ```sh
./ishow 0x27
Hex = 0x00000027,   Signed = 39,    Unsigned = 39

./ishow 27
Hex = 0x0000001b,   Signed = 27,    Unsigned = 27

./fshow 0x15213243
Floating point value 3.255334057e-26
Bit Representation 0x15213243, sign = 0, exponent = 0x2a, fraction = 0x213243
Normalized.  +1.2593463659 X 2^(-85)

./fshow 15213243
Floating point value 2.131829405e-38
Bit Representation 0x00e822bb, sign = 0, exponent = 0x01, fraction = 0x6822bb
Normalized.  +1.8135598898 X 2^(-126)
 ```

 # 编码规范

 ## 整数编码规范

 ### 规范内容
 
  将每个函数中的 `return` "语句替换为一行或多行实现的 C 代码, 代码必须符合以下样式：
  
 ```c
  int Funct(arg1, arg2, ...) {
      /* 简要说明如何实现 */
      int var1 = Expr1；
      ...
      int varM = ExprM；

      varJ = ExprJ；
      ...
      varN = ExprN；
      返回 ExprR；
  }
```

  每个 "Expr "都是一个表达式，只使用以下内容：
  1. 整数常量 0 至 255 (0xFF) (闭区间) 不允许使用大常量，如 0xffffffffff
  2. 函数参数和局部变量（无全局变量）
  3. 一元整数运算 ！~
  4. 二元整数运算 & ^ | + << >>
    
  有些问题甚至进一步限制了允许使用的运算符集，具体请看每个题目的标题内容，**每个 "Expr "可以由多个运算符组成，并不限于每行只能使用一个运算符**

  明确禁止不能使用的:
  1. 使用任何控制结构，如 if、do、while、for、switch 等
  2. 定义或使用任何宏。
  3. 在本文件中定义任何其他的函数
  4. 调用任何函数
  5. 使用任何其他操作，如 &&、||、- 或 ?
  6. 使用任何形式的数据类型转换 Casting
  7. 使用 int 以外的任何数据类型，这意味着不能使用数组、结构体或联合体

### 规定约束

我们规定: 

机器都使用 two's complement 补码形式，int 都是 32 位 (4字节)

右移操作是算数右移

如果移位量小于 0 或大于 31，移位时会出现不可预测的行为。

### 代码案例

符合提交规范的代码如下，例如要实现计算 2^x + 1 / 2^x + 4 的运算

```c
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }
```

## 浮点数编码规范

### 规范内容

对于需要执行浮点运算的问题，编码规则不那么严格

可以使用循环和条件控制

允许使用 int 和无符号常量

可以使用任意整数和无符号常量

可以使用任何算术运算、逻辑或比较操作


明确禁止不能使用的:
  1. 定义或使用任何宏
  2. 在此文件中定义任何其他函数
  3. 调用任何函数
  4. 使用任何形式的铸造
  5. 使用除 int 或无符号之外的任何数据类型，这意味着不能使用数组、结构体或联合体
  6. 使用任何浮点数据相关的变量类型、操作或常量

## 注意事项

1. 使用 dlc（数据实验室检查器）编译器（详见讲义）检查解答是否合法
2. 每个函数有一个允许使用的最大操作数（整数、逻辑或比较）限制，用于实现该函数，dlc 会检查最大操作数，请注意，赋值操作（‘=’）不计入操作数；你可以在不受限制的情况下使用任意多的赋值操作
3. 使用 btest 测试框架检查函数的正确性
4. 使用 BDD 检查器正式验证函数
5. 每个函数的最大操作数在该函数的注释头部给出。如果最大操作数在讲义和此文件中不一致，以此文件为准
