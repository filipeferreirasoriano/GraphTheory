#include <bits/stdc++.h>

using namespace std;

vector<int> pre;
vector<int> post;
int cnt = 0;
int cnt2 = 0;

vector<vector<int>> reverse_graph(vector<vector<int>> &adj_list)
{
    int size = adj_list.size();
    vector<vector<int>> reversed(size);

    for(int u = 0; u < size; u++)
    {
        for(auto v: adj_list[u])
        {
            reversed[v].push_back(u);
        }
    }

    return reversed;
}

void dfs_rec(vector<vector<int>> &adj_list, int i)
{
    pre[i] = ++cnt;

    for(auto j: adj_list[i])
    {
        if(!pre[j])
        {
            dfs_rec(adj_list, j);
        }
    }

    post[i] = cnt2++;
}

void dfs_post(vector<vector<int>> &adj_list)
{
    int size = adj_list.size();
    for(int i = 0; i < size; i++)
    {
        if(!pre[i])
        {
            dfs_rec(adj_list, i);
        }
    }
}

void sort_post_vector()
{
    int size = post.size();
    vector<int> aux(size);

    for(int i = 0; i < size; i++)
    {
        aux[post[i]] = i;
    }

    post = aux;
}

void dfs_pre_rec(vector<vector<int>> &adj_list, int i, vector<int> &scc)
{
    pre[i] = ++cnt;
    scc.push_back(i);
    
    for(auto j: adj_list[i])
    {
        if(!pre[j])
        {
            dfs_pre_rec(adj_list, j, scc);
        }
    }
}

vector<vector<int>> dfs_pre(vector<vector<int>> &adj_list)
{
    vector<vector<int>> sccs;

    //pre.clear();
    pre.assign(adj_list.size(), 0);
    cnt = 0;

    int size = post.size();

    sort_post_vector();

    for(int i = size - 1; i >= 0; i--)
    {
        if(!pre[post[i]])
        {
            vector<int> scc;
            dfs_pre_rec(adj_list, post[i], scc);

            sccs.push_back(scc);
        }
    }

    return sccs;
}

int main(int argc, char *argv[])
{
    string in_file = "";
    string out_file = "";
    
    for(int i = 1; i < argc; i++)
    {
        string arg = argv[i];

        if(arg == "-h")
        {
            cout << "Help:\n"
            << "-h: mostra o help\n"
            << "-o <arquivo>: redireciona a saida para o 'arquivo'\n"
            << "-f <arquivo>: indica o 'arquivo que contem o grafo de entrada\n";

            return 0;
        }
        else if(arg == "-o" && i < (argc - 1))
        {
            out_file = argv[++i];
        }
        else if(arg == "-f" && i < (argc - 1))
        {
            in_file = argv[++i];
        }
    }

    if(in_file == "")
    {
        cerr << "O arquivo de entrada nao foi especificado. Use o parametro -f.\n";

        return 1;
    }

    ifstream input(in_file);

    if(!input)
    {
        cerr << "O arquivo de entrada nao foi encontrado.\n";

        return 1;
    }

    int n, m, u, v;

    input >> n >> m;

    vector<vector<int>> adj_list(n);

    for(int i = 0; i < m; i++)
    {
        input >> u >> v;

        adj_list[u - 1].push_back(v - 1);
    }

    input.close();

    vector<vector<int>> reversed_graph = reverse_graph(adj_list);

    cnt = 0;
    cnt2 = 0;

    pre.clear();
    pre.resize(n);

    post.clear();
    post.resize(n);

    dfs_post(reversed_graph);

    vector<vector<int>> sccs = dfs_pre(adj_list);

    if(out_file != "")
    {
        ofstream output(out_file);
        if(!output)
        {
            cerr << "Nao foi possivel criar o arquivo de saida.\n";

            return 1;
        }

        for(auto scc: sccs)
        {
            for(auto i: scc)
            {
                output << i + 1 << ' ';
            }
            output << '\n';
        }

        output.close();
    }

    for(auto scc: sccs)
    {
        for(auto i: scc)
        {
            cout << i + 1 << ' ';
        }
        cout << '\n';
    }

    return 0;
}