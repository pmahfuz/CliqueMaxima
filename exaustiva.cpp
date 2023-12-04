
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

// Função para encontrar a clique máxima
vector<int> encontrarCliqueMaxima(vector<vector<int>>& grafo, int numVertices) {
    vector<int> cliqueMaxima;
    vector<int> candidatos(numVertices); // Inicialmente, todos os vértices são candidatos
    for (int i = 0; i < numVertices; ++i) {
        candidatos[i] = i;
    }

    while (!candidatos.empty()) {
        int v = candidatos.back();
        candidatos.pop_back();

        bool podeAdicionar = true;
        for (int u : cliqueMaxima) {
            if (grafo[u][v] == 0) {
                podeAdicionar = false;
                break;
            }
        }

        if (podeAdicionar) {
            cliqueMaxima.push_back(v);
            vector<int> novosCandidatos;
            for (int u : candidatos) {
                bool adjacenteATodos = true;
                for (int c : cliqueMaxima) {
                    if (grafo[u][c] == 0) {
                        adjacenteATodos = false;
                        break;
                    }
                }
                if (adjacenteATodos) {
                    novosCandidatos.push_back(u);
                }
            }
            candidatos = novosCandidatos;
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
