#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>
#include <queue>
using namespace std;

bool bfs(vector<vector<int>> &rgraph, vector<int> &parent, int s, int t, int num_vertices)
{
    vector<int> visited(num_vertices, 0);
    visited[0] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty())
    {
        int curr = q.front();
        q.pop();
        for (int i = 0; i < rgraph[curr].size(); i++)
        {
            if (!visited[i] && rgraph[curr][i] > 0)
            {
                q.push(i);
                visited[i] = 1;
                parent[i] = curr;
                if (i == num_vertices - 1)
                    return true;
            }
        }
    }
    return false;
}

int Augmenting_Flow(vector<vector<int>> graph, int s, int t, int num_vertices)
{
    // if number in rgraph > 0, it represents the slack of that edge (the same direction as edge)
    // if number in rgraph < 0, it represents the current flow of the edge (the opposite direction to edge)
    vector<vector<int>> rgraph(num_vertices, vector<int>(num_vertices));
    vector<int> parent(num_vertices, -1);
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
        while (curr != 0)
        {
            // cout << curr << " ";
            prev = parent[curr];
            path_flow = min(path_flow, rgraph[prev][curr]);
            curr = prev;
        }
        // cout << endl;

        curr = t;
        while (curr != 0)
        {
            prev = parent[curr];
            rgraph[prev][curr] -= path_flow;
            rgraph[curr][prev] += path_flow;
            curr = prev;
        }
        maxflow += path_flow;
        // cout << "maxflow: " << maxflow << endl;
    }
    return maxflow;
}

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int hero, monster, potion;
    cin >> hero >> monster >> potion;

    // build a diagraph(network flow), vertex 0 reprensents source
    // and then following that, in order, are heroes, monsters, and potions.
    // last one is sink (t)
    int vertices = hero + monster + 3;
    vector<vector<int>> graph(vertices, vector<int>(vertices, 0));

    // source connects to heroes
    // heroes connect to monsters
    for (int i = 1; i <= hero; i++)
    {
        graph[0][i] = 1;
        int total;
        cin >> total;
        for (int j = 0; j < total; j++)
        {
            int monster_index;
            cin >> monster_index;
            graph[i][hero + monster_index + 1] = 1;
        }
    }

    // source connects to potion
    graph[0][hero + 1] = potion;

    // potion connects to heroes
    for (int i = 1; i <= hero; i++)
    {
        graph[hero + 1][i] = 1;
    }

    // monsters connect to sink
    for (int i = 1; i <= monster; i++)
    {
        graph[hero + 1 + i][hero + monster + 2] = 1;
    }
    cout << Augmenting_Flow(graph, 0, vertices - 1, vertices);
}