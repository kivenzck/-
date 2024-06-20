#include"topn.h"
using namespace std;
//��ͷ using namespace std����ʹ��һ������Ϊstd��namespace�� 
//���������ռ� std �ڶ�������б�ʶ������Ч���ع⣩


int Gaussian_noise(double mean, double stddev)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::normal_distribution<double> dist(mean, stddev);
    return dist(generator);
}

void swap(int nums[], int i, int j) //���ڽ���num������i���j���ֵ
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
        newIndex = left;//���ӽڵ�󣬸��ڵ��±�������ӽڵ�
    }
    if (right<len && nums[right]>nums[newIndex])
    {
        newIndex = right;
    }
    if (newIndex != i) //�±귢���任������num������i���newIndex���ֵ
    {
        swap(nums, i, newIndex);
        heapify(nums, newIndex, len);//�����ж����ӽڵ�����ӽڵ�֮��Ĵ�С��ϵ��ֱ������i�ڵ������
    }
}

void buildMaxHeap(int nums[], int len)
{
    for (int i = len / 2 - 1; i >= 0; --i) //�Ե�һ����Ҷ�ӽڵ㼰֮ǰ�Ľ��жѻ�
    {
        heapify(nums, i, len);
    }
}

void sort(int nums[], int len)
{
    buildMaxHeap(nums, len);//��������
    for (int i = len - 1; i > 0; --i)
    {
        //swap(nums, 0, len); //�о���len-1�����ǲ����
        swap(nums, 0, len - 1);//��Ȼ��len-1
        heapify(nums, 0, --len);//������ 
        //���ѣ��Զ����������������㣺���ڵ���ڵ�����һ�ӽڵ㣻�Ѷ�Ԫ���Ƕ������Ԫ�أ� ��С�ѣ��Զ����������������㣺���ڵ�С�ڵ�����һ�ӽڵ㣻�Ѷ�Ԫ���Ƕ�����СԪ�ء�
    }//���Ѷ���ĩβ��������n-1�������ѣ��ٽ�����ֱ��������С��������
}