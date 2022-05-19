#include <iostream>

using namespace std;
#define INF 999999
#define V 8

int G[V][V] =
    {
        {0, 12, 5, 4, INF, INF, INF, INF},
        {12, 0, 9, 11, INF, INF, INF, INF},
        {5, 9, 0, 2, 2, 4, INF, INF},
        {4, 11, 2, 0, 7, INF, INF, INF},
        {INF, INF, 2, 7, 0, INF, 3, 6},
        {INF, INF, 4, INF, INF, 0, 8, 1},
        {INF, INF, INF, INF, 3, 8, 0, INF},
        {INF, INF, INF, INF, 6, 1, INF, 0},
};

int p[V];       // constructed MST
int key[V];     // store key from adjacency vertices
bool mstSet[V]; // set of vertices that is not included in MST

int minKey()
{
    int min = INF;
    int minIndex;
    for (int v = 0; v < V; v++)
    {
        if (mstSet[v] == false && key[v] < min)
        {
            min = key[v]; // if the vertice is not in the mstSet and key is also < min => change the index to that vertice
            minIndex = v;
        }
    }
    return minIndex;
}

void printMST()
{
    cout << "Edge   Weight" << endl;
    for (int i = 0; i < V; i++)
    {
        cout << static_cast<char>(p[i] + 'A') << " - " << static_cast<char>(i + 'A') << " " << key[i] << endl;
    }
}
void primMST()
{
    for (int i = 0; i < V; i++)
    {
        key[i] = INF, mstSet[i] = false;
    }
    key[0] = 0; // because beginning key
    p[0] = -1;  // because it is a root

    for (int count = 0; count < V - 1; count++)
    {
        int u = minKey();
        mstSet[u] = true; // choose the adjacency vertices to work and apply key value
        for (int v = 0; v < V; v++)
        {
            /*if (G[u][v] && mstSet[v] == false && G[u][v] < key[v])
            {
                p[v] = u;
                key[v] = G[u][v];
            }*/
            if (mstSet[v] == true)
            {
                for (int t = 0; t < V; t++)
                {
                    if (mstSet[t] == false)
                    {
                        if (G[v][t] < key[t])
                        {
                            key[t] = G[v][t];
                            p[t] = v;
                        }
                    }
                }
            }
        }
    }
}

int main()
{
    primMST();
    printMST();
    return 0;
}