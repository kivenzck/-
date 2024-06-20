#pragma warning(disable:4996) //解决返回值被忽略问题 scanf
#include <iostream> //符号 # 预处理指令 include 文件名 iostream 尖括号 <>
//#include <algorithm> //算法
#include <random>
#include <chrono>
using namespace std;
//开头 using namespace std就是使用一个名字为std的namespace。 
//这样命名空间 std 内定义的所有标识符都有效（曝光）
#pragma once

int Gaussian_noise(double mean, double stddev);//用于生成正态分布随机数
void swap(int nums[], int i, int j); //用于交换num数组中i项和j项的值
void heapify(int nums[], int i, int len);//堆排序
void buildMaxHeap(int nums[], int len);//形成最大堆
void sort(int nums[], int len);//排序