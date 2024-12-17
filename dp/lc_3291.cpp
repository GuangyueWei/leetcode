/*
 * lc_3291:形成目标字符串需要的最少字符串数
 *
 * 给一个字符串数组words 和一个字符串 target。
 * 如果字符串 x 是 words 中的任意字符串的前缀，则认为 x 是一个有效字符串。
 *
 * 现计划通过链接有效字符串形成 target， 请计算并返回需要链接的最少字符串的数量。如果无法通过这种方式形成 target， 则返回 -1。
 *
 * 思路：简单考虑：dp求解，状态定义：f[i] 表示前i个字符串所需要的最少操作次数；状态转移：f[i] = min(f[i], f[j] + 1), 其中 target[j...i]为一个字符串的前缀；但是该算法的复杂度为O(n^3);
 *     优化：能不能将其降到O(n^2)的复杂度呢，在求解f[i]时，直接对target[j...i]进行验证，而不需要确定j后再次进行验证？可以从后往前进行计算，f[i] 表示target[i...n]使用words数组表示所需要的
 *     最少次数；状态转移：f[i] = min(f[i], f[j] + 1), 其中target[i...j]为有效字符串前缀；且当target[i...j]不是时，直接退出当前循环，后续不再有有效字符串序列。
 *
 * */

class Tie {

public:
    vector<Tie*> children;

    Tie() {
        children.resize(26);
    }

    void add(string& s) {
        Tie* tmp = this;
        // int hop = 0;
        for (char c : s) {
            int d = c - 'a';
            if (tmp->children[d] == nullptr)  tmp->children[d] = new Tie();
            tmp = tmp->children[d];

        }

    }

    bool find(string& s, int start, int end) {
        Tie* tmp = this;
        for (int i = start; i < end; ++i) {
            char c = s[i];
            int d = c - 'a';
            if (tmp->children[d] == nullptr)  return false;
            tmp = tmp->children[d];
        }

        return true;
    }
};

class Solution {
public:
    int minValidStrings(vector<string>& words, string target) {
        int n = target.size();
        int inf = 0x3f3f3f3f;
        vector<int> f(n+1, inf);

        // cout << n << endl;
        // for (string word : words) {
        //     cout << word.size() << ' ';
        // }

        // init
        f[n] = 0;
        Tie* tie = new Tie();
        for (string& word : words) {
            tie->add(word);
        }

        for (int i = n-1; i >= 0; --i) {
            Tie* cur = tie;
            int r = i;
            while (r < n) {
                int d = target[r] - 'a';
                if (cur->children[d]) {
                    cur = cur->children[d];
                    r++;
                    f[i] = min(f[i], f[r] + 1);
                } else  break;
            }
        }

        return f[0] == inf ? -1 : f[0];
    }
};
