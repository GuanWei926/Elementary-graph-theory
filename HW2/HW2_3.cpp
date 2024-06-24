#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <climits>
using namespace std;

int main()
{
    int n, a, b, num_joint = 0;
    cin >> n;
    vector<vector<int>> adj_list(n);
    vector<int> is_joint(n, 0);
    for (int i = 0; i < n - 1; i++)
    {
        cin >> a >> b;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
        if (adj_list[a].size() == 3)
        {
            is_joint[a] = 1;
            num_joint++;
        }
        if (adj_list[b].size() == 3)
        {
            is_joint[b] = 1;
            num_joint++;
        }
    }

    // Cinderella's key
    int m, temp;
    cin >> m;
    if (num_joint != m)
    {
        cout << "NO";
        return 0;
    }
    string Cinderella = "";
    for (int i = 0; i < m; i++)
    {
        cin >> temp;
        Cinderella += to_string(temp);
    }

    // find the length of the vertical bar
    int start;
    vector<vector<int>> len_vertical(n);
    for (int i = 0; i < n; i++)
    {
        if (adj_list[i].size() != 1)
            continue;
        int len = -1;
        int stop;
        stack<pair<int, int>> st; // prev, curr
        st.push({-1, i});
        while (!st.empty())
        {
            len++;
            int prev = st.top().first;
            int curr = st.top().second;
            if (is_joint[curr])
            {
                stop = curr;
                break;
            }
            for (auto next : adj_list[curr])
            {
                if (next == prev)
                    continue;
                st.push({curr, next});
            }
        }
        len_vertical[stop].push_back(len);
        if (len_vertical[stop].size() == 2)
            start = stop;
    }
    /*for (int i = 0; i < n; i++){
        cout << i << ":: ";
        for (int j = 0; j < len_vertical[i].size(); j++)
            cout << len_vertical[i][j] << " ";
    }
    cout << endl;*/

    // find the joint sequence
    vector<int> joint;
    joint.push_back(start);
    for (auto x : adj_list[start])
    {
        stack<pair<int, int>> st; // prev, curr
        st.push({start, x});
        while (!st.empty())
        {
            int curr = st.top().second;
            int prev = st.top().first;
            st.pop();
            if (is_joint[curr])
            {
                joint.push_back(curr);
            }
            for (auto next : adj_list[curr])
            {
                if (next == prev)
                    continue;
                st.push({curr, next});
            }
        }
    }
    /*for (int i = 0; i < joint.size(); i++)
        cout << joint[i] << " ";
    cout << endl;*/

    // form the key
    vector<string> head;
    vector<string> tail;
    string mid = "";
    string mid_reverse = "";
    for (int i = 0; i < 2; i++)
    {
        head.push_back(to_string(len_vertical[joint[0]][i]));
    }
    for (int i = 0; i < 2; i++)
    {
        tail.push_back(to_string(len_vertical[joint[num_joint - 1]][i]));
    }
    for (int i = 1; i < joint.size() - 1; i++)
    {
        mid += to_string(len_vertical[joint[i]][0]);
    }
    for (int i = joint.size() - 2; i >= 1; i--)
    {
        mid_reverse += to_string(len_vertical[joint[i]][0]);
    }
    // cout << "mid: " << mid << endl;
    // cout << "mid_reverse: " << mid_reverse << endl;

    // combine
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            string ans = "";
            ans += head[i];
            ans += mid;
            ans += tail[j];
            // cout << ans << endl;
            if (ans == Cinderella)
            {
                cout << "YES";
                return 0;
            }

            ans = "";
            ans += tail[j];
            ans += mid_reverse;
            ans += head[i];
            // cout << ans << endl;
            if (ans == Cinderella)
            {
                cout << "YES";
                return 0;
            }
        }
    }
    cout << "NO";
    return 0;
}

/*
21
16 11
16 7
7 17
5 12
12 14
14 20
20 17
4 17
18 3
3 4
13 4
1 13
0 1
0 6
6 9
1 15
15 10
10 2
19 10
8 19
4
1 3 2 3
*/