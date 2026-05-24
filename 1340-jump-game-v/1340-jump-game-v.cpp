struct Edge{int to,nxt;};
class Solution{
    static constexpr int N=1000,M=N*(N-1)/2;
    static inline Edge e[M];
    static inline int adj[N],deg[N],dp[N],st[N],q[N],idx;
    static inline void add(int u,int v){
        e[idx]={v,adj[u]},adj[u]=idx++,++deg[v];
    }
public:
    static int maxJumps(vector<int>& a,int d){
        int n=a.size(),top=-1,f=0,b=0;
        idx=0;
        memset(adj,-1,n*sizeof(int));
        memset(deg,0,n*sizeof(int));
        fill(dp,dp+n,1);
        for(int i=0;i<n;i++){
            while(top>=0&&a[st[top]]<a[i]){
                int j=st[top--];
                if(i-j<=d) add(j,i);
            }
            st[++top]=i;
        }
        top=-1;
        for(int i=n-1;i>=0;i--){
            while(top>=0&&a[st[top]]<a[i]){
                int j=st[top--];
                if(j-i<=d) add(j,i);
            }
            st[++top]=i;
        }
        for(int i=0;i<n;i++) if(!deg[i]) q[b++]=i;
        while(f<b){
            int u=q[f++];
            for(int k=adj[u];k!=-1;k=e[k].nxt){
                int v=e[k].to;
                dp[v]=max(dp[v],dp[u]+1);
                if(--deg[v]==0) q[b++]=v;
            }
        }
        return *max_element(dp,dp+n);
    }
};