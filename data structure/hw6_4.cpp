/**
 * @name    template.cpp
 * @brief   p142模板程序
 * @date    2022-12-02
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
class FreqStack {
private:
    map <int,int> a;//某数出现的频率
    map <int,stack<int>> b;//某频率的数
    int maxfre;
public:
    FreqStack() {
        maxfre=0;
    }
    
    void push(int val) {
        a[val]++;
        b[a[val]].push(val);
        maxfre = max(maxfre,a[val]);
    }
    
    int pop() {
        int num = b[maxfre].top();
        b[maxfre].pop();
        a[num]--;
        maxfre = b[maxfre].empty()?maxfre-1:maxfre;
        return num;
    }
};
/********************************/
/*     以上是你需要提交的代码     */
/********************************/

int main() {
    int n;
    std::cin >> n;
    FreqStack fs;
    while (n --) {
        std::string order;
        std::cin >> order;
        if (order == "push") {
            int val;
            std::cin >> val;
            fs.push(val);
        }
        else if (order == "pop") {
            std::cout << fs.pop() << std::endl;
        }
    }
    return 0;
}

