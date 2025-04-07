
public class Successor {

    private final int[] arr;
    private final int numOfElements;

    public Successor(int numOfElements) {
        this.numOfElements = numOfElements;
        arr = new int[numOfElements];
        for (int index = 0; index < numOfElements; index++) {
            if (index == numOfElements - 1) {
                arr[index] = index;
            } else {
                arr[index] = index + 1;
            }
        }
    }

    public boolean delete(int element) {
        if (element >= this.numOfElements) {
            return false;
        }

        arr[element] = -1;
        if (element > 0 && element < numOfElements - 1) {
            arr[element - 1] = element + 1;
        } else if (element == numOfElements - 1) {
            if (element - 1 >= 0) {
                arr[element - 1] = element - 1;
            }
        }

        return true;
    }

    public int getSuccessor(int element) {
        if (element >= this.numOfElements) {
            return -1;
        }

        return arr[element];
    }
}
