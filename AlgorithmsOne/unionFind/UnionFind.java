
import java.util.ArrayList;

public class UnionFind {

    ArrayList<Integer> arr;

    UnionFind(int numOfObjects) {
        arr = new ArrayList<>(numOfObjects);
        for (int i = 0; i < numOfObjects; i++) {
            arr.add(-1);
        }
    }

    boolean union(int nodeOne, int nodeTwo) {
        int size = arr.size();
        if (nodeOne >= size || nodeTwo >= size) {
            return false;
        }

        int valOne = arr.get(nodeOne);
        int valTwo = arr.get(nodeTwo);

        if (valOne == -1 && valTwo != -1) {
            arr.set(nodeOne, valTwo);
        } else if (valTwo == -1 && valOne != -1) {
            arr.set(nodeTwo, valOne);
        } else {
            for (int index = 0; index < size; index++) {
                if (arr.get(index) == valTwo) {
                    arr.set(index, valOne);
                }
            }
        }

        return true;
    }
}
