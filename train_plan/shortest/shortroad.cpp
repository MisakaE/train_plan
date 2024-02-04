#include <bits/stdc++.h>
using namespace std;
int num_bit(int num)
{
    int cnt = 0;
    for (; num; num >>= 1)
    {
        if (num | 1)
            ++cnt;
    }
    return cnt;
}

const int N = 22;
const int INF = 0x3f3f3f3f;
int dp[4194334][23];
vector<vector<vector<int>>> dpsta;
string station_list[N + 2], none_str;
void shortestPathLength(vector<vector<int>> &graph)
{
    int n = graph.size();
    vector<vector<int>> dis = graph;
    memset(dp, 0x3f, sizeof(dp));
    for (int i = 0; i < n; ++i)
    {
        dp[1 << i][i] = 0;
    }
    int mx = 1 << n;
    for(int i = 0;i<mx;++i){
        vector<vector<int>> copys;
        for(int j=0;j<n;++j){
            vector<int> copps;
            copps.push_back(j);
            copys.push_back(copps);
        }
        dpsta.push_back(copys);
    }
    for (int i = 2; i <= n; ++i)
    {
        for (int k = 0; k < mx; ++k)
        {
            if (num_bit(k) == i)
            {
                int t = k;
                for (int j = 0; t; t >>= 1, ++j)
                {
                    if (t | 1)
                    {
                        int f = k ^ (1 << j);
                        for (int l = 0; f; f >>= 1, ++l){
                            if(dp[k ^ (1 << j)][l] + dis[j][l]<dp[k][j]){
                                dp[k][j] = dp[k ^ (1 << j)][l] + dis[j][l];
                                vector<int> copys = dpsta[k ^ (1 << j)][l];
                                copys.push_back(j);
                                dpsta[k][j] = copys;
                            }
                        }
                    }
                }
            }
        }
    }
    

    for(int j = 0;j<n;++j){
        for(int i:dpsta[(1<<n)-1][j]){
           cout<<station_list[i]<<"->";
        }
        cout<<endl<<dp[(1<<n)-1][j]<<endl<<endl;
    }
}


vector<vector<int>> read_in()
{
    vector<vector<int>> edges;
    for (int i = 0; i < N; ++i)
    {
        cin >> station_list[i];
    }
    for (int i = 0; i < N; ++i)
    {
        cin >> none_str;
        vector<int> nw;
        int nw_dis;
        for (int j = 0; j < N; ++j)
        {
            cin >> nw_dis;
            if (nw_dis <= 0)
                nw_dis = INF;
            nw.push_back(nw_dis);
        }
        edges.push_back(nw);
    }
    return edges;
}
int main()
{
    freopen("fullmap.data", "r", stdin);
    freopen("road.data","w",stdout);
    vector<vector<int>> edges = read_in();
    shortestPathLength(edges);
}