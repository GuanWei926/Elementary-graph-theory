#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <climits>
using namespace std;
#define INF 1e+15

int main()
{
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int T, sub;
    cin >> T >> sub;
    for (int w = 0; w < T; w++)
    {
        int num_vertex, num_edge, k;
        cin >> num_vertex >> num_edge >> k;
        vector<vector<pair<int, long long>>> edge_cost_reverse(num_vertex+1); // add final vertex
        for (int i = 0; i < num_edge; i++)
        {
            int x, y, weight;
            cin >> x >> y >> weight;
            edge_cost_reverse[y - 1].push_back({x - 1, weight});
        }
        if (k == 1)
        {
            vector<long long> dist(num_vertex, INF);
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
            dist[0] = 0;
            pq.push({0, 0}); // weight, vertex
            while (!pq.empty())
            {
                int curr = pq.top().second;
                pq.pop();
                for (int i = 0; i < edge_cost_reverse[curr].size(); i++)
                {
                    int next = edge_cost_reverse[curr][i].first;
                    long long weight = edge_cost_reverse[curr][i].second;
                    if (dist[curr] + weight < dist[next])
                    {
                        dist[next] = dist[curr] + weight;
                        pq.push({dist[next], next});
                    }
                }
            }

            for (int i = 0; i < num_vertex; i++)
            {
                if(dist[i] == INF)
                    cout << -1 << " ";
                else
                    cout << dist[i] << " ";
            }
            cout << "\n";
        }

        else if (k == 2)
        {
            vector<long long> dist1(num_vertex, INF);
            vector<long long> dist2(num_vertex, INF);
            vector<long long> ans(num_vertex + 1, INF);
            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq1;
            dist1[0] = 0;
            pq1.push({0, 0});
            // dijkastra for person 1's traversal
            while (!pq1.empty())
            {
                int curr = pq1.top().second;
                pq1.pop();
                for (int i = 0; i < edge_cost_reverse[curr].size(); i++)
                {
                    int next = edge_cost_reverse[curr][i].first;
                    long long weight = edge_cost_reverse[curr][i].second;
                    if (dist1[curr] + weight < dist1[next])
                    {
                        dist1[next] = dist1[curr] + weight;
                        pq1.push({dist1[next], next});
                    }
                }
            }

            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq2;
            dist2[num_vertex - 1] = 0;
            pq2.push({0, num_vertex - 1});
            // dijkastra for person 2's traversal
            while (!pq2.empty())
            {
                int curr = pq2.top().second;
                pq2.pop();
                for (int i = 0; i < edge_cost_reverse[curr].size(); i++)
                {
                    int next = edge_cost_reverse[curr][i].first;
                    long long weight = edge_cost_reverse[curr][i].second;
                    if (dist2[curr] + weight < dist2[next])
                    {
                        dist2[next] = dist2[curr] + weight;
                        pq2.push({dist2[next], next});
                    }
                }
            }

            // add the edges from final vertex
            for (int i = 0; i < num_vertex; i++)
            {
                edge_cost_reverse[num_vertex].push_back({i, dist1[i] + dist2[i]});
            }

            priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq3;
            ans[num_vertex] = 0;
            pq3.push({0, num_vertex});
            // dijkstra to find the answer
            while (!pq3.empty())
            {
                int curr = pq3.top().second;
                pq3.pop();
                for (int i = 0; i < edge_cost_reverse[curr].size(); i++)
                {
                    int next = edge_cost_reverse[curr][i].first;
                    long long weight = edge_cost_reverse[curr][i].second;
                    if (ans[curr] + weight < ans[next])
                    {
                        ans[next] = ans[curr] + weight;
                        pq3.push({ans[next], next});
                    }
                }
            }

            // print answer
            for (int i = 0; i < num_vertex; i++)
            {
                if(dist1[i]==INF || dist2[i]==INF)
                    cout << -1 << " ";
                else
                    cout << ans[i] << " ";
            }
            cout << "\n";
        }
    }
}

/*
2 2
4 5 1
2 3 1
3 1 2
3 4 3
2 4 3
2 1 4
4 5 2
2 3 1
3 1 2
3 4 3
2 4 3
2 1 4
*/

/*
2 4
4 6 1
1 2 2
2 1 2
2 3 4
3 2 4
4 2 3
2 4 3
4 6 2
1 2 2
2 1 2
2 3 4
3 2 4
4 2 3
2 4 3
*/
