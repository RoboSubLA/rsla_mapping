#include <iostream>
#include <vector>

#include "./mapping.hpp"

#include "./process_monitor.hpp"

#include "./spatial_map.hpp"

Mapping::Mapping()
{
    // MapCell* default_cell = new MapCell;

    SpatialMap<int> spatial_map(3, 3, 3);

    int counter = 0;
    for (int z = 0; z < spatial_map.axis_size(2); z++) {
        for (int y = 0; y < spatial_map.axis_size(1); y++) {
            for (int x = 0; x < spatial_map.axis_size(0); x++) {
                spatial_map.set(x, y, z, &counter);
            }
        }
    }

    spatial_map.print();

    MapCell i;

    std::cout << "default int: " << i.shape << std::endl;

    //
    // topographic map
    // LogicalMap<MapCell>

    // use pointers for cells so that changes are reflected in both maps

    // path finding A*star manhattan distance using array shape?

    // need to correct for dead reckoning
    // what sensors do we have, what will localization take care of?
    // loop closure correct the space at least once?

    // what am i getting from localization/computer vision,
    // what am i giving to everyone else

    // ros2 messages

    // Vector3f a(1, 1, 1);
    // Vector3f b(1, 1, 1);

    // sdf_box(a, b);
}

Mapping::~Mapping()
{
    std::cout << "kbyeeeee" << std::endl;
}

// float Mapping::sdf_empty()
// {
//     return -1;
// }

// float Mapping::sdf_box(Vector3f p, Vector3f b, Matrix4f t)
// {
//     Vector3f q = p.cwiseAbs() - b;
//     return fmax(q.norm(), 0.0) + fmin(fmax(q.x(), fmax(q.y(), q.z())), 0.0);
// }

// float Mapping::sdf_sphere(Vector3f p, float s, Matrix4f t)
// {
//     return p.norm() - s;
// }

// float Mapping::sdf_torus(Vector3f p, Vector2f ts, Matrix4f t)
// {
//     float x = Vector3f(p.x(), 0.f, p.z()).norm() - ts.x();
//     float y = p.y();
//     Vector2f q = Vector2f(x, y);
//     return q.norm() - ts.y();
// }
