
import java.awt.Color;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Scanner;
import java.util.Set;
import javax.imageio.ImageIO;

public class LineIntersectionCounter {

    // Threshold for edge detection
    private static final int EDGE_THRESHOLD = 50;
    // Threshold for line merging
    private static final double LINE_MERGE_THRESHOLD = 5.0;
    // Distance to determine if a point is on an axis
    private static final int AXIS_THRESHOLD = 5;

    public static void main(String[] args) {
        try {
            // Read from standard input
            Scanner scanner = new Scanner(System.in);
            String filename = scanner.nextLine();
            scanner.close();

            // Load the image
            File file = new File(filename);
            BufferedImage image = ImageIO.read(file);

            // Process the image
            int intersectionCount = countIntersections(image);

            // Output the result
            System.out.println(intersectionCount);
        } catch (IOException e) {
            System.err.println("Error reading image: " + e.getMessage());
            e.printStackTrace();
        }
    }

    // Main method to count intersections
    private static int countIntersections(BufferedImage image) {
        // Step 1: Detect lines in the image
        List<Line> lines = detectLines(image);

        // Step 2: Find and count intersections
        Set<Point> intersections = findIntersections(lines);

        // Step 3: Filter out intersections with axes
        Set<Point> filteredIntersections = filterAxisIntersections(intersections, image);

        return filteredIntersections.size();
    }

