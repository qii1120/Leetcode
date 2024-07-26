#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <string.h>
#include <set>
using namespace std;
int find(vector<int> &n, int start, int end)
{
    if(start==(end-1)) return n[start];
    return min(find(n, start, (start+end)/2), find(n, (start+end)/2, end));
}
int findMin(vector<int>& nums) {
    return find(nums, 0, nums.size());
}
int main()
{
    vector<int> nums;
    nums.push_back(3);
    nums.push_back(4);
    nums.push_back(5);
    nums.push_back(1);
    nums.push_back(2);
    cout<<findMin(nums)<<endl;
    return 0;
}