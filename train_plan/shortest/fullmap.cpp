#include<bits/stdc++.h>
using namespace std;
const int INF = 0x3f3f3f3f;
const int N = 22; 
string station_list[25];
string none_str;
vector<vector<int>> edges;
void read_in(){
    for(int i=0;i<N;++i){
        cin >> station_list[i];
    }
    for(int i = 0;i<N;++i){
        cin >> none_str;
        vector<int> nw;
        int nw_dis;
        for(int j=0;j<N;++j){
            cin >> nw_dis;
            if(nw_dis<=0)nw_dis=INF;
            nw.push_back(nw_dis);
        }
        edges.push_back(nw);
    }
}

pair<vector<int>,vector<vector<int>>> spfa(int be){
    int dis[N+N];
    bool f[N+N];
    for(int i = 0;i<N+N-10;++i)dis[i]=INF,f[i]=false;
    dis[be]=0;
    queue<int> q;
    vector<int> dist,sing;
    vector<vector<int>> road;
    for(int i=0;i<N;++i)road.push_back(sing);
    road[be].push_back(be);
    q.push(be),f[be]=true;
    while(!q.empty()){
        int nw = q.front();
        q.pop();
        f[nw]=false;
        for(int i=0;i<edges[nw].size();++i){

            if(dis[i]>dis[nw]+edges[nw][i]){
                vector<int> u = road[nw];
                u.push_back(i);
                road[i]=u;
                dis[i]=dis[nw]+edges[nw][i];
                if(!f[i]){
                    q.push(i);
                    f[i]=true;
                }
            }
        }
    }
    for(int i=0;i<N;++i)
        dist.push_back(dis[i]);
    return pair(dist,road);
}
int main(){
    freopen("listt.data","r",stdin);
    read_in();
    freopen("fullmap.data","w",stdout);
    vector<vector<vector<int>>>road;
    cout<<"     ";
    for(int i = 0;i<N;++i)cout<<station_list[i]<<"  ";
    cout<<endl;
    for(int i = 0;i<N;++i){
        cout<<station_list[i]<<"    ";
        pair<vector<int>,vector<vector<int>>> res = spfa(i);
        vector<int> dis = res.first;
        road.push_back(res.second);
        for(int j:dis)cout<<j<<"    ";
        cout<<endl;

    }
    fclose(stdout);
    freopen("detial.data","w",stdout);
    for(int i = 0;i<N;++i){
        for(int j=0;j<N;++j){
            if(road[i][j].size()>2){
                cout<<endl;
                for(int k:road[i][j]){
                    cout<<station_list[k]<<"->";
                }
                cout<<endl;
            }
        }
    }
}