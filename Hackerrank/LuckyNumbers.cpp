#include <cstdio>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <string.h>
using namespace std;
/* Head ends here */
int squares[10]={0,1,4,9,16,25,36,49,64,81};
vector<int> prime;
long long max_num=0;
vector<long long> input_first, input_second, result_begin, result_end;

bool IS_PRIME(int a)
{
    int begin=0,end=prime.size()-1;
    while(begin<=end)
    {
        int mid=(begin+end)/2;
        if(a==prime[mid])
            return true;
        else if(a>prime[mid])
            begin=mid+1;
        else end=mid-1;
    }
    return false;
}

void Init_Prime()
{
    prime.push_back(2);
    prime.push_back(3);
    for(int i=5;i<81*18;i+=2)
    {
        int flag=0;
        for(int j=1;j<prime.size();j++)
        {
            if(i%prime[j]==0)
            {
                flag=1;
                break;
            }
        }
        if(!flag)
            prime.push_back(i);
    }
}
void add_one(vector<int> &bits, int &sum, int &square_sum)
{
    for(int i=0;i<bits.size();i++)
    {
        if(bits[i]!=9)
        {
            bits[i]++;
            sum++;
            square_sum+=2*bits[i]-1;
            break;
        }
        else{
            if(bits.size()==i+1)
                bits.push_back(0);
            bits[i]=0;
            sum-=9;
            square_sum-=81;
        }
    }
}
void Deal_MAX(long long max)
{
    vector<int> all_bits;
    all_bits.push_back(0);
    int sum=0,square_sum=0, first_index=0, second_index=0;
    long long ret=0;
    for(long long i=1;i<=max;i++)
    {
        for(;first_index<input_first.size()&&input_first[first_index]==i;first_index++)
            result_begin.push_back(ret);
        add_one(all_bits,sum,square_sum);
        if(IS_PRIME(sum)&&IS_PRIME(square_sum))
            ret++;
        for(;second_index<input_second.size()&&input_second[second_index]==i;second_index++)
            result_end.push_back(ret);
    }
}
int partition(vector<long long> &arr, vector<int> &old_index, int begin, int end)
{
    int r=arr[end];
    int j=begin;
    for(int i=begin;i<end;i++)
    {
        if(arr[i]<r)
        {
            long long tmp=arr[i];
            arr[i]=arr[j];
            arr[j]=tmp;
            tmp=old_index[i];
            old_index[i]=old_index[j];
            old_index[j++]=tmp;
        }
    }
    arr[end]=arr[j];
    arr[j]=r;
    int tmp=old_index[end];
    old_index[end]=old_index[j];
    old_index[j]=tmp;
    return j;
}
void my_sort(vector<long long> &arr, vector<int> &old_index, int begin, int end)
{
    if(begin<end)
    {
        int q=partition(arr,old_index,begin,end);
        my_sort(arr,old_index,begin,q-1);
        my_sort(arr,old_index,q+1,end);
    }
}
/* Tail starts here */
int main() {
    Init_Prime();
    int _cases,_a_i;
    long long _a,_b;
    scanf("%d", &_cases);
    vector<int> first_new_index(_cases), second_new_index(_cases), first_old_index, second_old_index;
    for(_a_i = 0; _a_i < _cases; _a_i++) { 
        first_old_index.push_back(_a_i);
        second_old_index.push_back(_a_i);
        scanf("%lld %lld", &_a,&_b);
        if(_b>max_num)
            max_num=_b;
        input_first.push_back(_a);
        input_second.push_back(_b);
    }
    my_sort(input_first,first_old_index,0,_cases-1);
    my_sort(input_second,second_old_index,0,_cases-1);
    for(int i=0;i<_cases;i++)
    {
        first_new_index[first_old_index[i]]=i;
        second_new_index[second_old_index[i]]=i;
    }
    Deal_MAX(max_num);
    for(int i=0;i<_cases;i++)
        printf("%lld\n",result_end[second_new_index[i]]-result_begin[first_new_index[i]]);
    return 0;
}
