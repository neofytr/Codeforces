
import java.util.ArrayList;

public class UnionFind {

    ArrayList<Integer> arr;

    UnionFind(int numOfObjects) {
        arr = new ArrayList<>(numOfObjects);
        for (int i = 0; i < numOfObjects; i++) {
            arr.add(0);
        }
    }
}
