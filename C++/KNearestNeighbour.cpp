//
// Created by Daniel Hametner on 25.01.2021.
//

// system includes
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <iostream>

// own includes
#include "KNearestNeighbour.h"
#include "string_util.h"

/**
 * In this constructor, a pointer to a float array is
 * passed which is then classified, the dimension in which
 * the KNN works and a file name in which the training data
 * is located is passed.
 *
 * @param p_toClassify is a pointer to a float array to be classified
 * @param k is the k of the KNN (how many results are taken into account)
 * @param dimension is the dimension in which the KNN works
 * @param fileName is the file name where the training data is located
 */
KNearestNeighbour::KNearestNeighbour(float *p_toClassify, int dimension, int k, const string &fileName) {
    this->p_toClassify = p_toClassify;
    this->dimension = dimension;
    this->k = k;

    read_iris_data(fileName);
}

/**
 * This method frees the allocated space in this class.
 */
KNearestNeighbour::~KNearestNeighbour() {
    delete[] p_toClassify;

    for (ClassifiedPoint *point : points)
        delete point;

    for (ClassifiedDistance *distance : distances)
        delete distance;
}

/**
 * This method converts the current read line from
 * the trainings data CSV into an iris point.
 *
 * @param inVal is the current read line
 * @return a ClassifiedPoint pointer with the
 *         information in the current line
 */
ClassifiedPoint *KNearestNeighbour::to_iris_point(const string &inVal) const {
    std::vector<string> tokens = split_str(inVal, ",");

    if (tokens.size() != 5)
        return nullptr;
    ClassifiedPoint *p_point = new ClassifiedPoint;

    p_point->points = new float[dimension];
    for (int i = 0; i < dimension; i++)
        p_point->points[i] = std::stof(tokens.at(i));

    p_point->iris_type = get_iris_type(std::stoi(tokens.at(4)));
    return p_point;
}

/**
 * This method compares two ClassifiedDistances and
 * return a boolean if the first value is greater than
 * the second one.
 *
 * @param dist1 is the first value to be compared
 * @param dist2 is the second value to be compared
 * @return a boolean if the first distance
 *         is greater than the second
 */
bool KNearestNeighbour::compare_distance(const ClassifiedDistance *dist1, const ClassifiedDistance *dist2) {
    return dist1->distance < dist2->distance;
}

/**
 * This method reads in the trainings data within the
 * given file is located to perform the KNN.
 *
 * @param fileName is the file name where the training data
 *        is located
 */
void KNearestNeighbour::read_iris_data(const string &fileName) {
    std::ifstream file(fileName);
    string line;

    std::getline(file, line);
    while (std::getline(file, line)) {
        ClassifiedPoint *p_point = to_iris_point(line);

        if (!file.eof() && p_point != nullptr)
            points.push_back(to_iris_point(line));
    }
    file.close();
}

/**
 * This method calculates the euclidean distance between a point
 * and the point to be classified in the given dimension.
 *
 * Calculating the Euclidean-Distance:
 *  ((p1_1 - p2_1)^2 + (p1_2 - p2_2)^2 + ... + (p1_x - p2_x)^2))^1/2
 *
 * @param point is the read in point od the trainings data CSV
 * @return the calculated euclidean distance between the two points
 */
float KNearestNeighbour::eucl_distance(float *point) {
    float tempDist = 0.0f;

    for (int i = 0; i < dimension; i++) {
        tempDist += std::pow(point[i] - p_toClassify[i], 2);
    }
    return std::sqrt(tempDist);
}

/**
 * This method classifies all points within the training data CSV
 * and calculates the distance between them to sort them later and
 * evaluate the classified point.
 */
void KNearestNeighbour::classify_points() {
    for (ClassifiedPoint *point : points) {
        ClassifiedDistance *p_distance = new ClassifiedDistance;
        p_distance->iris_type = point->iris_type;
        p_distance->distance = eucl_distance(point->points);

        distances.push_back(p_distance);
    }
    std::sort(distances.begin(), distances.end(), compare_distance);
}

/**
 * This method outputs both the calculated distances with the correct
 * classification and the percentage of occurrences of the classification.
 */
void KNearestNeighbour::print_results() {
    if (points.empty() || distances.empty()) {
        std::cout << "Points and Distances are empty!" << endl;
        return;
    }
    string result = "\0";

    for (int i = 0; i < k; i++) {
        result += "Result(" + std::to_string(i + 1) + "): ";
        result += std::to_string(distances.at(i)->distance) + " ";
        result += get_iris_name(distances.at(i)->iris_type);
        result += "\n";
    }
    std::cout << result << std::endl;

    float iris_setosa = 0.0f;
    float iris_versicolor = 0.0f;
    float iris_virginica = 0.0f;

    for (int i = 0; i < k; i++) {
        if (distances.at(i)->iris_type == IRIS_SETOSA)
            iris_setosa += static_cast<float>(1.0f / k);
        else if (distances.at(i)->iris_type == IRIS_VERSICOLOR)
            iris_versicolor += static_cast<float>(1.0f / k);
        else if (distances.at(i)->iris_type == IRIS_VIRGINICA)
            iris_virginica += static_cast<float>(1.0f / k);
    }
    result = "The classified point is too: \n";

    result += std::to_string(iris_setosa) + " ";
    result += get_iris_name(IRIS_SETOSA);
    result += ".\n";
    result += std::to_string(iris_versicolor) + " ";
    result += get_iris_name(IRIS_VERSICOLOR);
    result += ".\n";
    result += std::to_string(iris_virginica) + " ";
    result += get_iris_name(IRIS_VIRGINICA);
    result += ".";

    std::cout << result << std::endl;
}
