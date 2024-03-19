#include <bits/stdc++.h>

using namespace std;

vector<int> dijkstra(vector<vector<pair<int, int>>> &adj_list, int first)
{
    vector<int> dist(adj_list.size(), INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> p_queue;

    dist[first] = 0;
    p_queue.push({dist[first], first});

    while(!p_queue.empty())
    {
        int u = p_queue.top().second;
        p_queue.pop();

        for(auto a: adj_list[u])
        {
            int v = a.first, w = a.second;

            if(dist[v] > dist[u] + w)
            {
                dist[v] = dist[u] + w;
                p_queue.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main(int argc, char *argv[])
{
    string in_file = "";
    string out_file = "";
    int first = 1;

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

    int n, m, a, b, w;

    input >> n >> m;
    
    vector<vector<pair<int, int>>> adj_list(n + 1);

    for(int i = 0; i < m; i++)
    {
        input >> a >> b >> w;

        adj_list[a].push_back({b, w});
        adj_list[b].push_back({a, w});
    }

    input.close();

    vector<int> dist = dijkstra(adj_list, first);

    for(int i = 1; i <= n; i++)
    {
        cout << i << ":";
        if(dist[i] != INT_MAX)
        {
            cout << dist[i] << " ";
        }
        else
        {
            cout << "-1 ";
        }
    }
    cout << "\n";

    if(out_file != "")
    {
        ofstream output(out_file);
        if(!output)
        {
            cerr << "Nao foi possivel criar o arquivo de saida.\n";

            return 1;
        }

        for(int i = 1; i <= n; i++)
        {
            output << i << ":";
            if(dist[i] != INT_MAX)
            {
                output << dist[i] << " ";
            }
            else
            {
                output << "-1 ";
            }
        }

        output << "\n";

        output.close();
    }

    return 0;
}