/**
 * @file    template.cpp
 * @name    p138妯℃澘绋嬪簭
 * @date    2022-11-20
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
/*     浠ヤ笅鏄?綘闇�瑕佹彁浜ょ殑浠ｇ爜     */
/********************************/
class Solution {
public: 
    int solve(std::vector<vector<std::string>> &old_chart, std::vector<std::vector<std::string>> &new_chart) {
        int count = 0;
        //需要建立名字到坐标的映射 使用map
        map<string,int> m;
        for( int i = 0; i < new_chart.size(); i ++ ) {
            for( int j = 0; j < new_chart[i].size(); j ++ ) {
              m[new_chart[i][j]] = i*new_chart[i].size()+j;
            }
        }
        //进行换位操作
        for( int i = 0; i < new_chart.size(); i ++ ) {
            for( int j = 0; j < new_chart[i].size(); j ++ ) {
              if(new_chart[i][j] != old_chart[i][j]){
                  string t = new_chart[i][j];
                  new_chart[i][j] = old_chart[i][j];
                  m[t] = m[old_chart[i][j]];
                  new_chart[m[t]/new_chart[i].size()][m[t]%new_chart[i].size()] = t;
                  count++;
              }
            }
        }
        return count;
    }
};
/********************************/
/*     浠ヤ笂鏄?綘闇�瑕佹彁浜ょ殑浠ｇ爜     */
/********************************/

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<std::string>> old_chart(n, std::vector<std::string>(m));
    std::vector<std::vector<std::string>> new_chart(n, std::vector<std::string>(m));

    for( int i = 0; i < n; i ++ ) {
        for( int j = 0; j < m; j ++ ) {
            std::cin >> old_chart[i][j];
        }
    }
    for( int i = 0; i < n; i ++ ) {
        for( int j = 0; j < m; j ++ ) {
            std::cin >> new_chart[i][j];
        }
    }

    Solution s;
    std::cout << s.solve(old_chart, new_chart) << std::endl;
    return true;
}