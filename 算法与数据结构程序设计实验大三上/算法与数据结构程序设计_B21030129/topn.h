#pragma warning(disable:4996) //�������ֵ���������� scanf
#include <iostream> //���� # Ԥ����ָ�� include �ļ��� iostream ������ <>
//#include <algorithm> //�㷨
#include <random>
#include <chrono>
using namespace std;
//��ͷ using namespace std����ʹ��һ������Ϊstd��namespace�� 
//���������ռ� std �ڶ�������б�ʶ������Ч���ع⣩
#pragma once

int Gaussian_noise(double mean, double stddev);//����������̬�ֲ������
void swap(int nums[], int i, int j); //���ڽ���num������i���j���ֵ
void heapify(int nums[], int i, int len);//������
void buildMaxHeap(int nums[], int len);//�γ�����
void sort(int nums[], int len);//����