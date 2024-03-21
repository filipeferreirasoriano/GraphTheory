#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> prim(vector<vector<pair<int, int>>> &adj, int first, int &min_cost)
{
    int size = adj.size();

    vector<pair<int, int>> agm(size);

    vector<int> parent(size, -1);
    vector<int> cost(size, INT_MAX);
    vector<bool> visited(size, false);

    cost[first] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> p_queue;

    p_queue.push({cost[first], first});

    while(!p_queue.empty())
    {
        int u = p_queue.top().second;
        p_queue.pop();

        visited[u] = true;

        for(auto v: adj[u])
        {
            if(!visited[v.first] && cost[v.first] > v.second)
            {
                cost[v.first] = v.second;
                parent[v.first] = u;

                p_queue.push({cost[v.first], v.first});
            }
        }
    }

    for(int i = 0; i < size; i++)
    {
        agm[i] = {parent[i], i};
        min_cost += cost[i];
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

    vector<vector<pair<int, int>>> adj_list(n);

    for(int i = 0; i < m; i++)
    {
        input >> u >> v >> w;

        adj_list[u - 1].push_back({v - 1, w});
        adj_list[v - 1].push_back({u - 1, w});
    }

    first--;

    input.close();
    
    int min_cost = 0;
    
    vector<pair<int, int>> agm = prim(adj_list, first, min_cost);

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
                if(p.first != -1)
                {
                    output << "(" << p.first + 1 << "," << p.second + 1 << ") ";
                }
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
                if(p.first != -1)
                {
                    cout << "(" << p.first + 1 << "," << p.second + 1 << ") ";
                }
            }
            cout << "\n";
        }
        else
        {
            cout << min_cost << "\n";
        }
    return 0;
}