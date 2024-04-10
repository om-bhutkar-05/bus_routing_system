#include "header.hpp"
#include <fstream>

Graph::Graph(int vertices) {
    V = vertices;
    adjMatrix.resize(V, vector<double>(V, numeric_limits<double>::infinity()));
    nodes.resize(V);
}

void Graph::addEdge(int source, int destination, double weight) {
    adjMatrix[source - 1][destination - 1] = weight;
}

void Graph::populateFromJSON(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << filename << endl;
        return;
    }

    json data;
    try {
        file >> data;

        for (const auto& place : data["places"]) {
            int id = stoi(place["id"].get<string>());
            string name = place["place_name"].get<string>();
            nodes[id - 1] = {id, name};
        }

        for (const auto& connection : data["connections"]) {
            int source = stoi(connection["source"].get<string>());
            int destination = stoi(connection["destination"].get<string>());
            double weight = stod(connection["weight"].get<string>());
            addEdge(source, destination, weight);
        }
    } catch (const exception& e) {
        cerr << "Error parsing JSON: " << e.what() << endl;
        return;
    }
}

void Graph::printMatrix() {
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < V; ++i) {
        cout << nodes[i].name << ":\t";
        for (int j = 0; j < V; ++j) {
            if (adjMatrix[i][j] == numeric_limits<double>::infinity())
                cout << "INF ";
            else
                cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

vector<double> Graph::dijkstra(int source) {
    vector<double> distance(V, numeric_limits<double>::infinity());
    distance[source - 1] = 0;

    vector<bool> visited(V, false);

    for (int count = 0; count < V - 1; ++count) {
        int minIndex = -1;
        double minDist = numeric_limits<double>::infinity();

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && distance[v] <= minDist) {
                minDist = distance[v];
                minIndex = v;
            }
        }

        visited[minIndex] = true;

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && adjMatrix[minIndex][v] != numeric_limits<double>::infinity() &&
                distance[minIndex] != numeric_limits<double>::infinity() &&
                distance[minIndex] + adjMatrix[minIndex][v] < distance[v]) {
                distance[v] = distance[minIndex] + adjMatrix[minIndex][v];
            }
        }
    }

    return distance;
}
