
import java.util.Random;
import java.util.Scanner;

public class knuthMethod {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Random random = new Random();

        String word, winner = null;
        int count = 0;

        while (scanner.hasNext()) {// until EOF
            word = scanner.next();
            count++;

            if (random.nextDouble() < 1 / count) { // next double gives a number in the range [0,1)
                winner = word;
            }
        }

        if (winner != null) {
            System.out.println("Winner: " + winner);
        } else {
            System.err.println("No input given!");
        }

    }
}
