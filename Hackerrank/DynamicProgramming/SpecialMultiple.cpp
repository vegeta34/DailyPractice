#include <iostream>
#include <vector>
using namespace std;

const int MAX_N=500;
vector<int> prime;
void init_prime(int upper)
{
    vector<bool> arr(upper+1);
    for(int i=0;i<=upper;i++)
        arr[i]=true;
    for(int i=2;i*i<=upper;i++)
    {
        if(arr[i])
        {
            for(int j=i*i;j<=upper;j+=i)
                arr[j]=false;
        }
    }
    for(int i=2;i<=upper;i++)
    {
        if(arr[i])
            prime.push_back(i);
    }
}
long long get_multiple(int n)
{
	long long ret=9;
	vector<char> bits;
	bits.push_back('9');
	while(1)
	{
		if(ret%n==0)
			return ret;
		long long ad=8;
		int i=bits.size()-1;
		for(;i>=0;i--)
		{
			if(bits[i]=='9')
			{
				bits[i]='0';
				ad*=10;
			}
			else{
				bits[i]='9';
				ret+=ad+1;
				break;
			}
		}
		if(i==-1)
		{
			bits.push_back('0');
			bits[0]='9';
			ret+=ad+1;
		}
		if(ret%n==0)
			return ret;
	}
}

int main()
{
	int t,n;
	cin>>t;
	while(t--)
	{
		cin>>n;
		cout<<get_multiple(n)<<endl;
	}
	return 0;
}