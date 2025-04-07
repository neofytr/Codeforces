
import java.util.Scanner;

class quickUnion {

    private final int arr[];
    private final int size[];
    private int components;
    private final int numOfObjects;

    public quickUnion(int numOfObjects) {
        this.numOfObjects = numOfObjects;
        arr = new int[numOfObjects];
        size = new int[numOfObjects];
        components = numOfObjects;
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

        if (firstRoot == secondRoot) {
            return true;
        }

        if (size[firstRoot] > size[secondRoot]) {
            arr[secondRoot] = firstRoot;
            size[firstRoot] += size[secondRoot];
        } else {
            arr[firstRoot] = secondRoot;
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

}

public class socialNetwork {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            int numOfObjects = scanner.nextInt();
            int numOfTimestamps = scanner.nextInt();

            quickUnion friendships = new quickUnion(numOfObjects);

            int firstNode, secondNode;

            for (int index = 1; index <= numOfTimestamps; index++) {
                firstNode = scanner.nextInt();
                secondNode = scanner.nextInt();

                friendships.union(firstNode, secondNode);

                if (friendships.isFullyConnected()) {
                    System.out.println("fully connected at timestamp: " + index);
                    break;
                }
            }
        }
    }
}
