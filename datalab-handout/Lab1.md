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