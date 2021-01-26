//
// Created by Daniel Hametner on 25.01.2021.
//

#ifndef KNN_K_NEAREST_NEIGHBOUR_H
#define KNN_K_NEAREST_NEIGHBOUR_H

// system includes
#include <vector>
#include <string>

// own includes
#include "IrisType.h"

using namespace ::std;

/**
 * This struct represents a classified point with
 * its associated data.
 */
struct ClassifiedPoint {
    IrisType iris_type;
    float *points;
};

/**
 * This struct represents a classified distance with
 * its associated data.
 */
struct ClassifiedDistance {
    IrisType iris_type;
    double distance;
};

/**
 * In this class, all information and methods for performing a
 * KNN algorithm, including the presentation of the results from
 * the classified data, are implemented in the class.
 */
class KNearestNeighbour {
private:
    float *p_toClassify = nullptr;
    int dimension;
    int k;

    std::vector<ClassifiedPoint *> points;
    std::vector<ClassifiedDistance *> distances;

    static bool compare_distance(const ClassifiedDistance *dist1, const ClassifiedDistance *dist2);

    ClassifiedPoint *to_iris_point(const string &inVal) const;

    void read_iris_data(const string &fileName);

    float eucl_distance(float *point);

public:
    KNearestNeighbour(float *p_toClassify, int dimension, int k, const string &fileName);

    ~KNearestNeighbour();

    void classify_points();

    void print_results();
};

#endif // KNN_K_NEAREST_NEIGHBOUR_H
