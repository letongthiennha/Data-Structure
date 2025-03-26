#pragma once

#include <string>

//temporary, readapt later

const std::string addEdge = {
    "graph[u][v] = 1;\n"
    "graph[v][u] = 1;" 
};

const std::string removeEdge = {
    "if (graph[u][v] == graph[v][u])\n" 
        "graph[v][u] = 0;\n"
    "graph[u][v] = 0;" 
};

const std::string setWeight = {
    "if (graph[u][v] == graph[v][u])\n" 
        "graph[v][u] = weight;\n"
    "graph[u][v]= weight;"
};

const std::string toggleDirected = {
    "graph[v][u] = 0;"
};

const std::string untoggleDirected = {
    "if (graph[u][v] == graph[v][u]) return;\n"
    "if (graph[u][v]) graph[v][u] = graph[u][v];"
};

const std::string Dijkstra = {
    "distances[source] = 0;\n"
    "pQueue.push(source);\n"
    "while (!pQueue.empty()) {\n"
    "    current = pQueue.pop();\n"
    "    for (neighbor : graph.getNeighbors(current)) {\n"
    "        if (distances[current] + weight < distances[neighbor]) {\n"
    "            distances[neighbor] = distances[current] + weight;\n"
    "            pQueue.push(neighbor);\n"
    "        }\n"
    "    }\n"
    "}"
};