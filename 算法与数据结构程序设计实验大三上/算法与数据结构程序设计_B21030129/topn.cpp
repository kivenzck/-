#include"topn.h"
using namespace std;
//开头 using namespace std就是使用一个名字为std的namespace。 
//这样命名空间 std 内定义的所有标识符都有效（曝光）


int Gaussian_noise(double mean, double stddev)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> dist(mean, stddev);
    return dist(generator);
}

void swap(int nums[], int i, int j) //用于交换num数组中i项和j项的值
{
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

void heapify(int nums[], int i, int len)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int newIndex = i;//i = len / 2 - 1
    if (left<len && nums[left]>nums[newIndex])
    {
        newIndex = left;//左子节点大，父节点下标等于左子节点
    }
    if (right<len && nums[right]>nums[newIndex])
    {
        newIndex = right;
    }
    if (newIndex != i) //下标发生变换，交换num数组中i项和newIndex项的值
    {
        swap(nums, i, newIndex);
        heapify(nums, newIndex, len);//继续判断新子节点和其子节点之间的大小关系，直到建立i节点的最大堆
    }
}

void buildMaxHeap(int nums[], int len)
{
    for (int i = len / 2 - 1; i >= 0; --i) //对第一个非叶子节点及之前的进行堆化
    {
        heapify(nums, i, len);
    }
}

void sort(int nums[], int len)
{
    buildMaxHeap(nums, len);//建立最大堆
    for (int i = len - 1; i > 0; --i)
    {
        //swap(nums, 0, len); //感觉是len-1，但是不想改
        swap(nums, 0, len - 1);//果然是len-1
        heapify(nums, 0, --len);//堆排序 
        //最大堆：对堆树中任意子树满足：父节点大于等于任一子节点；堆顶元素是堆中最大元素； 最小堆：对堆树中任意子树满足：父节点小于等于任一子节点；堆顶元素是堆中最小元素。
    }//将堆顶和末尾交换，对n-1再求最大堆，再交换，直到数组由小到大排列
}