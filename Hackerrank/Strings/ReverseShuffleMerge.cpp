#include <iostream>
#include <vector>
using namespace std;
const int MAX_SIZE=10002;
char str[MAX_SIZE];
int map[26],sub_map[26];
vector<char> ret;

bool smallest_str(int len,int end)
{
    if(end<len-1)
        return false;
    if(len==0)
        return true;
    for(int i=0;i<26;i++)
    {
        if(sub_map[i]>0)
        {
            int j=end;
            while(1)
            {
				map[str[j]-'a']--;
				if(str[j]-'a'!=i&&map[str[j]-'a']<sub_map[str[j]-'a'])
					break;
                if(str[j]-'a'==i)
                {
                    sub_map[i]--;
                    ret.push_back(str[j]);
                    if(smallest_str(len-1,j-1))
                        return true;
                    ret.pop_back();
                    sub_map[i]++;
                    break;
                }
                j--;
            }
			while(j<=end)
				map[str[j++]-'a']++;
        }
    }
	return false;
}

int main()
{
    cin>>str;
    int len;
    for(len=0;str[len]!='\0';len++)
        map[str[len]-'a']++;
    for(int i=0;i<26;i++)
        sub_map[i]=map[i]/2;
    smallest_str(len/2,len-1);
    for(int i=0;i<ret.size();i++)
        cout<<ret[i];
    return 0;
}
