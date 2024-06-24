#include<iostream>
#include<cstdlib>
#include<vector>
#include<queue>
using namespace std;

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int n, m, x, y;
    cin >> n >> m;
    vector<vector<int>>adj_list(n+1);
    vector<int>vec(n+1, 0);
    queue<int>q;
    for(int i=0 ; i<m ; i++){
        cin >> x >> y;
        adj_list[x].push_back(y);
        adj_list[y].push_back(x);
    }

    int vertex;
    vec[1] = 1;
    q.push(1);
    while(!q.empty()){
        vertex = q.front();
        q.pop();
        for(auto index : adj_list[vertex]){
            if(vec[index]==0){
                if(vec[vertex] == 1)
                    vec[index] = 2;
                else
                    vec[index] = 1;
                q.push(index);
            }
            else if(vec[vertex] == vec[index]){
                cout << "No\n";
                return 0;
            }
        }
    }
    cout << "Yes\n";
    return 0;
}
