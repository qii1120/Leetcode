#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <string.h>
#include <set>
using namespace std;
bool canPartition(vector<int>& nums) {
    int sum=0;
    for(int i=0; i<nums.size();i++) sum += nums[i];
    if(sum%2!=0) return false;
    sum/=2;
    set<int> s;
    s.insert(0);
    for(int i=0; i<nums.size();i++)
    {
        set<int> s2(s);
        for(set<int>::iterator it=s2.begin();it!=s2.end(); it++)
        {
            s.insert(nums[i]+(*it));
            if((nums[i]+(*it)==sum)) return true;
        }
    }
    return false;
}
int main()
{
    vector<int> nums;
    nums.push_back(2);
    nums.push_back(2);
    nums.push_back(3);
    nums.push_back(5);
    cout<<(canPartition(nums)?"yes":"no")<<endl;
    return 0;
}