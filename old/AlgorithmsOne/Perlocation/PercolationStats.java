import edu.princeton.cs.algs4.StdOut;
import edu.princeton.cs.algs4.StdRandom;
import edu.princeton.cs.algs4.StdStats;

public class PercolationStats {
    private final double trialMean;
    private final double stdDeviation;
    private final double confidenceHigh;
    private final double confidenceLow;

    public PercolationStats(int n, int trials) {
        if (n <= 0 || trials <= 0) {
            throw new IllegalArgumentException("Grid size and trials must be positive");
        }

        double[] fraction = new double[trials];
        for (int index = 0; index < trials; index++) {
            Percolation perc = new Percolation(n); // all sites are initially blocked
            int row, column;
            while(!perc.percolates()) {
                row = StdRandom.uniformInt(n) + 1;
                column = StdRandom.uniformInt(n) + 1;
                if (!perc.isOpen(row, column)) {
                    perc.open(row, column);
                }
            }

            fraction[index] = perc.numberOfOpenSites() / (double)(n * n); // fraction of open sites at the time of percolation
        }

        trialMean = StdStats.mean(fraction); // percolation threshold
        stdDeviation = StdStats.stddev(fraction);
        confidenceLow = trialMean - (1.96 * stdDeviation) / Math.sqrt(trials);
        confidenceHigh = trialMean + (1.96  * stdDeviation) / Math.sqrt(trials);
    }

    public double mean() {
        return this.trialMean;
    }

    public double stddev() {
        return this.stdDeviation;
    }

    public double confidenceLo() {
        return this.confidenceLow;
    }

    public double confidenceHi() {
        return this.confidenceHigh;
    }

    public static void main(String[] args) {
        PercolationStats stats = new PercolationStats(Integer.parseInt(args[0]), Integer.parseInt(args[1]));
        StdOut.printf("mean                    = %f\n", stats.mean());
        StdOut.printf("stddev                  = %f\n", stats.stddev());
        StdOut.printf("95%% confidence interval = [%f, %f]\n", stats.confidenceLo(), stats.confidenceHi());
    }
}