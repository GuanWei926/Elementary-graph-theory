#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

bool isK5(vector<vector<int>> &adj, vector<int> &idx)
{
    if (idx.size() != 5)
        return false;
    for (int i = 0; i < 5; i++)
    {
        for (int j = i + 1; j < 5; j++)
        {
            if (adj[idx[i]][idx[j]] != 1)
                return false;
        }
    }
    return true;
}

bool isK33(vector<vector<int>> &adj, vector<int> &idx)
{
    if (idx.size() != 6)
        return false;
    sort(idx.begin(), idx.end());
    do
    {
        bool check = true;
        // The first three vertices must not be connected.
        for (int i = 0; i < 3; i++)
        {
            for (int j = i + 1; j < 3; j++)
            {
                if (adj[idx[i]][idx[j]] == 1)
                {
                    check = false;
                    break;
                }
            }
            if (!check)
                break;
        }
        if (!check)
            continue;

        // the last three vertices must not be connected.
        for (int i = 3; i < 6; i++)
        {
            for (int j = i + 1; j < 6; j++)
            {
                if (adj[idx[i]][idx[j]] == 1)
                {
                    check = false;
                    break;
                }
            }
            if (!check)
                break;
        }
        if (!check)
            continue;

        // The first three vertices and the last three vertices must be connected.
        for (int i = 0; i < 3; i++)
        {
            for (int j = 3; j < 6; j++)
            {
                if (adj[idx[i]][idx[j]] == 0)
                {
                    check = false;
                    break;
                }
            }
            if (!check)
                break;
        }
        if (check)
            return true;

    } while (next_permutation(idx.begin(), idx.end()));
    return false;
}

int main()
{
    int testcase;
    cin >> testcase;
    for (int w = 0; w < testcase; w++)
    {
        bool flag = false;
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> edge(m);
        for (int i = 0; i < m; i++)
        {
            int a, b;
            cin >> a >> b;
            edge[i].first = a;
            edge[i].second = b;
        }

        int sum = (1 << m); // each bit represents an edge exists or not
        for (int ii = 0; ii < sum; ii++)
        {
            // cout << ii << endl;
            bool check;
            vector<vector<int>> adj(n + 1, vector<int>(n + 1, 0));
            vector<int> deg(n + 1, 0);
            int temp = ii;
            // determine the edge we want to choose
            for (int j = 0; j < m; j++)
            {
                if (temp & 1)
                {
                    adj[edge[j].first][edge[j].second] = 1;
                    adj[edge[j].second][edge[j].first] = 1;
                }
                else
                {
                    adj[edge[j].first][edge[j].second] = 0;
                    adj[edge[j].second][edge[j].first] = 0;
                }
                temp >>= 1;
            }

            // calculate the degree of each node
            for (int i = 1; i <= n; i++)
            {
                for (int j = 1; j <= n; j++)
                {
                    if (adj[i][j] == 1)
                    {
                        deg[i]++;
                    }
                }
            }

            // remove the node with degree 2 (since we will do the subdivision)
            while (true)
            {
                check = true;
                for (int i = 1; i <= n; i++)
                {
                    int a, b;
                    if (deg[i] == 2)
                    {
                        a = b = -1;
                        for (int j = 1; j <= n; j++)
                        {
                            if (adj[i][j] == 1)
                            {
                                if (a == -1)
                                    a = j;
                                else
                                    b = j;
                            }
                        }

                        // if a and b are adjacent to each other originally, then the degree of them will decrease 1
                        if (adj[a][b] == 1)
                        {
                            deg[a]--;
                            deg[b]--;
                        }

                        // connect a and b, and then remove i
                        adj[a][b] = adj[b][a] = 1;
                        adj[i][a] = adj[a][i] = 0;
                        adj[i][b] = adj[b][i] = 0;
                        deg[i] = 0;
                        check = false;
                        break;
                    }
                }
                if (check)
                    break;
            }

            vector<int> idx; // store the vertices which may be in K5 or K33
            // check K5
            static int count = 0;
            // cout << count++ << endl;
            idx.clear();
            for (int i = 1; i <= n; i++)
            {
                if (deg[i] == 4)
                {
                    idx.push_back(i);
                }
            }

            if (isK5(adj, idx))
            {
                cout << "NO\n";
                flag = true;
            }
            if (flag)
                break;

            // check K33
            idx.clear();
            for (int i = 1; i <= n; i++)
            {
                if (deg[i] == 3)
                    idx.push_back(i);
            }

            if (isK33(adj, idx))
            {
                cout << "NO\n";
                flag = true;
            }
            if (flag)
                break;
        }
        if (flag)
            continue;
        cout << "YES\n";
    }
}