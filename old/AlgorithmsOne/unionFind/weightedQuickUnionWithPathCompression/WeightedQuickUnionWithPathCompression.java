
public class WeightedQuickUnionWithPathCompression {

    private final int[] arr;
    private final int numOfObjects;
    private final int[] size; // size[i] is the size of the tree rooted at i

    public WeightedQuickUnionWithPathCompression(int numOfObjects) {
        arr = new int[numOfObjects];
        size = new int[numOfObjects];
        this.numOfObjects = numOfObjects;
        for (int index = 0; index < numOfObjects; index++) {
            arr[index] = index; // each element initially is a root
            size[index] = 1;
        }
    }

    private int getRoot(int index) {
        int initIndex = index;
        while (arr[index] != index) {
            arr[index] = arr[arr[index]];
            index = arr[index];
        }

        int temp;

        // do path compression
        while (arr[initIndex] != initIndex) {
            temp = arr[initIndex];
            arr[initIndex] = index; // set the parent of the node to the root
            initIndex = temp;
        }

        return index;
    }

    public boolean union(int firstNode, int secondNode) {
        if (firstNode >= this.numOfObjects || secondNode >= this.numOfObjects) {
            return false;
        }

        int rootOne = getRoot(firstNode);
        int rootTwo = getRoot(secondNode);

        if (rootOne == rootTwo) {
            return true;
        }

        // attach the smaller tree to the root of the larger tree; this makes the algorithm significantly faster
        if (size[rootOne] > size[rootTwo]) {
            arr[rootTwo] = rootOne;
            size[rootOne] += size[rootTwo];
        } else {
            arr[rootOne] = rootTwo;
            size[rootTwo] += size[rootOne];
        }

        return true;
    }

    public boolean connected(int firstNode, int secondNode) {
        return getRoot(firstNode) == getRoot(secondNode);
    }
}
