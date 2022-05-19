#include <iostream>
using namespace std;

#define V 5

#define INF 177013

void printSolution(int dist[][V]);

void Floyd(int graph[][V])
{
    int dist[V][V], i, j, k;

    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    for (k = 0; k < V; k++)
    {
        for (i = 0; i < V; i++)
        {
            for (j = 0; j < V; j++)
            {
                if (dist[i][j] > (dist[i][k] + dist[k][j]) && (dist[k][j] != INF && dist[i][k] != INF))
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    printSolution(dist);
}

void printSolution(int dist[][V])
{
    cout << "The following matrix shows the shortest "
            "distances"
            " between every pair of vertices \n";
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (dist[i][j] == INF)
                cout << "INF"
                     << "     ";
            else
                cout << dist[i][j] << "     ";
        }
        cout << endl;
    }
}

int main()
{
    int graph[V][V] = {{0, 10, INF, 5, INF},
                       {INF, 0, 1, 2, INF},
                       {INF, INF, 0, INF, 4},
                       {INF, 8, 9, 0, 2},
                       {7, INF, 6, INF, 0}};

    Floyd(graph);
    return 0;
}