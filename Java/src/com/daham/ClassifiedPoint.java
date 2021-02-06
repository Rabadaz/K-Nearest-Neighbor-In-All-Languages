package com.daham;

/**
 * This class represents a classified point with
 * its associated data.
 */
public class ClassifiedPoint {
    protected IrisType irisType;
    protected float[] point;

    public ClassifiedPoint(IrisType irisType, float[] point) {
        this.irisType = irisType;
        this.point = point;
    }

    public IrisType getIrisType() {
        return irisType;
    }

    public float[] getPoint() {
        return point;
    }
}
