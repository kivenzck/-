//题目A1：Top - N问题
//假设全国有10000人参加物理竞赛，只录取成绩优异的前10名，并将他们从高分到低分输出。(满分100分) 人和分数应该对应，就是说找出前10还包括人名，但是找出前十的分数也可以对应到人名，但是随机数的结果不符合物理竞赛的实际结果，需要改进算法
//而对落选的其他考生，无需排出名次，问此种情况下，试编写尽可能快的算法解决Top - 10问题？
//扩展：如何在10亿数中找出前1000大的数？

#pragma warning(disable:4996) //解决返回值被忽略问题 scanf
#include <iostream> //符号 # 预处理指令 include 文件名 iostream 尖括号 <>
//#include <algorithm> //算法
#include <random>
#include <chrono>
#include"topn.h"
using namespace std;
//开头 using namespace std就是使用一个名字为std的namespace。 
//这样命名空间 std 内定义的所有标识符都有效（曝光）


int nums[10];

int main()
{
    srand(time(0)); //time(0)是得到当前时间值
    int len = sizeof(nums) / sizeof(int);//sizeof(a)/sizeof(int)含义
    //sizeof是求字节数的函数，计算小括号里的变量占内存多少单元，计算单位是字节数。
    //a如果是int，float，long就是4个字节，short就是2个字节，char就是1个字节，double就是8个字节。
    //sizeof（int）就是求int型变量的字节数，也就是等于4。sizeof的优先级比除号 / 的高。
    //本段代码的功能是获取数组元素的个数
    //printf("%d ", len); //测试代码
    for (int i = 0; i < len; ++i)
    {
        nums[i] = Gaussian_noise(50, 10) % 100;//防止出现100+的数，但是负数存在出现可能，需要限制11.7 14：21
        //nums[i] = rand() % 100;  //编程语言中rand()表示产生一个随机整数，%100将随机数限制在[0,100)，应该改进为建立一个gaussrand( )函数，生成正态分布的数据
    }
    //获取随机数(0，100]，len的长度
    for (int i = 0; i < len; ++i)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");
    int k = 0;
    printf("\n请输入需要获取成绩的前n名的个数："); //需要将随机数改为正态分布
    scanf("%d", &k);
    sort(nums, len);//排序，从小到大
    for (int i = len - 1; i > len - 1 - k; --i)
    {
        printf("%d ", nums[i]);//输出最后的k个数
    }
    return 0;
}