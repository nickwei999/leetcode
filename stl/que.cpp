// 自定义比较函数： https://en.cppreference.com/w/cpp/container/priority_queue/priority_queue
// priority_queue默认使用 less<int> 即小于号 生成大顶堆；


#include <iostream>
#include <queue>
#include <utility>
#include <vector>
using namespace std;
using my_pair_t = pair<size_t, bool>;
using my_container_t = vector<my_pair_t>;

struct myCmp {
    bool operator()(const my_pair_t& e1, const my_pair_t& e2) {
        return e1.first < e2.first;
    };
};

int main() {
    auto my_comp = [](const my_pair_t& e1, const my_pair_t& e2) {
        return e1.first > e2.first;
    };
    priority_queue<my_pair_t, my_container_t, decltype(my_comp)> queue(my_comp);
    priority_queue<my_pair_t, my_container_t, myCmp> queue1;
    queue.push(make_pair(5, true));
    queue.push(make_pair(3, false));
    queue.push(make_pair(7, true));

    queue1.push(make_pair(5, true));
    queue1.push(make_pair(3, false));
    queue1.push(make_pair(7, true));

    cout << boolalpha;
    while (!queue.empty()) {
        const auto& p = queue.top();
        cout << p.first << " " << p.second << "\n";
        queue.pop();
    }

    cout << endl;
    while (!queue1.empty()) {
        const auto& p = queue1.top();
        cout << p.first << " " << p.second << "\n";
        queue1.pop();
    }

    priority_queue<int,vector<int>, greater<int>> que;
    for (int i = 0; i < 10; ++i) {
        que.push(i);
    }
    cout << endl;
    while (!que.empty()) {
        const auto& p = que.top();
        cout << p << "\n";
        que.pop();
    }
}