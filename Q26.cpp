#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;

int removeDuplicates(vector<int> &nums)
{
    set<int> s(nums.begin(), nums.end());
    nums.assign(s.begin(), s.end());
    return nums.size();
}

int main()
{
    int n;
    vector<int> nums;
    for (int i = 0; i < 5; i++)
        nums.push_back(i);
    nums.push_back(1);
    nums.push_back(4);
    cout << removeDuplicates(nums) << endl;
    return 0;
}