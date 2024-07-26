#include <iostream>
#include <vector>
using namespace std;

bool doesValidArrayExist(vector<int>& derived) {
    for(int i = 1; i < derived.size(); i++) derived[0] = derived[0]^derived[i];
    return !derived[0];
}
int main()
{
    vector<int> derived;
    derived.push_back(1);
    derived.push_back(1);
    derived.push_back(0);
    cout<<(doesValidArrayExist(derived)?"true":"false")<<endl;
    return 0;
}