
import java.util.Scanner;

public class test {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) { // automatically closes the interface scanner after the block completes or returns in an error
            int numOfObjects = scanner.nextInt();
            UnionFind unionFind = new UnionFind(numOfObjects);

            while (scanner.hasNextLine()) {
                int firstNode = scanner.nextInt();
                int secondNode = scanner.nextInt();

                if (!unionFind.union(firstNode, secondNode)) {
                    System.err.println("Invalid Nodes " + firstNode + " and " + secondNode + ". Must be in the range 0 to " + (numOfObjects - 1));
                    return;
                }
            }

            System.out.println(unionFind.connected(12, 34));
        }
    }
}
