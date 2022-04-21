const int MAXN = 1e6 + 42;

map<char, int> to[MAXN];
int link[MAXN], que[MAXN], sz = 1;

void add_str(string s, int k)
{
    int v = 0;
    for(auto c: s)
    {
        if(!to[v][c]) to[v][c] = sz++;
        v = to[v][c];
    }
}

void push_links()
{
    link[0] = -1;
    int st = 0, fi = 1;
    que[0] = 0;
    while(st < fi)
    {
        int v = que[st++];
        for(auto it: to[v])
        {
            int u = it.second;
            int c = it.first;
            int j = link[v];
            while(j != -1 && !to[j][c]) j = link[j];
            if(j != -1) link[u] = to[j][c];
            que[fi++] = u;
        }
    }
}