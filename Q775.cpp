#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
bool isIdealPermutation(vector<int>& nums) {
    int m = 0;
    for(int i=0;i<nums.size()-2;i++)
        if((m = max(m, nums[i]))>nums[i+2]) return false;
    return true;
}
int main()
{
    vector<int> nums;
    // nums.push_back(1);
    nums.push_back(0);
    // nums.push_back(2);
    // nums.push_back(2);
    // nums.insert(nums.begin()+2, 5);
    for (size_t i = 0; i < nums.size(); i++)
    {
        cout<<nums[i]<<endl;
    }
    cout<<(isIdealPermutation(nums)?"true":"false")<<endl;
    return 0;
}