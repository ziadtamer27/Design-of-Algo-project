#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>
#include <iomanip>
#include <numeric>
using namespace std;

// public class for Graph 
struct Graph {
    int n;
    vector<vector<int>> adj;
    Graph(int n) 
    {
        this->n = n;
        adj = vector<vector<int>>(n, vector<int>(n, 0));
    }
    // Undirected graph, add edge between u and v with weight w 
    void addEdge(int u, int v, int w) 
        { 
            adj[u][v]+=w; 
            adj[v][u]+=w;
        }
    long long cutWeight(const vector<bool>& inS) const 
    {
        // check all nodes ,if it's in S and in T then get edge weight and add to total
        long long t=0;
        for(int u=0 ; u<n ; ++u) 
            if(inS[u]) 
                for(int v=0 ; v<n ; ++v) 
                    if(!inS[v]) 
                        t+=adj[u][v];
        return t;
    }
    //Just print the adjacency matrix for visualization 
    // the node is True in S and False in T
    void print() const 
    {
        cout<<"Adjacency Matrix:\n";
        cout << "    ";
        for(int i=0;i<n;++i)  cout<<setw(4)<<i;
        cout<<"\n";
        for(int i=0;i<n;++i)
        {
            cout<<setw(4)<<i; 
            for(int j=0;j<n;++j) 
                cout<<setw(4)<<adj[i][j]; 
                cout<<"\n"; 
        }
    }
};


// A class to hold minimum cut, including its weight and the partition of vertices.
struct CutResult {
    long long weight; 
    vector<bool> partition;

    CutResult():weight(LLONG_MAX){}

    CutResult(long long w,vector<bool>p):weight(w),partition(p){}
    void print(const string& lbl) const 
    {
        cout<<lbl<<"\n";
        cout<<"Min Cut Weight : "<<weight<<"\n";
        cout<<"Partition S : { "; 
        for(int i=0 ; i<(int)partition.size() ; ++i) 
            if(partition[i]) cout<<i<<" ";
        cout<<"}\n";
        cout<<"Partition T : { "; 
        for(int i=0 ; i<(int)partition.size() ; ++i) 
            if(!partition[i]) cout<<i<<" ";
        cout<<"}\n";
    }
};

// BRUTE FORCE  O(2^n * n^2)
CutResult bruteForceCut(const Graph& g)
// return the object of min cut resulted from brute force method
{
    int n=g.n; 
    CutResult best; 
    long long total=1LL<<n;

    for(long long mask=1 ; mask<total-1 ; ++mask)
    {
        vector<bool> inS(n); 

        for(int i=0 ; i<n ; ++i) 
            inS[i] = (mask>>i)&1;

        long long w = g.cutWeight(inS); 
        if(w < best.weight) 
            best = CutResult(w,inS);
    }
    return best;
}

// ITERATIVE IMPROVEMENT  O(n^3) per restart
long long moveGain(const Graph& g,const vector<bool>& inS,int v)
{
    long long gn=0;
    for(int u=0;u<g.n;++u)
    {
        if(u==v||!g.adj[v][u]) continue; 
        if(inS[u]==inS[v]) gn-=g.adj[v][u]; 
        else gn+=g.adj[v][u]; 
    }
    return gn;
}

CutResult Iterative_improvement(const Graph& g,int R=50){
    srand(42); 
    int n=g.n; 
    CutResult gb;
    for(int r=0;r<R;++r){
        vector<bool> inS(n); 
        int ss,st;
        do
        { 
            for(int i=0;i<n;++i) inS[i]=rand()%2; 
            ss=(int)count(inS.begin(),inS.end(),true); 
            st=n-ss; 
        }
        while(!ss||!st);

        bool imp=true;
        while(imp)
        {
            imp=false; int bv=-1; 
            long long bg=0;
            for(int v=0;v<n;++v)
            {
                if(inS[v]&&ss==1) continue; 
                if(!inS[v]&&st==1) continue;
                long long gv=moveGain(g,inS,v); 
                if(gv>bg) { bg=gv; bv=v; }
            }
            if(bv!=-1)
{ 
                if(inS[bv])  {--ss;  ++st;}
                else         {++ss;--st;}
                inS[bv]=!inS[bv]; 
                imp=true; 
            }
        }
        long long w=g.cutWeight(inS); 
        if(w<gb.weight) 
            gb=CutResult(w,inS);
    }
    return gb;
}

