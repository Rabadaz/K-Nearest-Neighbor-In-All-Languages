//
// Created by Daniel Hametner on 25.01.2021.
//

#ifndef KNN_IRIS_TYPE_H
#define KNN_IRIS_TYPE_H

// system includes
#include <string>

using namespace ::std;

/**
 * This enum contains all classifications for this KNN example.
 */
enum IrisType {
    IRIS_SETOSA,      // Class 0
    IRIS_VERSICOLOR,  // Class 1
    IRIS_VIRGINICA,   // Class 2
    NOT_AVAILABLE     // No class
};

/**
 * This method returns the correct iris classification
 * for the given number.
 *
 * @param num is a numeric value between 0, 1 and 2
 * @return the iris dataset classification
 */
static IrisType get_iris_type(int num) {
    switch (num) {
        case 0:
            return IRIS_SETOSA;
        case 1:
            return IRIS_VERSICOLOR;
        case 2:
            return IRIS_VIRGINICA;
        default:
            return NOT_AVAILABLE;
    }
}

/**
 * This method returns the correct iris classification
 * name for the given iris classification.
 *
 * @param iris_type is the provided iris classification
 * @return the iris classification name
 */
static string get_iris_name(IrisType iris_type) {
    switch (iris_type) {
        case IRIS_SETOSA:
            return "iris setosa";
        case IRIS_VERSICOLOR:
            return "iris versicolor";
        case IRIS_VIRGINICA:
            return "iris virginica";
        case NOT_AVAILABLE:
        default:
            return "NOT AVAILABLE";
    }
}

#endif // KNN_IRIS_TYPE_H