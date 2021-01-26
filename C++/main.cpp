//
// Created by Daniel Hametner on 25.01.2021.
//

// system includes
#include <iostream>

// own includes
#include "KNearestNeighbour.h"

using namespace ::std;

int main(int argc, char const *argv[]) {
    int dimension = 4;
    int k = 3;

    float *toClassify = new float[dimension]{5.7f, 3.0f, 5.2f, 1.6f};

    std::cout << "#####################################" << std::endl;
    std::cout << "## KNearestNeighbour CXX17 example ##" << std::endl;
    std::cout << "#####################################" << std::endl;
    std::cout << std::endl;

    KNearestNeighbour *kNearestNeighbour = new KNearestNeighbour(toClassify, dimension, k, "../iris_flower_dataset.csv");
    kNearestNeighbour->classify_points();
    kNearestNeighbour->print_results();

    delete kNearestNeighbour;
    std::exit(EXIT_SUCCESS);
}