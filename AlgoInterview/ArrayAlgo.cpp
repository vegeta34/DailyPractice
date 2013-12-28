/*����10����ʱ�䣬�������Ÿ���ʮ�������������������Ӧ��ʮ���� 
Ҫ������ÿ����������ǰ������ʮ���������ų��ֵĴ����� 
���ŵ�ʮ�������£� 
��0��1��2��3��4��5��6��7��8��9��
��һ�����ӣ� 
��ֵ: 0,1,2,3,4,5,6,7,8,9 
����: 6,2,1,0,0,0,1,0,0,0 
0�����ų�����6�Σ�1�����ų�����2�Σ� 
2�����ų�����1�Σ�3�����ų�����0��.... 
�Դ�����..*/

#include <iostream>
#include <vector>
using namespace std;

void GenerateArray2(vector<int> a1, vector<int> &a2)
{
	for(int i=0;i<a2.size();i++)
		a2[i]=0;
	bool success=false;
	while(!success)
	{
		success=true;
		for(int i=0;i<a1.size();i++)
		{
			int freq=0;
			for(int j=0;j<a2.size();j++)
			{
				if(a2[j]==a1[i])
					freq++;
			}
			if(freq!=a2[i])
			{
				a2[i]=freq;
				success=false;
			}
		}
	}
}

int main()
{
	int n;
	cin>>n;
	vector<int> arr1(n), arr2(n);
	for(int i=0;i<n;i++)
		arr1[i]=i;
	GenerateArray2(arr1,arr2);
	for(int i=0;i<n;i++)
		cout<<arr2[i]<<' ';
	return 0;
}