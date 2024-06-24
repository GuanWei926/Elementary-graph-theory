#include<iostream>
#include<cstdlib>
#include<climits>
#include<vector>
#include<queue>
using namespace std;

// recursive(TLE) ==> UP to DOWN
/*int sol(vector<vector<int>> adj_list, vector<int> parent, vector<int>&height, int vertex){
    if(adj_list[vertex].size()==1 && adj_list[vertex][0] == parent[vertex]){
        height[vertex] = 0;
        return 0;
    }

    int max_h = INT_MIN;
    for (int i = 0; i < adj_list[vertex].size(); i++){
        int next = adj_list[vertex][i];
        if(next == parent[vertex])
            continue;
        height[next] = sol(adj_list, parent, height, next);
        if(height[next] > max_h){
            max_h = height[next];
        }
    }
    return max_h + 1;
}*/

// iterative ==> DOWN to UP


int main(){
    int n;
    cin >> n;
    vector<vector<int>> adj_list(n+1);
    vector<int> parent(n + 1, -1);
    vector<int> height(n + 1, 0);
    queue<int> q;
    queue<int> qh;
    // create adjacency list
    for (int i = 0; i < n - 1; i++){
        int x, y;
        cin >> x >> y;
        adj_list[x].push_back(y);
        adj_list[y].push_back(x);
    }


    // find the parent of each vertices
    q.push(1);
    while(!q.empty()){
        int curr = q.front();
        q.pop();
        for(auto x : adj_list[curr]){
            if(adj_list[curr].size()==1 && x == parent[curr]){
                qh.push(curr);
                break;
            } 
            if(x == parent[curr])
                continue;
            parent[x] = curr;
            q.push(x);
        }
    }

    /* calculate the height of each vertices with recursion
    height[1] = sol(adj_list, parent, height, 1);
    */

    // calculate the height of each vertices with iteration
    while(!qh.empty()){
        int curr = qh.front();
        qh.pop();
        if(curr == 1)
            continue;
        height[parent[curr]] = max(height[parent[curr]], height[curr] + 1);
        qh.push(parent[curr]);
    }
    for (int i = 1; i < n + 1; i++){
        cout << height[i] << " " << parent[i] << "\n";
    }
}

/*
g++ HW3_3-111550061.cpp
8
1 2
2 3
3 4
1 5
5 6
5 7
1 8
*/

/*
10
1 2
2 10
1 6
3 10
2 8
6 7
8 9
4 6
5 10
*/