#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

// tarjan's algorithm
void tarjan(vector<vector<int>> &adj_list, int curr, vector<int> &visited,
            vector<int> &disc, vector<int> &low, int step, int parent, vector<int> &is_cutvertex, int &total)
{
    int children = 0;
    visited[curr] = 1;
    disc[curr] = step;
    low[curr] = step;

    for (auto next : adj_list[curr])
    {
        if (!visited[next])
        {
            children++;
            tarjan(adj_list, next, visited, disc, low, step + 1, curr, is_cutvertex, total);

            low[curr] = min(low[curr], low[next]);

            // case2 : u is not the root of the DFS tree and it has a child v
            // such that no vertex in the subtree rooted with v has a back edge
            // to one of the ancestors in DFS tree of u.
            if (parent != -1 && low[next] >= disc[curr])
            {
                if(is_cutvertex[curr] != 1){
                    is_cutvertex[curr] = 1;
                    total++;
                }
            }
        }

        else if (next != parent)
            low[curr] = min(low[curr], disc[next]);
    }

    // case1 : u is the root of the DFS tree and it has at least two children.
    if (parent == -1 && children >= 2)
    {
        if(is_cutvertex[curr]!=1){
            is_cutvertex[curr] = 1;
            total++;
        }
    }
}

int main()
{
    int num_vertices, num_edges;
    cin >> num_vertices >> num_edges;
    vector<vector<int>> adj_list(num_vertices + 1);
    for (int i = 0; i < num_edges; i++)
    {
        int x, y;
        cin >> x >> y;
        adj_list[x].push_back(y);
        adj_list[y].push_back(x);
    }

    int total = 0;
    // disc[] --> Stores discovery times of visited vertices
    vector<int> disc(num_vertices + 1, 0);
    // low[] -- >> earliest visited vertex (the vertex with minimum discovery time) that can be reached from subtree rooted with current vertex
    vector<int> low(num_vertices+1);
    vector<int> visited(num_vertices + 1, 0);
    vector<int> is_cutvertex(num_vertices + 1, 0);
    int step = 1, parent = -1;
    for (int curr = 1; curr <= num_vertices; curr++)
    {
        if (!visited[curr])
            tarjan(adj_list, curr, visited, disc, low, step, parent, is_cutvertex, total);
    }

    cout << total << "\n";

    for (int curr = 1; curr <= num_vertices; curr++)
    {
        if (is_cutvertex[curr])
            cout << curr << " ";
    }
}
