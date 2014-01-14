/*https://www.hackerrank.com/challenges/find-median*/

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int partition(vector<int> &a, int head, int tail)
{
    int j=head;
    for(int i=head;i<tail;i++){
        if(a[i]<a[tail]){
            int tmp=a[i];
            a[i]=a[j];
            a[j]=tmp;
            j++;
        }
    }
    int tmp=a[j];
    a[j]=a[tail];
    a[tail]=tmp;
    return j;
}
int get_median(vector<int> &a, int n)
{
    int ret=0;
    int head=0,tail=n-1;
    while(1){
        ret=partition(a,head,tail);
        if(ret==n/2)
            return a[ret];
        else if(ret>n/2)
            tail=ret-1;
        else head=ret+1;
    }
}
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */  
    int n;
    cin>>n;
    vector<int> a(n);
    for(int i=0;i<n;i++)
        cin>>a[i];
    cout<<get_median(a,n);
    return 0;
}

