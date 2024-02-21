#ifndef SPATIAL_MAP_HPP
#define SPATIAL_MAP_HPP

#include <glm/ext.hpp>
#include <glm/glm.hpp>

#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class SpatialMap {
public:
    SpatialMap(int x = 4, int y = 4, int z = 4)
    {
        resize(x, y, z);

        T default_value;
        data.push_back(default_value);

        origin = glm::vec3(0.0f, 0.0f, 0.0f);

        std::cout << "here" << std::endl;
        print();

        std::cout << "here" << std::endl;
        for (T* elem : grid) {
            elem = &default_value;
        }

        std::cout << "here" << std::endl;
        print();

        std::cout << "here" << std::endl;
    };

    ~SpatialMap() {};

    void set(int x, int y, int z, T* value)
    {
        grid[x + (y * grid_size.x) + (z * grid_size.x * grid_size.y)] = value;
    }

    T* get(int x, int y, int z)
    {
        return grid[x + (y * grid_size.x) + (z * grid_size.x * grid_size.y)];
    }

    void resize(int x, int y, int z)
    {
        std::vector<T*> old_grid = grid;

        // int* new_data = new int[x * y * z];

        // to do copy contents of data into new_data

        grid.resize(x * y * z);
        grid_size = glm::vec3(x, y, z);

        std::cout << old_grid.size() << "    " << grid.size() << std::endl;
    }

    void print()
    {
        int count = data.size();

        std::cout << count << std::endl;

        for (auto itter : grid) {
            std::cout << *itter << " ";
        }

        std::cout << std::endl;

        // std::cout << std::string(data.begin(), data.end()) << std::endl;
    }

    int axis_size(int axis = 0)
    {
        int size;

        switch (axis) {
        case 0:
            size = grid_size.x;
            break;
        case 1:
            size = grid_size.y;
            break;
        case 2:
            size = grid_size.z;
            break;
        }

        return size;
    }

private:
    std::vector<T*> grid;
    std::vector<T> data;
    glm::vec3 grid_size;

    // Origin of the space
    glm::vec3 origin;
    // AUV transform matrix
    glm::mat4 transform = glm::mat4(1.0f);
};

#endif