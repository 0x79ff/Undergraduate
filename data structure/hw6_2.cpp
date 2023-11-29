/**
 * @file    template.cpp
 * @name    模板程序
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
class Solution {
public:
    bool cmp(string &a,string &b){
        //返回true说明a应该在b前面
        string s1=a+b;
        string s2=b+a;
        return s1>s2?true:false;
    }
    void bubble_sort(vector<string>&s,int len)
    {
        for(int i=1;i<len;i++){
            for(int j=0;j<len-i;j++){
                if(!cmp(s[j],s[j+1])){
                    swap(s[j],s[j+1]);
                }
            }
        }
    }
    std::string largestNumber(std::vector<int>& nums) {
        // 这里填写你的代码 
        string ans="";
        int len = nums.size();
        vector<string>s;
        for(int i=0;i<len;i++){
            if(nums[i]==0){
                s.push_back("0");
            }
            else{
                s.push_back(to_string(nums[i]));
            }
        }
        bubble_sort(s,len);
        for(int i=0;i<len;i++){
            ans+=s[i];
        }
        return ans;
    } 
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main() {
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i ++ ) {
        std::cin >> nums[i];
    }
    Solution s;
    std::cout << s.largestNumber(nums) << std::endl;
    return 0;
}
