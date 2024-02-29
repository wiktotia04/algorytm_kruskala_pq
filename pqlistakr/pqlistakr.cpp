#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "dsu.h"
#include "kolejka.h"
#include <chrono> 


using namespace std;
using namespace std::chrono;


struct TEdge
{
    int u;
    int v;
    int weight;
};


class Graph {
    PriorityQueue pq;
    vector<TEdge> edgelist;
    int V;

public:
    Graph(int V) { this->V = V; }

    int z = 0;
    // dodawanie wierzchołków do grafu
    void addEdge(int x, int y, int w)
    {
        z = (x > z) ? x : z;
        z = (y > z) ? y : z;
        bool edge_exists = false;
        for (TEdge& e : edgelist) {
            if ((e.u == x && e.v == y) || (e.u == y && e.v == x))
            {
                edge_exists = true;
                break;
            }

        }

        if (!edge_exists)
        {
            edgelist.push_back({ x, y, z });
            pq.push(x, y, w);
        }

    }

    void kruskals_mst()
    {
        DSU s(5000);
        int ans = 0;
       

       // cout << "wybrane krawędzie" << endl;


        // zapisanie elementów do kolejki prio
        while (!pq.empty()) {

            int w = pq.frontprio();
            int x = pq.front_u();
            int y = pq.front_v();
            // cout << pq.front_u() << " " << pq.front_v() << " " << pq.frontprio() << endl;
            pq.pop();

            // nie tworz koła
            if (s.find(x) != s.find(y)) {
                s.unite(x, y);
                ans += w;
                //cout << x << " -- " << y << " == " << w << endl;
            }

        }

        //cout << "Minimalne drzewo spinajace:" << ans << endl;
    }
};

int main()
{ // Otwórz plik w trybie dopisywania (ios::app)
    ofstream outputFile("czas320.txt", ios::app);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            int value = 1 + i;
            int n, v1, v2, v3;


            string filename = "graph320_" + to_string(value) + ".txt";
            ifstream inputFile(filename);

            if (!inputFile.is_open()) {
                cout << "Error: Failed to open the input file: " << filename << endl;
                continue;  // Przejdź do następnej iteracji pętli
            }

            auto start = high_resolution_clock::now(); // Zapisz czas początkowy

            inputFile >> n; // Odczytaj ilość połączeń



            // Dopisz nowe dane w nowej linii
            outputFile << " ";

            Graph g(n);

            // Odczytaj kolejne definicje krawędzi
            for (int i = 0; i < n; i++) {
                inputFile >> v1 >> v2 >> v3;    // Wierzchołek startowy, końcowy i waga krawędzi
                g.addEdge(v1, v2, v3);
            }

            g.kruskals_mst();

            auto stop = high_resolution_clock::now(); // Zapisz czas końcowy
            auto duration = duration_cast<microseconds>(stop - start); // Oblicz czas trwania

            // cout << "Czas działania programu dla pliku " << filename << ": " << duration.count() << " mikrosekund" << endl;

             // Dopisz czas trwania do pliku w nowej linii
            outputFile << duration.count();
            // outputFile.close();


        }

        outputFile << endl;

    }
    return 0;
}