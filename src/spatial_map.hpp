#ifndef SPATIAL_MAP_HPP
#define SPATIAL_MAP_HPP

#include <Eigen/Dense>
#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class SpatialMap {
public:
    SpatialMap(int x = 4, int y = 4, int z = 4)
    {
        T default_value;
        data.push_back(default_value);

        layout_size(0) = x;
        layout_size(1) = y;
        layout_size(2) = z;

        origin << 0, 0, 0;

        layout.resize(x * y * z);

        print();

        for (T* elem : layout) {
            elem = &default_value;
        }

        print();
    };

    ~SpatialMap() {};

    void set(int x, int y, int z, T* value)
    {
        layout[x + (y * layout_size.x()) + (z * layout_size.x() * layout_size.y())] = value;
    }

    T* get(int x, int y, int z)
    {
        return layout[x + (y * layout_size.x()) + (z * layout_size.x() * layout_size.y())];
    }

    void resize(int x, int y, int z)
    {
        std::vector<T*> old_layout = layout;

        // int* new_data = new int[x * y * z];

        // to do copy contents of data into new_data

        layout.resize(x * y * z);

        layout_size(0) = x;
        layout_size(1) = y;
        layout_size(2) = z;

        std::cout << old_layout.size() << "    " << layout.size() << std::endl;
    }

    int flat_size()
    {
        return layout_size.x() * layout_size.y() * layout_size.z();
    }

    int size(int axis)
    {
        return layout_size(axis);
    }

    int data_size()
    {
        return data.size();
    }

    void print()
    {
        int count = flat_size();

        std::cout << count << std::endl;

        for (std::vector<T*>::iterator it = layout.begin(); it != layout.end(); ++it) {
            std::cout << *it << " ";
        }

        std::cout << std::endl;

        // std::cout << std::string(data.begin(), data.end()) << std::endl;
    }

private:
    Eigen::Vector3i layout_size;
    Eigen::Vector3i origin;

    std::vector<T> data;
    std::vector<T*> layout;
};

#endif