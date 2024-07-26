#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
using namespace std;
int findTheCity(int n, vector<vector<int>> &edges, int distanceThreshold)
{
    int arr[n][n], p[n][n];
    memset(p, 0, sizeof(p));
    memset(arr, 100000, sizeof(arr));
    for(int i=0;i<edges.size();i++)
    {
        arr[edges[i][0]][edges[i][1]] = edges[i][2];
        arr[edges[i][1]][edges[i][0]] = edges[i][2];
        p[edges[i][0]][edges[i][1]]=1;
        p[edges[i][1]][edges[i][0]]=1;
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(j==i) continue;
            else if(p[i][j]==1)
            {
                for(int k=0;k<n;k++)
                {
                    if(k==i||k==j) continue;
                    else if(p[j][k]==1)
                        arr[i][k] = min(arr[i][k], arr[i][j]+arr[j][k]);
                }
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
            cout<<arr[i][j]<<" ";
        cout<<endl;
    }
    return 0;
}
int main()
{
    int n=4;
    vector<vector<int> > nums = {{0, 1, 3}, {1, 2, 1}, {1, 3, 4}, {2, 3, 1}};
    cout << findTheCity(n, nums, 4) << endl;
    return 0;
}