
import java.util.Scanner;

class quickUnion {

    private final int arr[];
    private final int size[];
    private int components;
    private final int max[]; // max[i] is the largest element in the component whose root node is i
    private final int numOfObjects;

    public quickUnion(int numOfObjects) {
        this.numOfObjects = numOfObjects;
        arr = new int[numOfObjects];
        size = new int[numOfObjects];
        this.max = new int[numOfObjects];
        components = numOfObjects;
        for (int index = 0; index < numOfObjects; index++) {
            arr[index] = index; // each element is a tree of single root, with the element at the root
            size[index] = 1;
            this.max[index] = index; // maximum element in the component containing index
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

        if (firstRoot == secondRoot) {
            return true;
        }

        int newMax = Math.max(max[firstRoot], max[secondRoot]);

        if (size[firstRoot] > size[secondRoot]) {
            arr[secondRoot] = firstRoot;
            max[firstRoot] = newMax;
            size[firstRoot] += size[secondRoot];
        } else {
            arr[firstRoot] = secondRoot;
            max[secondRoot] = newMax;
            size[secondRoot] += size[firstRoot];
        }

        components--; // we connected two unconnected component sets; reduce the number of components by 1

        return true;
    }

    public boolean connected(int firstNode, int secondNode) {
        return getRoot(firstNode) == getRoot(secondNode);
    }

    public boolean isFullyConnected() {
        return components == 1;
    }

    public int getMax(int node) {
        return max[getRoot(node)];
    }

}

public class canonical {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            int numOfObjects = scanner.nextInt();

            quickUnion friendships = new quickUnion(numOfObjects);

            int firstNode, secondNode;

            while (scanner.hasNextLine()) {
                firstNode = scanner.nextInt();
                secondNode = scanner.nextInt();

                friendships.union(firstNode, secondNode);
            }
        }
    }
}
