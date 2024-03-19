#include <bits/stdc++.h>

using namespace std;

void floyd_warshall(vector<vector<int>> &adj_list)
{
    int n = adj_list.size();

    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (adj_list[i][k] < INT_MAX && adj_list[k][j] < INT_MAX)
                {
                    adj_list[i][j] = min(adj_list[i][j], adj_list[i][k] + adj_list[k][j]);
                }
            }
        }
    }
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

    int n, m, u, v, w;

    input >> n >> m;

    vector<vector<int>> adj_list(n, vector<int>(n, INT_MAX));

    for(int i = 0; i < n; i++)
    {
        adj_list[i][i] = 0;
    }

    for(int i = 0; i < m; i++)
    {
        input >> u >> v >> w;

        adj_list[u - 1][v - 1] = w;
        adj_list[v - 1][u - 1] = w;
    }

    input.close();

    floyd_warshall(adj_list);

    for(int i = 0; i < n; i++)
    {
        cout << i + 1 << ": ";
        for(int j = 0; j < n; j++)
        {
            cout << "(" << j + 1 << ", ";
            if(adj_list[i][j] != INT_MAX)
            {
                cout << adj_list[i][j] << ") ";
            }
            else
            {
                cout << "-1) ";
            }
        }
        cout << "\n";
    }

    if(out_file != "")
    {
        ofstream output(out_file);

        if(!output)
        {
            cerr << "Nao foi possivel criar o arquivo de saida.\n";

            return 1;
        }

        for(int i = 0; i < n; i++)
        {
            output << i + 1 << ": ";
            for(int j = 0; j < n; j++)
            {
                output << "(" << j + 1 << ", ";
                if(adj_list[i][j] != INT_MAX)
                {
                    output << adj_list[i][j] << ") ";
                }
                else
                {
                    output << "-1) ";
                }
            }
            output << "\n";
        }

        output.close();
    }

    return 0;
}