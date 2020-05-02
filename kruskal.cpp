#include <bits/stdc++.h>
using namespace std;
/*
                1 --- 3
              / |    /|
             0  |  /  |
              \ |/    |
                2 --- 4
    Contoh graph dengan bobot nilai: 
    0----1 : 4
    0----2 : 8
    1----3 : 6
    1----2 : 2
    2----3 : 3
    2----4 : 9
    3----4 : 5
*/

/* Input yang dimasukkan adalah sebagai berikut :
5 7 
0 1 4
0 2 8
1 2 2
1 3 6
2 3 3
2 4 9
3 4 5

Keterangan : 
5 7 ===> memiliki 5 nodes dan 7 edges
0 1 4 => dari node 0 ke 1 memiliki bobot 4
*/
class Edge {
    public:
    int source;
    int dest;
    int weight;
};

bool compare(Edge e1, Edge e2) {
    return e1.weight < e2.weight;
}

int findParent(int node, int *parent) {
    if(parent[node] == node) {
        return node;
    }

    return findParent(parent[node], parent);
}

void kruskalAlgo(Edge *input, int nodes, int edges) {
    sort(input, input+edges, compare); //Mengurutkan edges berdasarkan bobot (weight)
    //ambil satu per satu dari yang terkecil. Jika ada yang cycle, maka taruh di array terakhir (push)
    //array T untuk menyimpan MST
    int *parent = new int[nodes];

    for (int i = 0; i < nodes; i++) {
        parent[i] = i; 
    }
    Edge *ouput = new Edge[nodes-1];
    int count = 0;
    int i = 0;
    while (count!=(nodes-1)) {
        Edge minEdge = input[i];

        int sourceParent = findParent(minEdge.source, parent);
        int destParent   = findParent(minEdge.dest, parent);

        if(sourceParent!=destParent) {
            ouput[count] = minEdge;
            count += 1;
            //now take union 
            parent[sourceParent] = destParent;
        }

        i += 1;
    }

    // Tampilkan MST
    cout << "MST yang terbentuk menggunakan algoritma Kruskal adalah :\n"; 
    int total_min_distance = 0;
    for(int i = 0; i < nodes-1; i++) {
        if(ouput[i].source < ouput[i].dest) {
            cout << ouput[i].source << " " << ouput[i].dest << " " << ouput[i].weight << endl;
            total_min_distance += ouput[i].weight;
        }
        else {
            cout << ouput[i].dest << " " << ouput[i].source << " " << ouput[i].weight << endl;
            total_min_distance += ouput[i].weight;
        }
    }
    cout << "Total Jarak Minimum adalah " << total_min_distance << endl;
    //free space
    delete[] ouput;
    delete[] parent;

    return;
}

int main() {
    int nodes, edges;
    cin >> nodes >> edges;
    //make an array of edges;
    Edge *input = new Edge[edges];
    for(int i = 0; i < edges; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        input[i].source = u;
        input[i].dest = v;
        input[i].weight = w;
    }
    kruskalAlgo(input, nodes, edges);

    return 0;
}
