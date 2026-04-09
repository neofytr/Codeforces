
public class union {

    private final int arr[];
    private final int size[];
    private final int numOfObjects;

    public union(int numOfObjects) {
        this.numOfObjects = numOfObjects;
        arr = new int[numOfObjects];
        size = new int[numOfObjects];
        for (int index = 0; index < numOfObjects; index++) {
            arr[index] = index; // each element is a tree of single root, with the element at the root
            size[index] = 1;
        }
    }

    private int getRoot(int index) {
        int initIndex = index;
        while (index != arr[index]) {
            index = arr[index];
        }

        // path compression loop
        int temp;
        while (initIndex != arr[initIndex]) {
            temp = arr[initIndex]; // store the current parent of the current node
            arr[initIndex] = index; // set the parent of the current node to the root

            initIndex = temp;
        }

        return index;
    }

    public boolean union(int firstNode, int secondNode) {
        if (firstNode >= this.numOfObjects || secondNode >= this.numOfObjects) {
            return false;
        }

        int firstRoot = getRoot(firstNode);
        int secondRoot = getRoot(secondNode);

        if (size[firstRoot] > size[secondRoot]) {
            arr[secondRoot] = firstRoot;
            size[firstRoot] += size[secondRoot];
        } else {
            arr[firstRoot] = secondRoot;
            size[secondRoot] += size[firstRoot];
        }

        return true;
    }

    public boolean connected(int firstNode, int secondNode) {
        return getRoot(firstNode) == getRoot(secondNode);
    }

}
