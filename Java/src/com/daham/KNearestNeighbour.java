package com.daham;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * In this class, all information and methods for performing a
 * KNN algorithm, including the presentation of the results from
 * the classified data, are implemented in the class.
 */
public class KNearestNeighbour {
    private final List<ClassifiedPoint> POINTS;
    private final List<ClassifiedDistance> DISTANCES;
    protected float[] toClassify;
    protected int dimension;
    protected int k;

    /**
     * In this constructor, a pointer to a float array is
     * passed which is then classified, the dimension in which
     * the KNN works and a file name in which the training data
     * is located is passed.
     *
     * @param toClassify is a pointer to a float array to be classified
     * @param k is the k of the KNN (how many results are taken into account)
     * @param dimension is the dimension in which the KNN works
     * @param fileName is the file name where the training data is located
     */
    public KNearestNeighbour(float[] toClassify, int dimension, int k, String fileName) {
        this.toClassify = toClassify;
        this.dimension = dimension;
        this.k = k;

        POINTS = new ArrayList<>();
        DISTANCES = new ArrayList<>();

        readIrisData(fileName);
    }

    /**
     * This method reads in the trainings data within the
     * given file is located to perform the KNN.
     *
     * @param fileName is the file name where the training data
     *        is located
     */
    private void readIrisData(String fileName) {
        try {
            if (fileName == null || fileName.isEmpty())
                return;
            File file = new File(fileName);

            if (!file.exists())
                return;
            BufferedReader reader = new BufferedReader(new FileReader(file));
            String line;

            reader.readLine();
            while ((line = reader.readLine()) != null) {
                if (line.isEmpty())
                    continue;
                String[] data = line.split(",");

                int num = Integer.parseInt(data[data.length - 1]);
                IrisType irisType = IrisType.getIrisType(num);
                float[] point = new float[dimension];

                for (int i = 0; i < dimension; i++)
                    point[i] = Float.parseFloat(data[i]);

                var cPoint = new ClassifiedPoint(irisType, point);
                POINTS.add(cPoint);
            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * This method calculates the euclidean distance between a point
     * and the point to be classified in the given dimension.
     *
     * Calculating the Euclidean-Distance:
     *  ((p1_1 - p2_1)^2 + (p1_2 - p2_2)^2 + ... + (p1_x - p2_x)^2))^1/2
     *
     * @param point is the read in point of the trainings data CSV
     * @return the calculated euclidean distance between the two points
     */
    private float euclDistance(float[] point) {
        float tempDist = 0.0f;

        for (int i = 0; i < dimension; i++)
            tempDist += Math.pow(point[i] - toClassify[i], 2);
        return (float) Math.sqrt(tempDist);
    }

    /**
     * This method classifies all points within the training data CSV
     * and calculates the distance between them to sort them later and
     * evaluate the classified point.
     */
    public void classifyPoints() {
        for (ClassifiedPoint cPoint : POINTS) {
            float distance = euclDistance(cPoint.getPoint());
            var cDistance = new ClassifiedDistance(cPoint.getIrisType(), distance);

            DISTANCES.add(cDistance);
        }
        Collections.sort(DISTANCES);
    }

    /**
     * This method outputs both the calculated distances with the correct
     * classification and the percentage of occurrences of the classification.
     */
    public void printResults() {
        if (POINTS.isEmpty() || DISTANCES.isEmpty())
            return;
        StringBuilder builder = new StringBuilder();

        for (int i = 0; i < k; i++) {
            builder.append("Result(").append(i + 1).append("): ");
            builder.append(DISTANCES.get(i).getDistance()).append(" ");
            builder.append(DISTANCES.get(i).getIrisType().getName());
            builder.append("\n");
        }
        builder.append("\n");

        float irisSetosa = 0.0f;
        float irisVersicolor = 0.0f;
        float irisVirginica = 0.0f;

        for (int i = 0; i < k; i++) {
            if (DISTANCES.get(i).getIrisType() == IrisType.IRIS_SETOSA)
                irisSetosa += 1.0f / k;
            else if (DISTANCES.get(i).getIrisType() == IrisType.IRIS_VERSICOLOR)
                irisVersicolor += 1.0f / k;
            else if (DISTANCES.get(i).getIrisType() == IrisType.IRIS_VIRGINICA)
                irisVirginica += 1.0f / k;
        }
        builder.append("The classified point is too: \n");
        builder.append(irisSetosa).append(" ");
        builder.append(IrisType.IRIS_SETOSA.getName());
        builder.append(".\n");
        builder.append(irisVersicolor).append(" ");
        builder.append(IrisType.IRIS_VERSICOLOR.getName());
        builder.append(".\n");
        builder.append(irisVirginica).append(" ");
        builder.append(IrisType.IRIS_VIRGINICA.getName()).append(".");

        System.out.println(builder);
    }
}
