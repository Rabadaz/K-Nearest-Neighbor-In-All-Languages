package com.daham;

/**
 * This struct represents a classified distance with
 * its associated data.
 */
public class ClassifiedDistance implements Comparable<ClassifiedDistance> {
    protected IrisType irisType;
    protected float distance;

    public ClassifiedDistance(IrisType irisType, float distance) {
        this.irisType = irisType;
        this.distance = distance;
    }

    @Override
    public int compareTo(ClassifiedDistance other) {
        return Float.compare(distance, other.distance);
    }

    public IrisType getIrisType() {
        return irisType;
    }

    public float getDistance() {
        return distance;
    }
}
