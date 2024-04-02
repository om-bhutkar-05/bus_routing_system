#include"header.hpp"
Graph::Graph() {}

Graph::~Graph() {
    clear();
}

void Graph::addVertex(const string& id, const string& place_name, double latitude, double longitude) {
    if (vertices.find(id) == vertices.end()) {
        Vertex* newVertex = new Vertex;
        newVertex->id = id;
        newVertex->place_name = place_name;
        newVertex->latitude = latitude;
        newVertex->longitude = longitude;
        vertices[id] = newVertex;
    }
}

void Graph::addEdge(const string& source, const string& destination, double weight) {
    Vertex* srcVertex = getVertex(source);
    Vertex* destVertex = getVertex(destination);

    if (srcVertex && destVertex) {
        srcVertex->connections.push_back(make_pair(destination, weight));
    }
}

Vertex* Graph::getVertex(const string& id) {
    if (vertices.find(id) != vertices.end()) {
        return vertices[id];
    }
    return nullptr;
}

void Graph::display() {
    for (auto& pair : vertices) {
        cout << "Vertex ID: " << pair.second->id << endl;
        cout << "Place Name: " << pair.second->place_name << endl;
        cout << "Latitude: " << pair.second->latitude << endl;
        cout << "Longitude: " << pair.second->longitude << endl;
        cout << "Connections:" << endl;
        for (auto& connection : pair.second->connections) {
            cout << " -> " << connection.first << " (Weight: " << connection.second << ")" << endl;
        }
        cout << endl;
    }
}

void Graph::clear() {
    for (auto& pair : vertices) {
        delete pair.second;
    }
    vertices.clear();
}
