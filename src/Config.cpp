#include "Config.hpp"
#include <fstream>
#include <iostream>

bool Config::loadFromFile(const FilePath& filePath) {
    std::ifstream in(filePath.c_str());
    if (!in.is_open()) {
        std::cerr << "Error: cannot open JSON file '" << filePath << "'\n";
        return false;
    }
    try {
        nlohmann::json j;
        in >> j;
        // size_grid: entier
        grid.size = j.at("size_grid").get<int>();
        if (j.contains("cell_size")) {
            grid.cellSize = j.at("cell_size").get<float>();
        }
        // origin: [x, y]
        auto ori = j.at("origin");
        origin.x = ori.at(0).get<int>();
        origin.y = ori.at(1).get<int>();
        // path: tableau de paires [col, row]
        path.clear();
        for (auto& coord : j.at("path")) {
            int c = coord.at(0).get<int>();
            int r = coord.at(1).get<int>();
            path.emplace_back(c, r);
        }
    } catch (const nlohmann::json::exception& e) {
        std::cerr << "JSON parse error: " << e.what() << "\n";
        return false;
    }
    return true;
}

const std::vector<std::pair<int, int>>& Config::getPath() const {
    return path;
}