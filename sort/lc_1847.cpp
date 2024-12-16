/*
 * lc_1847: 最近的房间
 * 一个酒店里有 n 个房间，这些房间用二维整数数组 rooms 表示，其中 rooms[i] = [roomIdi, sizei] 表示有一个房间号为 roomIdi 的房间且它的面积为 sizei 。每一个房间号 roomIdi 保证是 独一无二 的。
 * 同时给你 k 个查询，用二维数组 queries 表示，其中 queries[j] = [preferredj, minSizej] 。第 j 个查询的答案是满足如下条件的房间 id ：
 *   房间的面积 至少 为 minSizej ，且
 *   abs(id - preferredj) 的值 最小 ，其中 abs(x) 是 x 的绝对值。
 * 如果差的绝对值有 相等 的，选择 最小 的 id 。如果 没有满足条件的房间 ，答案为 -1 。
 * 请你返回长度为 k 的数组 answer ，其中 answer[j] 为第 j 个查询的结果。
 *
 * 思路：（重点）将询问queries中的size进行排序，从大到小，并且将rooms中满足的条件的id放入一个set中，使用二分进行查询；
 *     （学习）对于set中的lower_bound函数找到大于等于当前值的指针，使用prev(point)获取当前元素的前一个指针，next获取当前元素的下一个指针。
 * */

class Solution {
public:
    vector<int> closestRoom(vector<vector<int>>& rooms, vector<vector<int>>& queries) {
        int k = queries.size();
        vector<vector<int>> k_quer(k, vector<int>(3));

        for (int i = 0; i < k; ++i) {
            k_quer[i][0] = queries[i][0];
            k_quer[i][1] = queries[i][1];
            k_quer[i][2] = i;
        }

        sort(k_quer.begin(), k_quer.end(), [&](const vector<int>& q1, const vector<int>& q2){
            return q1[1] > q2[1];
        });
        // for (auto q : k_quer) {
        //     cout << q[1] << ' ';
        // }

        sort(rooms.begin(), rooms.end(), [&](const vector<int>& room1, const vector<int>& room2){
            return room1[1] > room2[1];
        });
        // cout << endl;
        // for (auto r : rooms) {
        //     cout << r[1] << ' ';
        // }

        vector<int> ret(k, -1);
        set<int> roomId;
        int n = rooms.size();
        int left = 0;
        int inf = 0x3f3f3f3f;
        for (auto q : k_quer) {
            int id = q[0], size = q[1], idx = q[2];
            while (left < n && rooms[left][1] >= size) {
                roomId.emplace(rooms[left][0]);
                left++;
            }
            if (roomId.empty()) continue;
            auto p = roomId.lower_bound(id);
            auto pre = prev(p);
            // cout << *p << ' ' << *pre << endl;
            if (p != roomId.end() && abs(id - *p) < abs(id - *pre) || p == roomId.begin())
                ret[idx] = *p;
            else    ret[idx] = *pre;
        }

        return ret;

    }
};