    // Detect lines in the image using Hough transform-like approach
    private static List<Line> detectLines(BufferedImage image) {
        int width = image.getWidth();
        int height = image.getHeight();

        // Step 1: Edge detection (simple threshold-based)
        List<Point> edgePoints = new ArrayList<>();

        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                Color color = new Color(image.getRGB(x, y));
                int brightness = (color.getRed() + color.getGreen() + color.getBlue()) / 3;

                // If the pixel is dark enough (part of a line)
                if (brightness < EDGE_THRESHOLD) {
                    edgePoints.add(new Point(x, y));
                }
            }
        }

        // Step 2: Find axes (assume axes are horizontal and vertical lines near edges)
        Line xAxis = findXAxis(image);
        Line yAxis = findYAxis(image);

        // Step 3: Group edge points into lines (using RANSAC-like approach)
        List<Line> allLines = fitLinesToPoints(edgePoints);

        // Add axes to the list of lines
        allLines.add(xAxis);
        allLines.add(yAxis);

        return allLines;
    }

    // Find the horizontal x-axis
    private static Line findXAxis(BufferedImage image) {
        int width = image.getWidth();
        int height = image.getHeight();
        int middleHeight = height / 2;

        // Start from the middle and search for a horizontal dark line
        for (int y = middleHeight; y < height - 10; y++) {
            int darkPixelCount = 0;

            for (int x = 0; x < width; x++) {
                Color color = new Color(image.getRGB(x, y));
                int brightness = (color.getRed() + color.getGreen() + color.getBlue()) / 3;

                if (brightness < EDGE_THRESHOLD) {
                    darkPixelCount++;
                }
            }

            // If we found a horizontal line with enough dark pixels
            if (darkPixelCount > width / 3) {
                return new Line(0, y, width - 1, y);
            }
        }

        // If no clear axis is found, assume it's at the bottom
        return new Line(0, height - 1, width - 1, height - 1);
    }

    // Find the vertical y-axis
    private static Line findYAxis(BufferedImage image) {
        int width = image.getWidth();
        int height = image.getHeight();
        int middleWidth = width / 2;

        // Start from the middle and search for a vertical dark line
        for (int x = 0; x < middleWidth; x++) {
            int darkPixelCount = 0;

            for (int y = 0; y < height; y++) {
                Color color = new Color(image.getRGB(x, y));
                int brightness = (color.getRed() + color.getGreen() + color.getBlue()) / 3;

                if (brightness < EDGE_THRESHOLD) {
                    darkPixelCount++;
                }
            }

            // If we found a vertical line with enough dark pixels
            if (darkPixelCount > height / 3) {
                return new Line(x, 0, x, height - 1);
            }
        }

        // If no clear axis is found, assume it's at the left
        return new Line(0, 0, 0, height - 1);
    }

    // Fit lines to the edge points
    private static List<Line> fitLinesToPoints(List<Point> points) {
        List<Line> lines = new ArrayList<>();
        List<Point> remainingPoints = new ArrayList<>(points);

        // Continue until most points are assigned to lines
        while (remainingPoints.size() > points.size() * 0.1) {
            // If too few points remain, stop
            if (remainingPoints.size() < 10) {
                break;
            }

            // Try to fit a line with the remaining points
            Line bestLine = null;
            List<Point> bestInliers = new ArrayList<>();

            // Perform multiple iterations to find the best line
            for (int iter = 0; iter < 100; iter++) {
                // Randomly select two points
                int idx1 = (int) (Math.random() * remainingPoints.size());
                int idx2 = (int) (Math.random() * remainingPoints.size());

                // Make sure the points are different
                if (idx1 == idx2) {
                    continue;
                }

                Point p1 = remainingPoints.get(idx1);
                Point p2 = remainingPoints.get(idx2);

                // Create a line from these two points
                Line line = new Line(p1.x, p1.y, p2.x, p2.y);

                // Count inliers (points close to this line)
                List<Point> inliers = new ArrayList<>();
                for (Point p : remainingPoints) {
                    double distance = line.distanceToPoint(p);
                    if (distance < LINE_MERGE_THRESHOLD) {
                        inliers.add(p);
                    }
                }

                // Update the best line if this one has more inliers
                if (inliers.size() > bestInliers.size()) {
                    bestLine = line;
                    bestInliers = inliers;
                }
            }

            // If we found a good line with enough inliers
            if (bestLine != null && bestInliers.size() > 10) {
                // Refine the line by fitting to all inliers
                bestLine = fitLineToPoints(bestInliers);
                lines.add(bestLine);

                // Remove the inliers from the remaining points
                remainingPoints.removeAll(bestInliers);
            } else {
                // If we can't find a good line, exit
                break;
            }
        }

        return lines;
    }

    // Fit a line to a set of points using least squares
    private static Line fitLineToPoints(List<Point> points) {
        // Use least squares to fit a line to the points
        double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;
        int n = points.size();

        for (Point p : points) {
            sumX += p.x;
            sumY += p.y;
            sumXY += p.x * p.y;
            sumX2 += p.x * p.x;
        }

        // Check if we have a vertical line
        double xVariance = sumX2 / n - (sumX / n) * (sumX / n);
        if (xVariance < 1e-6) {
            // Vertical line case
            int avgX = (int) (sumX / n);
            return new Line(avgX, 0, avgX, 511);
        }

        // Calculate slope and intercept
        double slope = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
        double intercept = (sumY - slope * sumX) / n;

        // Create a line that spans the image
        int x1 = 0;
        int y1 = (int) (intercept);
        int x2 = 511;
        int y2 = (int) (slope * 511 + intercept);

        // Make sure y values are within image bounds
        y1 = Math.max(0, Math.min(511, y1));
        y2 = Math.max(0, Math.min(511, y2));

        return new Line(x1, y1, x2, y2);
    }

    // Find intersections between all pairs of lines
    private static Set<Point> findIntersections(List<Line> lines) {
        Set<Point> intersections = new HashSet<>();

        for (int i = 0; i < lines.size(); i++) {
            for (int j = i + 1; j < lines.size(); j++) {
                Line line1 = lines.get(i);
                Line line2 = lines.get(j);

                Point intersection = line1.findIntersection(line2);
                if (intersection != null) {
                    // Check if the intersection is within the image bounds
                    if (intersection.x >= 0 && intersection.x <= 511
                            && intersection.y >= 0 && intersection.y <= 511) {
                        intersections.add(intersection);
                    }
                }
            }
        }

        return intersections;
    }

    // Filter out intersections with axes
    private static Set<Point> filterAxisIntersections(Set<Point> intersections, BufferedImage image) {
        Set<Point> filtered = new HashSet<>();

        int width = image.getWidth();
        int height = image.getHeight();

        // Find the axes by looking for horizontal and vertical lines
        Line xAxis = findXAxis(image);
        Line yAxis = findYAxis(image);

        for (Point p : intersections) {
            // Check if the point is close to either axis
            double distToXAxis = xAxis.distanceToPoint(p);
            double distToYAxis = yAxis.distanceToPoint(p);

            // If point is far enough from both axes, include it
            if (distToXAxis > AXIS_THRESHOLD && distToYAxis > AXIS_THRESHOLD) {
                filtered.add(p);
            }
        }

        return filtered;
    }

    // Point class for storing x,y coordinates
    static class Point {

        int x, y;

        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public boolean equals(Object obj) {
            if (this == obj) {
                return true;
            }
            if (obj == null || getClass() != obj.getClass()) {
                return false;
            }
            Point point = (Point) obj;
            return x == point.x && y == point.y;
        }

        @Override
        public int hashCode() {
            return 31 * x + y;
        }

        @Override
        public String toString() {
            return "(" + x + "," + y + ")";
        }
    }

    // Line class for storing and manipulating line segments
    static class Line {

        int x1, y1, x2, y2;
        double a, b, c; // Line equation: ax + by + c = 0

        Line(int x1, int y1, int x2, int y2) {
            this.x1 = x1;
            this.y1 = y1;
            this.x2 = x2;
            this.y2 = y2;

            // Calculate line equation coefficients
            this.a = y2 - y1;
            this.b = x1 - x2;
            this.c = x2 * y1 - x1 * y2;

            // Normalize coefficients
            double norm = Math.sqrt(a * a + b * b);
            if (norm > 1e-6) {
                a /= norm;
                b /= norm;
                c /= norm;
            }
        }

        // Find the intersection of this line with another line
        Point findIntersection(Line other) {
            // Check if lines are parallel
            double det = a * other.b - b * other.a;
            if (Math.abs(det) < 1e-6) {
                return null; // Lines are parallel
            }

            // Calculate intersection point
            double x = (b * other.c - c * other.b) / det;
            double y = (c * other.a - a * other.c) / det;

            // Check if the intersection is on both line segments
            if (isPointOnSegment(x, y) && other.isPointOnSegment(x, y)) {
                return new Point((int) Math.round(x), (int) Math.round(y));
            }

            return null;
        }

        // Check if a point is on this line segment
        boolean isPointOnSegment(double x, double y) {
            // Check if point is on the line
            double dist = Math.abs(a * x + b * y + c);
            if (dist > 1e-6) {
                return false;
            }

            // Check if point is within the segment bounds
            double minX = Math.min(x1, x2) - 1;
            double maxX = Math.max(x1, x2) + 1;
            double minY = Math.min(y1, y2) - 1;
            double maxY = Math.max(y1, y2) + 1;

            return x >= minX && x <= maxX && y >= minY && y <= maxY;
        }

        // Calculate the distance from a point to this line
        double distanceToPoint(Point p) {
            return Math.abs(a * p.x + b * p.y + c);
        }

        @Override
        public String toString() {
            return "Line{" + x1 + "," + y1 + " to " + x2 + "," + y2 + "}";
        }
    }
}
