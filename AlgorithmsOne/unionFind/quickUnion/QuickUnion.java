public class QuickUnion {

    private int[] arr;
    private int numOfObjects;

    public QuickUnion(int numOfObjects) {
        arr = new int[numOfObjects];
        this.numOfObjects = numOfObjects;
        for (int index = 0; index < numOfObjects; index++) {
            arr[index] = index; // each element initially is a root
        }
    }

    private int getRoot(int index) {
        while (arr[index] != index) {
            index = arr[index];
        }

        return index;
    }

    public boolean union(int firstNode, int secondNode) {
        if (firstNode >= this.numOfObjects || secondNode >= this.numOfObjects) {
            return false;
        }

        int rootOne = getRoot(firstNode);
        int rootTwo = getRoot(secondNode);

        if (rootOne != rootTwo) {
            arr[rootTwo] = rootOne;
        }

        return true;
    }

    public boolean connected(int firstNode, int secondNode) {
        return getRoot(firstNode) == getRoot(secondNode);
    }
}
