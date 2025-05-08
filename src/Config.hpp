#pragma once

#include <string>
#include <vector>
#include "FilePath.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

struct GridInfo {
    int size;      // taille de la grille (carrée)
    float cellSize = 1.0f;
};

struct Origin {
    int x;
    int y;
};

class Config {
public:
    GridInfo grid;
    Origin origin;
    std::vector<std::pair<int,int>> path;  // suite de coordonnées (col, row)

    // Charge la configuration depuis un fichier JSON
    bool loadFromFile(const FilePath& filePath);
};