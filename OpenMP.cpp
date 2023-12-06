#include <omp.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

void BronKerbosch(vector<int>& R, vector<int>& P, vector<int>& X, vector<vector<int>>& grafo, vector<vector<int>>& cliques) {
    if (P.empty() && X.empty()) {
        cliques.push_back(R); // Encontrou uma clique maximal
        return;
    }

    vector<int> P_temp = P; // Cópia temporária de P
    #pragma omp parallel for
    for (int v : P_temp) {
        vector<int> R_new = R;
        R_new.push_back(v);

        vector<int> P_new, X_new;
        // Intersecção de P com os vizinhos de v
        for (int u : P) {
            if (grafo[v][u] == 1) P_new.push_back(u);
        }
        // Intersecção de X com os vizinhos de v
        for (int u : X) {
            if (grafo[v][u] == 1) X_new.push_back(u);
        }

        BronKerbosch(R_new, P_new, X_new, grafo, cliques);

        P.erase(remove(P.begin(), P.end(), v), P.end()); // Remove v de P
        X.push_back(v);
    }
}

vector<int> encontrarCliqueMaxima(vector<vector<int>>& grafo, int numVertices) {
    vector<vector<int>> cliques;
    vector<int> R, P(numVertices), X;
    for (int i = 0; i < numVertices; ++i) P[i] = i;

    BronKerbosch(R, P, X, grafo, cliques);

    // Encontrar a maior clique
    vector<int> cliqueMaxima;
    for (const auto& clique : cliques) {
        if (clique.size() > cliqueMaxima.size()) {
            cliqueMaxima = clique;
        }
    }

    return cliqueMaxima;
}

// Função para ler o grafo a partir do arquivo de entrada
vector<vector<int>> LerGrafo(const string& nomeArquivo, int& numVertices) {
    ifstream arquivo(nomeArquivo);
    int numArestas;
    arquivo >> numVertices >> numArestas;

    vector<vector<int>> grafo(numVertices, vector<int>(numVertices, 0));

    for (int i = 0; i < numArestas; ++i) {
        int u, v;
        arquivo >> u >> v;
        grafo[u - 1][v - 1] = 1;
        grafo[v - 1][u - 1] = 1;  // O grafo é não direcionado
    }

    arquivo.close();

    return grafo;
}

int main() {
    string nomeArquivo = "grafo.txt";
    int numVertices;
    vector<vector<int>> grafo;

    grafo = LerGrafo(nomeArquivo, numVertices);

    vector<int> cliqueMaxima = encontrarCliqueMaxima(grafo, numVertices);

    cout << "Clique máxima encontrada:" << endl;
    for (int v : cliqueMaxima) {
        cout << (v + 1) << " "; // Ajustando a indexação para começar de 1
    }
    cout << endl;

    return 0;
}
