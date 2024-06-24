#include<iostream>
#include<cstdlib>
#include<vector>
#include<queue>
#include<algorithm>
#include<climits>
using namespace std;

int bfs(int start, vector<vector<int>>adj_list){
    // first step. find the farthest vertex
    queue<pair<int,int>>q1; // now, previous
    int farthest=start;
    q1.push({start, 1});
    while(!q1.empty()){
        int num = q1.front().first, prev=q1.front().second;
        q1.pop();
        for(auto next : adj_list[num]){
            if(next!=prev){
                q1.push({next,num});
                farthest = next;
            }
        }
    }

    // second step. find the diameter
    queue<pair<int,int>>q2;
    q2.push({farthest, farthest});
    int step = -1;
    while(!q2.empty()){
        int length = q2.size();
        step++;
        for(int i=0 ; i<length ; i++){
            int num = q2.front().first, prev=q2.front().second;
            q2.pop();
            for(auto next : adj_list[num]){
                if(next!=prev){
                    q2.push({next,num});
                }
            }
        }
    }
    return step;
}

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int n, a, b;
    cin >> n;
    vector<vector<int>>adj_list(n+1);
    for(int i=0 ; i<n-1 ; i++){
        cin >> a >>b;
        adj_list[a].push_back(b);
        adj_list[b].push_back(a);
    }

    cout << bfs(1, adj_list);
}
