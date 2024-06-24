#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

bool bfs(vector<vector<int>> &rgraph, vector<int> &parent, int s, int t, int num_vertices)
{
    vector<int> visited(num_vertices + 1, 0);
    visited[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int curr = q.front();
        // cout << curr << endl;
        q.pop();
        for (int i = 1; i <= num_vertices; i++)
        {
            if (!visited[i] && rgraph[curr][i] > 0)
            {
                q.push(i);
                visited[i] = 1;
                parent[i] = curr;
                if (i == t)
                    return true;
            }
        }
    }
    return false;
}

int Augmenting_Flow(vector<vector<int>> graph, int s, int t, int num_vertices, int &ans)
{
    // if number in rgraph > 0, it represents the slack of that edge (the same direction as edge)
    // if number in rgraph < 0, it represents the current flow of the edge (the opposite direction to edge)
    vector<vector<int>> rgraph(num_vertices + 1, vector<int>(num_vertices));
    vector<int> parent(num_vertices + 1, -1);
    int maxflow = 0;
    rgraph = graph;
    /*for (int i = 0; i < rgraph.size(); i++)
    {
        for (int j = 0; j < rgraph[0].size(); j++)
        {
            cout << rgraph[i][j] << " ";
        }
        cout << endl;
    }*/

    while (bfs(rgraph, parent, s, t, num_vertices))
    {
        int curr = t, prev;
        int path_flow = INT_MAX;
        while (curr != s)
        {
            // cout << curr << " ";
            prev = parent[curr];
            path_flow = min(path_flow, rgraph[prev][curr]);
            curr = prev;
        }
        // cout << endl;

        curr = t;
        while (curr != s)
        {
            prev = parent[curr];
            rgraph[prev][curr] -= path_flow;
            rgraph[curr][prev] += path_flow;
            curr = prev;
        }
        maxflow += path_flow;
        if (maxflow > ans)
            return -1;
        // cout << "maxflow: " << maxflow << endl;
    }
    return maxflow;
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<int> parent(n + 1);
    vector<vector<int>> graph(n + 1, vector<int>(n + 1));
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        graph[x][y] = 1;
        graph[y][x] = 1;
    }

    int ans = INT_MAX;
    for (int source = 1; source <= n; source++)
    {
        for (int sink = source + 1; sink <= n; sink++)
        {
            // cout << "test: " << source << " " << sink << endl;
            int num_path = Augmenting_Flow(graph, source, sink, n, ans);
            if (num_path != -1)
                ans = min(ans, num_path);
        }
    }
    cout << ans << "\n";
}