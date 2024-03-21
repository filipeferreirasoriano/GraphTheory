#include <bits/stdc++.h>

using namespace std;

vector<int> parent;
vector<int> height;

struct Edge
{
    int u;
    int v;
    int w;
};

int func(Edge a, Edge b)
{
    return a.w < b.w;
}

void make_set(int x)
{
    parent[x] = x;
    height[x] = 0;
}

int find_set(int x)
{
    if(x == parent[x])
    {
        return x;
    }
    return parent[x] = find_set(parent[x]);
}

void union_set(int a, int b)
{
    a = find_set(a);
    b = find_set(b);

    if(a != b)
    {
        if(height[a] < height[b])
        {
            int aux = a;
            a = b;
            b = aux;
        }
        if(height[a] == height[b])
        {
            height[a]++;
        }
        parent[b] = a;
    }
}

vector<pair<int, int>> kruskal(vector<Edge> &adj, int &min_cost, int n)
{
    vector<pair<int, int>> agm;

    for(int i = 0; i < n; i++)
    {
        make_set(i);
    }

    for(auto edge: adj)
    {
        if(find_set(edge.u) != find_set(edge.v))
        {
            min_cost += edge.w;
            
            union_set(edge.u, edge.v);
            agm.push_back({edge.u, edge.v});
        }
    }

    return agm;
}

int main(int argc, char *argv[])
{
    string in_file = "";
    string out_file = "";
    int first = 1;
    bool print_solution = false;

    for(int i = 1; i < argc; i++)
    {
        string arg = argv[i];

        if(arg == "-h")
        {
            cout << "Help:\n"
            << "-h: mostra o help\n"
            << "-o <arquivo>: redireciona a saida para o 'arquivo'\n"
            << "-f <arquivo>: indica o 'arquivo que contem o grafo de entrada\n"
            << "-i: vertice inicial\n";

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
        else if(arg == "i" && i < (argc - 1))
        {
            first = atoi(argv[++i]);
        }
        else if(arg == "-s")
        {
            print_solution = true;
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

    int n, m, u, v, w;

    input >> n >> m;

    parent.resize(n);
    height.resize(n);

    vector<Edge> adj_list;

    for(int i = 0; i < m; i++)
    {
        input >> u >> v >> w;

        adj_list.push_back({u - 1, v - 1, w});
    }

    first--;

    input.close();

    sort(adj_list.begin(), adj_list.end(), func);
    
    int min_cost = 0;

    vector<pair<int, int>> agm = kruskal(adj_list, min_cost, n);

    if(out_file != "")
    {
        ofstream output(out_file);

        if(!output)
        {
            cerr << "Nao foi possivel criar o arquivo de saida.\n";

            return 1;
        }

        if(print_solution)
        {
            for(auto p: agm)
            {
                output << "(" << p.first + 1 << "," << p.second + 1 << ") ";
            }
            output << "\n";
        }
        else
        {
            output << min_cost << "\n";
        }

        output.close();
    }

    if(print_solution)
    {
        for(auto p: agm)
        {
            cout << "(" << p.first + 1 << "," << p.second + 1 << ") ";
        }
        cout << "\n";
    }
    else
    {
        cout << min_cost << "\n";
    }
    return 0;
}