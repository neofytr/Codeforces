
public class UnionFind {

    int[] arr;

    UnionFind(int numOfObjects) {
        arr = new int[numOfObjects];
        for (int i = 0; i < numOfObjects; i++) {
            arr[i] = -1;
        }
    }

    boolean union(int nodeOne, int nodeTwo) {
        int size = arr.length;
        if (nodeOne >= size || nodeTwo >= size) {
            return false;
        }

        int valOne = arr[nodeOne];
        int valTwo = arr[nodeTwo];

        if (valOne == -1 && valTwo != -1) {
            arr[nodeOne] = valTwo;
        } else if (valTwo == -1 && valOne != -1) {
            arr[nodeTwo] = valOne;
        } else if (valOne == -1 && valTwo == -1) {
            arr[nodeOne] = nodeOne;
            arr[nodeTwo] = nodeOne;
        } else {
            for (int index = 0; index < size; index++) {
                if (arr[index] == valTwo) {
                    arr[index] = valOne;
                }
            }
        }

        return true;
    }

    boolean connected(int nodeOne, int nodeTwo) {
        return arr[nodeOne] == arr[nodeTwo] && arr[nodeOne] != -1;
    }
}
