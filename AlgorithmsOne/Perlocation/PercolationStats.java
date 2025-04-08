

public class PercolationStats {
    private final Percolation percolation;
    private final double mean;
    private final double stdDeviation;
    private final double confidenceHigh;
    private final double confidenceLow;

    public PercolationStats(int n, int trials) {
        int sum = 0;
        for (int index = 0; index < trials; index++) {
            percolation = new Percolation(n);
            
        }
    }

    // sample mean of percolation threshold
    public double mean()

    // sample standard deviation of percolation threshold
    public double stddev()

    // low endpoint of 95% confidence interval
    public double confidenceLo()

    // high endpoint of 95% confidence interval
    public double confidenceHi()

    // test client (see below)
    public static void main(String[] args)
}