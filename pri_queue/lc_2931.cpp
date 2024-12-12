/*
 *  购买物品的最大开销
 *
 *  思路：优先队列，小的value优先购买；
 * */
class Solution {
public:
    long long maxSpending(vector<vector<int>>& values) {
        long long ret = 0;
        int m = values.size(), n = values[0].size();
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> Q;

        for (int i = 0; i < m; ++i) {
            Q.push({values[i][n-1], i, n-1});
        }

        long long day = 1;
        while (!Q.empty()) {
            auto [value, i, j] = Q.top();
            Q.pop();
            ret += value * day;
            day++;
            if (j > 0) Q.push({values[i][j-1], i, j-1});
        }

        return ret;
    }
};
