
import java.util.Scanner;

public class test {

    public static void main(String[] args) {
        try (Scanner scanner = new Scanner(System.in)) {
            int numOfObjects = scanner.nextInt();
            QuickUnion quickUnion = new QuickUnion(numOfObjects);

            int firstNode, secondNode;

            while (scanner.hasNextLine()) {
                firstNode = scanner.nextInt();
                secondNode = scanner.nextInt();

                if (!quickUnion.union(firstNode, secondNode)) {
                    System.err.println("Invalid Nodes " + firstNode + " and " + secondNode + ". Must be in the range 0 to " + (numOfObjects - 1));
                    return;
                }
            }

            System.out.println(quickUnion.connected(1, 4));
        }

    }
}
