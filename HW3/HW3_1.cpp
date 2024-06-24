#include <iostream>
#include <cstdlib>
#include <vector>
#include <climits>
using namespace std;

void heapify(vector<pair<int, int>> &min_heap, vector<int> &city_position, int position)
{
    while (true)
    {
        if (2 * position + 1 >= min_heap.size())
            break;
        int curr_val = min_heap[position].second;
        int left_val = min_heap[2 * position + 1].second;
        int right_val;
        if (2 * position + 2 >= min_heap.size())
            right_val = INT_MAX;
        else
            right_val = min_heap[2 * position + 2].second;

        if (curr_val > left_val && curr_val > right_val)
        {
            if (left_val <= right_val)
            {
                city_position[min_heap[position].first] = 2 * position + 1;
                city_position[min_heap[2 * position + 1].first] = position;
                swap(min_heap[position], min_heap[2 * position + 1]);
                position = 2 * position + 1;
            }
            else
            {
                city_position[min_heap[position].first] = 2 * position + 2;
                city_position[min_heap[2 * position + 2].first] = position;
                swap(min_heap[position], min_heap[2 * position + 2]);
                position = 2 * position + 2;
            }
        }
        else if (curr_val > left_val)
        {
            city_position[min_heap[position].first] = 2 * position + 1;
            city_position[min_heap[2 * position + 1].first] = position;
            swap(min_heap[position], min_heap[2 * position + 1]);
            position = 2 * position + 1;
        }
        else if (curr_val > right_val)
        {
            city_position[min_heap[position].first] = 2 * position + 2;
            city_position[min_heap[2 * position + 2].first] = position;
            swap(min_heap[position], min_heap[2 * position + 2]);
            position = 2 * position + 2;
        }
        else
            break;
    }
    return;
}

void extract_min(vector<pair<int, int>> &min_heap, vector<int> &city_position)
{
    city_position[min_heap[min_heap.size() - 1].first] = 0;
    swap(min_heap[0], min_heap[min_heap.size() - 1]);
    min_heap.pop_back();
    heapify(min_heap, city_position, 0);
    return;
}

void decrease_key(vector<pair<int, int>> &min_heap, vector<int> &city_position, int city, int position, int num)
{
    min_heap[position].second = num;
    while (true)
    {
        if (position == 0)
            break;
        int parent_idx = (position - 1) / 2;
        if (min_heap[parent_idx].second > min_heap[position].second)
        {
            city_position[city] = parent_idx;
            city_position[min_heap[parent_idx].first] = position;
            swap(min_heap[parent_idx], min_heap[position]);
            position = parent_idx;
        }
        else
            break;
    }
    return;
}

int main()
{
    int testcase;
    cin >> testcase;
    for (int w = 0; w < testcase; w++)
    {
        int num_city, num_special;
        int min_city, min_city_cost = INT_MAX;
        cin >> num_city >> num_special;
        vector<int> visited(num_city + 1, 0);
        vector<int> city_cost(num_city + 1);
        vector<vector<pair<int, int>>> cost(num_city + 1);

        // record cost of each city
        for (int i = 1; i < num_city + 1; i++)
        {
            cin >> city_cost[i];
            if (city_cost[i] < min_city_cost)
            {
                min_city_cost = city_cost[i];
                min_city = i;
            }
        }

        // record cost of each special offers
        for (int i = 0; i < num_special; i++)
        {
            int x, y, weight;
            cin >> x >> y >> weight;
            cost[x].push_back({y, weight});
            cost[y].push_back({x, weight});
        }

        // record cost of the bridge connecting to the minimal vertex
        for (int i = 1; i < num_city + 1; i++)
        {
            if (i == min_city)
                continue;
            int weight = min_city_cost + city_cost[i];
            cost[i].push_back({min_city, weight});
            cost[min_city].push_back({i, weight});
        }

        // Prim algorithm
        int city = 1;
        long long ans = 0;
        int curr = 1;
        visited[1] = 1;
        // build min-heap
        vector<pair<int, int>> min_heap(num_city - 1); // city, key
        vector<int> city_position(num_city + 1, 0);
        for (int i = 0; i < num_city - 1; i++)
        {
            min_heap[i] = {i + 2, INT_MAX};
            city_position[i + 2] = i;
        }

        while (city < num_city)
        {
            for (auto x : cost[curr])
            {
                if (visited[x.first])
                    continue;
                if (x.second < min_heap[city_position[x.first]].second)
                {
                    decrease_key(min_heap, city_position, x.first, city_position[x.first], x.second);
                }
                // cout << "tst: " << curr << " " << x.first << " " << min_heap[city_position[x.first]].second << endl;
            }

            int next = min_heap[0].first;
            int min_cost = min_heap[0].second;
            extract_min(min_heap, city_position);
            city++;
            ans += min_cost;
            visited[next] = 1;
            curr = next;
        }
        cout << ans << endl;
    }
}
