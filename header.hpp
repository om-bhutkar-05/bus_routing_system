
#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

using namespace std;

struct Vertex {
    string id;
    string place_name;
    double latitude;
    double longitude;
    list<pair<string, double>> connections;
};

class Graph {
private:
    unordered_map<string, Vertex*> vertices;

public:
    Graph();
    ~Graph();
    void addVertex(const string& id, const string& place_name, double latitude, double longitude);
    void addEdge(const string& source, const string& destination, double weight);
    Vertex* getVertex(const string& id);
    void display();
    void clear();
};


