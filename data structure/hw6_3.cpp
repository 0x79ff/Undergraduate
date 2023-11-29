/**
 * @file    template.cpp
 * @name    p57模板程序
 * @date    2022-11-22
 */

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
using namespace std;

/********************************/
/*     以下是你需要提交的代码     */
/********************************/
class Solution
{
public:
    void merge(vector<int> &a, int first, int mid, int last)
    {
        int *tmpa = new int[last - first + 2];
        int i = first, j = mid + 1, pos = 1;
        while (i <= mid && j <= last)
        {
            if (a[i] <= a[j])
            {
                tmpa[pos++] = a[i++];
            }
            else
            {
                tmpa[pos++] = a[j++];
            }
        }
        while (i <= mid)
        {
            tmpa[pos++] = a[i++];
        }
        while (j <= last)
        {
            tmpa[pos++] = a[j++];
        }
        for (int i = first; i <= last; i++)
        {
            a[i] = tmpa[i - first + 1];
        }
        delete[] tmpa;
        tmpa = NULL;
    }

    void merge_sort(vector<int> &a, int first, int last)
    {
        if (first == last)
            return;
        int mid = (first + last) / 2;
        merge_sort(a, first, mid);
        merge_sort(a, mid + 1, last);
        merge(a, first, mid, last);
    }
    std::vector<int> mySort(std::vector<int> &nums)
    {
        // 这里填写你的代码
        merge_sort(nums,0,nums.size()-1);
        return nums;
    }
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> nums[i];
    }
    Solution s;
    std::vector<int> after_sort(s.mySort(nums));
    std::cout << after_sort[0];
    for (int i = 1; i < n; i++)
    {
        std::cout << ' ' << after_sort[i];
    }
    std::cout << std::endl;
    return 0;
}
