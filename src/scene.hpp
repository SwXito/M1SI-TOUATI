#pragma once

#include <vector>
#include "globject.hpp"
#include "../third_party/glbasimac/glbasimac/glbi_convex_2D_shape.hpp"
#include "../third_party/glbasimac/tools/basic_mesh.hpp"

using namespace glbasimac;

constexpr float REEL_CELL_SIZE  = 2.0f;

// Paramètres des balasts (doivent tenir sur un carré 1×1)
constexpr int   NUM_BALASTS     = 5;      // 5 balasts
constexpr float BALAST_RADIUS   = 0.1f;   
constexpr float BALAST_HEIGHT   = 1.6f;  
constexpr float BALAST_START_X  = 0.2f;   // position X du 1er balast
constexpr float BALAST_END_X    = 1.8f;   // position X du dernier balast
constexpr float BALAST_SPACING  = (BALAST_END_X - BALAST_START_X) / (NUM_BALASTS - 1);

// Traverses (2 sous les balasts 2 et 4)
constexpr int   NUM_TRAVERSES   = 2;
constexpr float TRAV_WIDTH      = 0.1f;
constexpr float TRAV_THICK      = 0.1f;

// Rails (droits et courbes)
constexpr float POS_X_RAIL1     =  3.0f;
constexpr float POS_X_RAIL2     =  7.0f;
constexpr float RAIL_SR         =  0.2f;
constexpr float RAIL_HEIGHT     =  0.5f;
constexpr float CELL_SIZE       = 10.0f;

class Scene {
public:
    Scene(); ~Scene();
    void addOneObject(unsigned int typ_obj, float* diffuse, float* trans,
                      float rot, int typ_rot, float scale);
    void createScene(); 
    void drawScene(const std::vector<std::pair<int, int>>&);
    static void makeRot(int trot, float arot);

private:
    void createStraightRail();

    int nb_object;
    std::vector<float> translations;
    std::vector<float> rotation_angles;
    std::vector<int> rotation_axes;
    std::vector<float> scales;
    std::vector<GLObject*> les_objets;
    std::vector<IndexedMesh*> balasts;
    std::vector<IndexedMesh*> traverses;
    IndexedMesh* railCube;
    GLBI_Convex_2D_Shape* innerCurve;
    GLBI_Convex_2D_Shape* outerCurve;
};
