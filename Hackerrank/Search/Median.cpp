/*https://www.hackerrank.com/challenges/median*/

#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <cstdlib>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;
/* Head ends here */
vector<string> result;
template<class _Tx>
int find_remove_pop(vector<int> &arr, int value, _Tx func)
{
	int index=-1;
	for(int i=0;i<arr.size();i++){
		if(arr[i]==value)
		{
			index=i;
			break;
		}
	}
	if(index==-1)
		return -1;
	int tmp=arr[index];
	arr[index]=arr[arr.size()-1];
	arr[arr.size()-1]=tmp;
	arr.pop_back();
	make_heap(arr.begin(),arr.end(),func);
	return 0;
}
template<class _Tx, class _Ty>
void move_heap_data(vector<int> &h1, vector<int> &h2, _Tx func1, _Ty func2)
{
	pop_heap(h1.begin(),h1.end(),func1);
	h2.push_back(h1[h1.size()-1]);
	h1.pop_back();
	push_heap(h2.begin(),h2.end(),func2);
}
void push_median(int a, int b)
{
	string s;
	stringstream ss;
	ss<<((long long)a+(long long)b)/2;
	if((long long)a+(long long)b == -1)
		s="-0";
	else s=ss.str();
	if(((long long)a+(long long)b)%2)
		s+=".5";
	result.push_back(s);
}
void median(vector<char> s,vector<int> x) {
	int arr_size=0;
	vector<int> max_heap,min_heap;
    for(int i=0;i<s.size();i++){
		if(s[i]=='r'){
			if(arr_size>0){
				int ret;
				if(x[i]<=max_heap[0])
					ret=find_remove_pop(max_heap,x[i],less<int>());
				else
					ret=find_remove_pop(min_heap,x[i],greater<int>());
				if(ret==-1){
					result.push_back("Wrong!");
					continue;
				}
				arr_size--;
			}
		}
		else if(s[i]=='a'){
			arr_size++;
			if(max_heap.size()==0||x[i]<=max_heap[0]){
				max_heap.push_back(x[i]);
				push_heap(max_heap.begin(),max_heap.end(),less<int>());
			}
			else{
				min_heap.push_back(x[i]);
				push_heap(min_heap.begin(),min_heap.end(),greater<int>());
			}
		}
		if(arr_size==0)
			result.push_back("Wrong!");
		else{
			if(max_heap.size()<min_heap.size())
				move_heap_data(min_heap,max_heap,greater<int>(),less<int>());
			else if(max_heap.size() - min_heap.size() > 1)
				move_heap_data(max_heap,min_heap,less<int>(),greater<int>());
			if(max_heap.size()==min_heap.size())
				push_median(max_heap[0],min_heap[0]);
			else{
				string s;
				stringstream ss;
				ss<<max_heap[0];
				s=ss.str();
				result.push_back(s);
			}
		}
	}
}
int main(void){

//Helpers for input and output

   int N;
   cin >> N;
   
   vector<char> s;
   vector<int> x;
   char temp;
    int tempint;
   for(int i = 0; i < N; i++){
      cin >> temp >> tempint;
        s.push_back(temp);
        x.push_back(tempint);
   }
   median(s,x);
   for(int i=0;i<N;i++)
	   cout<<result[i]<<endl;
   return 0;
}
