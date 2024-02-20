#ifndef MAPPING_HPP
#define MAPPING_HPP

// #include <Eigen/Dense>
#include <glm/mat4>
#include <glm/vec3>

using namespace Eigen;

enum sdf_type {
    SDF_EMPTY,
    SDF_CUBE,
    SDF_SPHERE,
    SDF_TORUS,
};

// I should probably read the rules for the competition huh?
enum object_type {
    TERRAIN,
    GOAL,
    TARGET,
};

struct MapCell {
    uint8_t shape = SDF_EMPTY;
    Matrix4f transform = Matrix4f::Identity();
    // std::string tags;
};

class Mapping {
public:
    Mapping();
    ~Mapping();

    // float sdf_empty();

    // float sdf_box(Vector3f p, Vector3f b, Matrix4f ts = Matrix4f::Identity());

    // float sdf_sphere(Vector3f p, float s, Matrix4f ts = Matrix4f::Identity());

    // float sdf_torus(Vector3f p, Vector2f t, Matrix4f ts = Matrix4f::Identity());

private:
    void ready();

    void update();
};

#endif