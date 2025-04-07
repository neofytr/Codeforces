
public class UnionFind {

    int[] arr;

    UnionFind(int numOfObjects) {
        arr = new int[numOfObjects];
        for (int i = 0; i < numOfObjects; i++) {
            arr[i] = i;
        }
    }

    boolean union(int nodeOne, int nodeTwo) {
        int size = arr.length;
        if (nodeOne >= size || nodeTwo >= size) {
            return false;
        }

        int valOne = arr[nodeOne];
        int valTwo = arr[nodeTwo];

        for (int index = 0; index < size; index++) {
            if (arr[index] == valTwo) {
                arr[index] = valOne;
            }
        }

        return true;
    }

    boolean connected(int nodeOne, int nodeTwo) {
        return arr[nodeOne] == arr[nodeTwo];
    }
}
