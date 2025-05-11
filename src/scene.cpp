#include "scene.hpp"
#include "visu.hpp"
#include <cmath>

Scene::Scene(): nb_object(0), railCube(nullptr), innerCurve(nullptr), outerCurve(nullptr) {}
Scene::~Scene() {
    for (auto obj : les_objets) delete obj;
    for (auto b : balasts) delete b;
    for (auto t : traverses) delete t;
    delete railCube; delete innerCurve; delete outerCurve;
}

void Scene::addOneObject(unsigned int typ_obj, float* diffuse, float* trans,
                         float rot, int typ_rot, float scale) {
    les_objets.push_back(new GLObject(typ_obj, diffuse));
    translations.insert(translations.end(), trans, trans + 3);
    rotation_angles.push_back(rot);
    rotation_axes.push_back(typ_rot);
    scales.push_back(scale);
    nb_object++;
}

void Scene::createScene() {
    // Sol
    float tr1[3] = {0.0f, -1.0f, 0.0f}; float col1[3] = {0.8f,0.8f,0.8f};
    addOneObject(QUAD, col1, tr1, 0.0f, 2, 10.0f);

    // Balasts
    for (int i = 0; i < NUM_BALASTS_STRAIGHT; ++i)
        balasts.push_back(basicCylinder(BALAST_HEIGHT, BALAST_RADIUS));

    // Traverses (cubes échelonnés)
    for (int i = 0; i < NUM_TRAVERSES; ++i)
        traverses.push_back(basicCube(1.0f));
}

void Scene::makeRot(int trot, float arot) {
    if (trot==1) glRotatef(arot,1,0,0);
    else if (trot==2) glRotatef(arot,0,1,0);
    else glRotatef(arot,0,0,1);
}

void Scene::createStraightRail(bool courbure){
    glPushMatrix();
    if(!courbure){
        makeRot(2,90.0f);
        glTranslatef(-REEL_CELL_SIZE, 0, 0);
    }
    makeRot(1,90.0f);
    float mid = (BALAST_START_X + BALAST_END_X)*0.5f;
    glTranslatef(mid,0.2f,-0.1f);
    for (int i=0;i<NUM_BALASTS_STRAIGHT;++i) {
        glPushMatrix();
        float x = BALAST_START_X + i*BALAST_SPACING - mid;
        glTranslatef(x,0,0);
        balasts[i]->createVAO();
        balasts[i]->draw();
        glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();
    if(!courbure){
        makeRot(2,90.0f);
        glTranslatef(-REEL_CELL_SIZE, 0, 0);
    }
    makeRot(2, 90.0f);
    glTranslatef(-(RAIL_SR * REEL_CELL_SIZE + POS_X_RAIL1 * REEL_CELL_SIZE / CELL_SIZE), RAIL_HEIGHT / 2, mid);
    const int TI[2] = {1,3};
    for (int k=0;k<2;++k) {
        glPushMatrix();
        float x = BALAST_START_X + TI[k]*BALAST_SPACING - mid;
        glTranslatef(x,0,0);
        glScalef(TRAV_WIDTH,TRAV_THICK,BALAST_SPACING*(NUM_BALASTS_STRAIGHT-1)+RAIL_SR*2);
        traverses[k]->createVAO(); 
        traverses[k]->draw();
        glPopMatrix();
    }
    glPopMatrix();
}

void Scene::createCurvedRail(int a, float t, bool curved_in){
    float ang = 10.0f;
    
    glPushMatrix();
    makeRot(1,90.0f);
    makeRot(3, a);
    if(t == 2){
        glTranslatef(0, -REEL_CELL_SIZE, 0);
    }
    if(!curved_in){
        glTranslatef(REEL_CELL_SIZE, REEL_CELL_SIZE, 0);
    }
    glTranslatef(-0.2, 0.2, -0.1);
    for (int i = 0; i < NUM_BALASTS_CURVED; ++i, ang += 35) {     
        glPushMatrix();
        makeRot(3, ang);
        balasts[i]->createVAO();
        balasts[i]->draw();
        glPopMatrix();
        
    }
    glPopMatrix();
}

std::vector<TrackType> Scene::classifyTrack(const std::vector<std::pair<int,int>>& path) {
    std::vector<TrackType> result;
    int n = path.size();
    if (n < 3) {
        return std::vector<TrackType>(n, STRAIGHT);
    }

    result.push_back(STRAIGHT);

    for (int i = 1; i < n-1; ++i) {
        auto [x0, y0] = path[i-1];
        auto [x1, y1] = path[i];
        auto [x2, y2] = path[i+1];

        int dx1 = x1 - x0;
        int dy1 = y1 - y0;
        int dx2 = x2 - x1;
        int dy2 = y2 - y1;
        if (dx1 * dy2 == dy1 * dx2) {
            result.push_back(STRAIGHT);
        } else {
            int cross = dx1 * dy2 - dy1 * dx2;
            if (cross > 0) {
                result.push_back(CURVED_IN);
            } else {
                result.push_back(CURVED_OUT);
            }
        }
    }

    result.push_back(STRAIGHT);
    return result;
}

void Scene::drawScene(const std::vector<std::pair<int, int>>& path) {

    //Le sol
    glPushMatrix();
    makeRot(rotation_axes[0],rotation_angles[0]);
    glScalef(scales[0] * 3.0, scales[0] * 3.0, scales[0] * 3.0);
    les_objets[0]->glDrawObject();
    glPopMatrix();

    auto angle = 270;
    int t = 0;
    auto p = classifyTrack(path);
    auto courbure = false;
    for(size_t i = 0; i < path.size(); i++){
        glPushMatrix();
        glTranslatef(float(path.at(i).first)* REEL_CELL_SIZE, 0, float(path.at(i).second)* REEL_CELL_SIZE);
        if(p.at(i) == STRAIGHT){
            createStraightRail(courbure);
        }
        else{
            courbure = !courbure;
            if(p.at(i) == CURVED_IN){
                createCurvedRail(angle, t, true);
                angle = (angle + 90) % 360;
            }
            if(p.at(i) == CURVED_OUT){
                createCurvedRail(angle, t, false);
                angle = (angle - 90) % 360;
                if(t == 0)
                    t = REEL_CELL_SIZE;
                else
                    t = 0; 
            }

        }
        glPopMatrix();
    }

}