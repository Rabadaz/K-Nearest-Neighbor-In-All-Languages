package com.daham;

/**
 * This enum contains all classifications for this KNN example.
 */
public enum IrisType {
    IRIS_SETOSA("iris setosa"),          // Class 0
    IRIS_VERSICOLOR("iris versicolor"),  // Class 1
    IRIS_VIRGINICA("iris virginica"),    // Class 2
    NOT_AVAILABLE("NOT AVAILABLE");      // No class

    protected String name;

    IrisType(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }

    /**
     * This method returns the correct iris classification
     * for the given number.
     *
     * @param num is a numeric value between 0, 1 and 2
     * @return the iris dataset classification
     */
    public static IrisType getIrisType(int num){
        return switch (num) {
            case 0 -> IRIS_SETOSA;
            case 1 -> IRIS_VERSICOLOR;
            case 2 -> IRIS_VIRGINICA;
            default -> NOT_AVAILABLE;
        };
    }
}
