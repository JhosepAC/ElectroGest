#pragma once
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <climits>
#include <string>

using namespace std;

class Graph {
    int V; // Número de vértices
    vector<pair<int, int>>* adj; // Puntero a un array que contiene listas de adyacencia
    unordered_map<string, int> name_to_index; // Mapa de nombres a índices
    vector<string> index_to_name; // Vector de índices a nombres

public:
    Graph(vector<string> districts); // Constructor
    void addEdge(string u, string v, int w); // Función para añadir una arista al grafo
    vector<int> shortestPath(int s); // Función para encontrar el camino más corto desde una fuente
    int getIndex(string name); // Obtener el índice de un nombre
    string getName(int index); // Obtener el nombre de un índice
    void showMenu(); // Function to show the menu   
};

Graph::Graph(vector<string> districts) {
    V = districts.size();
    adj = new vector<pair<int, int>>[V];
    for (int i = 0; i < V; ++i) {
        name_to_index[districts[i]] = i;
        index_to_name.push_back(districts[i]);
    }
}

void Graph::addEdge(string u, string v, int w) {
    int u_index = getIndex(u);
    int v_index = getIndex(v);
    adj[u_index].push_back(make_pair(v_index, w));
    adj[v_index].push_back(make_pair(u_index, w));
}

vector<int> Graph::shortestPath(int src) {
    // Crear una cola de prioridad para almacenar vértices que están siendo preprocesados.
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Crear un vector para las distancias y las inicializa como infinito.
    vector<int> dist(V, INT_MAX);

    // Insertar la fuente en la cola de prioridad y inicializar su distancia como 0.
    pq.push(make_pair(0, src));
    dist[src] = 0;

    // Bucle hasta que la cola de prioridad esté vacía.
    while (!pq.empty()) {
        // El primer vértice en la cola es el vértice con la menor distancia.
        int u = pq.top().second;
        pq.pop();

        // 'i' es el iterador que recorre todos los vecinos de 'u'.
        for (auto i = adj[u].begin(); i != adj[u].end(); ++i) {
            // Obtener el vértice adyacente y el peso de la arista actual.
            int v = (*i).first;
            int weight = (*i).second;

            // Si hay un camino más corto a 'v' a través de 'u'.
            if (dist[v] > dist[u] + weight) {
                // Actualizar la distancia de 'v'.
                dist[v] = dist[u] + weight;
                pq.push(make_pair(dist[v], v));
            }
        }
    }

    return dist;
}

int Graph::getIndex(string name) {
    return name_to_index[name];
}

string Graph::getName(int index) {
    return index_to_name[index];
}

void Graph::showMenu() {

 

    vector<string> branches = { "Miraflores", "La Victoria", "Rimac", "La Molina", "San Martin de Porres", "Chorrillos" };

    //Mostar los distritos
    while (true) {
        cout << "Seleccione el distrito al que desea enviar el producto:\n";
        for (size_t i = 0; i < index_to_name.size(); ++i) {
            cout << i + 1 << ". " << index_to_name[i] << "\n";
        }
        cout << "0. Salir\n";

        int choice;
        cout << "Ingrese el numero de su eleccion: ";
        cin >> choice;

        if (choice == 0) {
            break;
        }

        if (choice < 1 || choice > index_to_name.size()) {
            cout << "Seleccion no valida. Por favor, intente de nuevo.\n";
            continue;
        }

        string domicilio = index_to_name[choice - 1];
        vector<int> dist = shortestPath(getIndex(domicilio));

        // Encontrar la sucursal más cercana
        int min_dist = INT_MAX;
        string nearest_district;

        for (const string& district : branches) {
            int district_index = getIndex(district);
            if (dist[district_index] < min_dist) {
                min_dist = dist[district_index];
                nearest_district = district;
            }
        }

        cout << "La sucursal mas cercana a " << domicilio << " esta en " << nearest_district << " con una distancia de " << min_dist << " unidades.\n";
    }
    
}


#endif // GRAPH_H
