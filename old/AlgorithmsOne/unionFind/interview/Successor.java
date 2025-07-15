
import java.util.Scanner;

class quickUnion {

    private final int[] arr;
    private final int numOfElements;

    public quickUnion(int numOfElements) {
        arr = new int[numOfElements + 1]; // the value numOfElements means does not exist; sentinel value
        this.numOfElements = numOfElements;
        for (int index = 0; index <= numOfElements; index++) {
            arr[index] = index;
        }
    }

    private int find(int element) {
        int init = element;
        while (element != arr[element]) {
            element = arr[element];
        }

        // path compression
        int temp;
        while (init != arr[init]) {
            temp = arr[init];
            arr[init] = element; // assign the current node to the root
            init = temp;
        }

        return element;
    }

    public boolean deleteElement(int element) {
        if (element >= this.numOfElements || element < 0) {
            return false;
        }

        arr[element] = find(element + 1);
        return true;
    }

    public int getSuccessor(int element) {
        if (element < 0 || element >= this.numOfElements) {
            return -1;
        }

        int get = find(element);
        if (get == this.numOfElements) {
            return -1;
        }

        return get;
    }
}

public class Successor {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            int numOfElements = scanner.nextInt();
            quickUnion numSet = new quickUnion(numOfElements);

            numSet.deleteElement(4);
            numSet.deleteElement(5);
            numSet.deleteElement(6);

            System.out.println(numSet.getSuccessor(4));
            System.out.println(numSet.getSuccessor(5));
            System.out.println(numSet.getSuccessor(6));
        }
    }
}
