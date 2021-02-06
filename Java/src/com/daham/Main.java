package com.daham;

public class Main {

    public static void main(String[] args) {
        int dimension = 4;
        int k = 3;

        float[] toClassify = {5.7f, 3.0f, 5.2f, 1.6f};

        System.out.println("#######################################");
        System.out.println("## KNearestNeighbour Java 15 example ##");
        System.out.println("#######################################");
        System.out.println();

        var kNearestNeighbour =
                new KNearestNeighbour(toClassify, dimension, k, "./src/com/daham/iris_flower_dataset.csv");
        kNearestNeighbour.classifyPoints();
        kNearestNeighbour.printResults();
    }
}