void printCutEdges(const Graph& g,const CutResult& res)
{
    cout<<"Cut edges:\n"; 
    bool any=false;
    for(int u=0;u<g.n;++u) 
        for(int v=u+1;v<g.n;++v)
            if(g.adj[u][v]>0&&res.partition[u]!=res.partition[v])
            {
                cout<<"  ("<<u<<" - "<<v<<") w="<<g.adj[u][v]<<"\n";
                any=true;
            }
    if(!any) cout<<"  (none)\n";
}

int main(){
    cout<<"Task 8 : Minimum Cut in Weighted Graph\n";

    // Example 1
    {
        cout<<"\nEXAMPLE 1 : 6-vertex graph\n\n";
        Graph g(6);
        g.addEdge(0,1,3); 
        g.addEdge(0,2,1); 
        g.addEdge(1,2,2); 
        g.addEdge(1,3,4);
        g.addEdge(2,4,1); 
        g.addEdge(3,4,2); 
        g.addEdge(3,5,3); 
        g.addEdge(4,5,5);
        g.print();
        CutResult bf=bruteForceCut(g); 
        bf.print("Brute Force"); 
        printCutEdges(g,bf);
        CutResult ls=Iterative_improvement(g); 
        ls.print("Iterative Improvement"); 
        printCutEdges(g,ls);
        cout<<"\nBF="<<bf.weight<<" LS="<<ls.weight<<" Optimal? "<<(ls.weight==bf.weight?"YES":"NO")<<"\n";
    }

    // Example 2
    {
        cout<<"EXAMPLE 2 : 8-vertex two-chain \n\n";
        Graph g(8);
        g.addEdge(0,1,10);g.addEdge(0,4,1);g.addEdge(1,2,10);g.addEdge(1,5,1);
        g.addEdge(2,3,10);g.addEdge(2,6,1);g.addEdge(3,7,1);
        g.addEdge(4,5,10);g.addEdge(5,6,10);g.addEdge(6,7,10);
        g.print();
        CutResult bf=bruteForceCut(g); 
        bf.print("Brute Force"); 
        printCutEdges(g,bf);
        CutResult ls=Iterative_improvement(g,80); 
        ls.print("Iterative Improvement"); 
        printCutEdges(g,ls);
        cout<<"\nBF="<<bf.weight<<" LS="<<ls.weight<<" Optimal? "<<(ls.weight==bf.weight?"YES":"NO")<<"\n";
    }

    // Example 3
    {
        cout<<"EXAMPLE 3 : Two-cluster 4+4\n\n";
        Graph g(8);
        g.addEdge(0,1,8);g.addEdge(0,2,7);g.addEdge(0,3,6);g.addEdge(1,2,9);g.addEdge(1,3,8);g.addEdge(2,3,7);
        g.addEdge(4,5,8);g.addEdge(4,6,7);g.addEdge(4,7,6);g.addEdge(5,6,9);g.addEdge(5,7,8);g.addEdge(6,7,7);
        g.addEdge(1,4,1);g.addEdge(2,5,1);
        g.print();
        CutResult bf=bruteForceCut(g); 
        bf.print("Brute Force"); 
        printCutEdges(g,bf);
        CutResult ls=Iterative_improvement(g,80); 
        ls.print("Iterative Improvement"); 
        printCutEdges(g,ls);
        cout<<"\nBF="<<bf.weight<<" LS="<<ls.weight<<" Optimal? "<<(ls.weight==bf.weight?"YES":"NO")<<"\n";
    }

    return 0;
}