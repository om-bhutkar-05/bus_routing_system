#include "header.hpp"
#include <fstream>
#include <algorithm> 
#include <cctype> 

string rm(string str) {
    
    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
    transform(str.begin(), str.end(), str.begin(), ::tolower);

    return str;
}
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


int Graph::getNodeID(const string& placeName) const {
    for (const Node& node : nodes) {
        if (rm(node.name) == rm(placeName)) {
            return node.id;
        }
    }
    return -1;
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
