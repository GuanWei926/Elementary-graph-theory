#include<iostream>
#include<cstdlib>
#include<string>
#include<cstring>
#include<vector>
#include<climits>
#include<algorithm>
using namespace std;

static bool cmp(string& a, string& b){
    return a.size() < b.size();
}

int overlapping(string a, string b){
    int len = min(a.size(), b.size());
    while(len>0){
        if(a.substr(a.size()-len) == b.substr(0, len)){
            break;
        }
        len--;
    }
    return len;
}

string min_ans = "";
void TSP(vector<vector<int>> matrix, vector<string> vertice, int m, int start, string ans, vector<int>visited, int num){
    if(num==m){
        if(min_ans == "")
            min_ans = ans;
        else if(ans.size() < min_ans.size())
            min_ans = ans;
        else if(ans.size() == min_ans.size() && ans<min_ans)
            min_ans = ans;
        //cout << "test: " << min_ans << endl;
        return;
    }
    //visited[start] = 1;
    int maxnum = INT_MIN;
    int next;
    int l_next, l_maxnum;
    string minstr, temp, l_temp;
    string l_minstr = "";
    for (int j = 0; j < m; j++){
        if(visited[j])
            continue;
        if(l_minstr == ""){
            l_minstr = vertice[j].substr(matrix[start][j]);
            l_next = j;
            l_maxnum = matrix[start][j];
        }
        else if(l_minstr > vertice[j].substr(matrix[start][j])){
            l_minstr = vertice[j].substr(matrix[start][j]);
            l_next = j;
            l_maxnum = matrix[start][j];
        }
        if (matrix[start][j] > maxnum){
            maxnum = matrix[start][j];
            minstr = vertice[j];
            next = j;
        }
        else if (matrix[start][j] == maxnum){
            if (vertice[j] < minstr){
                minstr = vertice[j];
                next = j;
            }
        }
    }
    auto found = ans.find(minstr);
    temp = ans;
    if(found==std::string::npos){
        temp += minstr.substr(maxnum);
    }
    visited[next] = 1;
    TSP(matrix, vertice, m, next, temp, visited, num + 1);

    visited[next] = 0;
    visited[l_next] = 1;
    found = ans.find(vertice[l_next]);
    l_temp = ans;
    if(found==std::string::npos){
        l_temp += l_minstr;
    }
    //cout << "test: " << l_temp << endl;
    TSP(matrix, vertice, m, l_next, l_temp, visited, num+1);
    return;
}

int main(){
    int n;
    cin >> n;
    vector<string> temp(n);
    vector<string> vertice;
    for (int i = 0; i<n ; i++){
        cin >> temp[i];
    }

    sort(temp.begin(), temp.end(), cmp);
    //cout << endl;
    for (int i = 0; i < n; i++){
        int check = 0;
        for (int j = i + 1; j < n; j++){
            auto found = temp[j].find(temp[i]);
            if(found!=std::string::npos){
                check = 1;
                break;
            }
        }
        if(!check){
            //cout << temp[i] << endl;
            vertice.push_back(temp[i]);
        }
    }
    //cout << vertice.size() << endl;
    int m = vertice.size();
    vector<vector<int>> matrix(m, vector<int>(m, 0));
    for (int i = 0; i < m; i++){
        for (int j = 0; j < m; j++){
            if(i==j)
                continue;
            int p = overlapping(vertice[i], vertice[j]);
            matrix[i][j] = p;
        }
    }

    // repetitive nearest neighbor algorithm
    //string ans = TSP(matrix, vertice, m, 0);
    //cout << ans << endl;
    for (int i = 0; i < m; i++){
        string str = vertice[i];
        vector<int> visited(m, 0);
        visited[i] = 1;
        TSP(matrix, vertice, m, i, str, visited, 1);
    }
    cout << min_ans;
}
