#include<iostream>
#include<cstdlib>
#include<vector>
using namespace std;

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    int n, m, x, y, weight;
    cin >> n >> m;
    vector<vector<int>>Matrix(n+1, vector<int>(n+1, 0));
    vector<int>in(n+1, 0);
    vector<int>out(n+1, 0);
    for(int i=0 ; i<m ; i++){
        cin >> x >> y >> weight;
        Matrix[x][y] = weight;
        out[x]++;
        in[y]++;
    }

    for(int i=1 ; i<=n ; i++){
        for(int j=1 ; j<=n ; j++){
            cout << Matrix[i][j] << " ";
        }
        cout << "\n";
    }
    for(int i=1 ; i<=n ; i++){
        cout << in[i] << " " << out[i] << "\n";
    }
    return 0;
}
