/*
 * lc_3266 k次乘运算后的最终数组
 * 给一个整数数组nums，一个整数k和一个整数multiplier。
 * 需要执行k次从操作，每次操作中：
 *     找到nums中的最小值x，如果存在多个最小值，选择前面的一个；
 *     将x替换成 x*multipiler
 * k次操作后，需要将nums中的每一个数值对 10e9 + 7 取模。
 * 返回执行完k次乘运算以及取余运算之后的最终数组。
 *
 * 思路：首先明确：对于一组有序数据(x1, x2, .... , xn)，乘上任意一个不为 1 的数 num，会存在一个有序序列 (y1, y2, ..., yn)使得 yn < y1 * num <= yn * num；
 * 	因此，首先可以先将X序列转变为Y序列，使用优先队列即可；后续k次操作，就可以对nums数组的长度求次数cnt与模mod，然后Y序列中的每一个数都乘上multipler的cnt次幂，然后选择前mod个数
 * 	乘上multipler；最后返回结果数组；
 * 	（其中涉及到对num的cnt次幂的计算，见下面代码）
 * */

class Solution {
    const int MOD = 1e9 + 7;
    int mypow(int n, long long num) {
        long long ret = 1;
        while (n) {
            if (n & 1) {
                ret = (ret * num) % MOD;
            }
            num = (num * num) % MOD;
            n >>= 1;
        }

        return ret;
    }

public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        if (multiplier == 1) return nums;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> Q;
        int n = nums.size();

        int max_val = -1;
        for (int i = 0; i < n; ++i) {
            Q.push({nums[i], i});
            max_val = max( max_val, nums[i]);
        }

        while (k && Q.top().first * multiplier <= max_val) {
            k--;
            auto [val, i] = Q.top();
            Q.pop();
            Q.push({val*multiplier, i});
        }

        int cnt = k / n, sur_cnt = k % n;
        int cnt_mulit = mypow(cnt, multiplier);
        for (int i = 0; i < n; ++i) {
            auto [val, loc] = Q.top();
            Q.pop();
            val = (val * cnt_mulit) % MOD;
            if (i < sur_cnt) {
                val = val * multiplier % MOD;
            }
            nums[loc] = val;
        }

        return nums;
    }
};

