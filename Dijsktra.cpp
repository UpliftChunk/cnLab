#include <bits/stdc++.h>
using namespace std;

#define fe(n)      for(int e=1; e<=n; e++)
#define fr(a,b)    for(auto r=a; r<b; r++)
#define line(var)  cout<<(var)<<'\n'
#define nl         cout<<'\n'
#define show(var)  cout<<(var)<<' '
#define showp(i,v) cout<<(i)<<':'<<v<<' '


// dijkstra
void dijkstra(vector<vector<int>> v, int src, vector<int> &dist, vector<int> &par)
{
    int n= v.size();
    vector<bool> NotVisited(n,1);
   
    int visits=0, cur=src;
    dist[src]=0;
    par[src]=src;
    while(visits!=n){
        NotVisited[cur]= 0;
        visits++;
       
        int mini= INT_MAX, miniInd=-1;
        fr(0,n){
            if(NotVisited[r] && v[cur][r]!=INT_MAX){
                if(dist[r]> dist[cur]+v[cur][r]){
                    dist[r]=dist[cur]+v[cur][r];
                    par[r]=cur;
                }
            }
            if(NotVisited[r] && mini> dist[r]){
                mini= dist[r];
                miniInd= r;
            }
        }
        cur= miniInd;
    }
   
}

int main() {
   int n, ed, a, b, x;
   show("Enter number of nodes: ");
   cin>>n;
   show("Enter number of edges: ");
   cin>>ed;

   vector<vector<int>> v(n, vector<int>(n,INT_MAX));
   fe(n) v[e-1][e-1]=0;

   line("Enter edge nodes and cost: ");
   map<char, int> m;
   map<int, char> ind;
   int nodeNum=1;
   char v1, v2;
   fe(ed){
      cin>>v1>>v2>>x;
      if(m[v1]!=0) a=m[v1]-1;
      else {
         m[v1]=nodeNum;
         a=nodeNum-1;
         ind[a]= v1;
         nodeNum++;
      }
      if(m[v2]!=0) b=m[v2]-1;
      else {
         m[v2]=nodeNum;
         b=nodeNum-1;
         ind[b]= v2;
         nodeNum++;
      }
      
      v[a][b]=v[b][a]=x;
   }

   char S;
   show("Enter source node:");
   cin>>S;
   int src= m[S]-1;

   vector<int> dist(n, INT_MAX), par(n, -1);

   dijkstra(v, src, dist, par);

   showp("Source", src+1);
   line("\nNode\tCost\tIntermediates");
   for(auto k:m){
      int i=k.second -1;
      cout<<k.first<<"\t"<<dist[i]<<"\t";
      if(par[i]==src) show("[null]");
      else{
         do{
            show(ind[par[i]]);
            i= par[i];
         }while(par[i]!=src);
      }
      nl;
   }

   return 0;
}


// input:
// 9 14
// A B 4
// A H 8
// B C 8
// B H 11
// C D 7
// C I 2
// C F 4
// D F 14
// D E 9
// E F 10
// F G 2
// G I 6
// G H 1
// H I 7
// A

// Output:
// Source:1
// Node Cost Intermediates
// A 0 [null]
// B 4 [null]
// C 12 B
// D 19 C B
// E 21 F G H
// F 11 G H
// G 9 H
// H 8 [null]
// I 14 C B 