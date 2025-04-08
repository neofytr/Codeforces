class quickunion {
    private final int[] parent; // parent[i] contains the parent of the node i
    private final int[] rank; // rank[i] contains the number of elements in the tree rooted at i
    private final int numOfObjects;

    public quickunion(int numOfObjects) {
        parent = new int[numOfObjects];
        rank = new int[numOfObjects];
        this.numOfObjects = numOfObjects;

        for (int index = 0; index < numOfObjects; index++) {
            parent[index] = index; // each element is in it's own component set initially; each component set is represented by a root node for which parent[index] = index
            rank[index] = 0;
        }
    }

    private int getRoot(int node) {
        if (node < 0 || node >= this.numOfObjects) {
            throw new IllegalArgumentException("Invalid index: " + node);
        }

        int initNode = node;
        while(node != parent[node]) {
            node = parent[node];
        }

        // node now contains the root node of node
        // we now do the path compression loop
        int temp;
        while(initNode != parent[initNode] ) {
            temp = parent[initNode];
            parent[initNode] = node; // path compress; change the parent node of all the nodes in the path to from node to the root node to the root node
            initNode = temp;
        }

        return node;
    }

    public void union(int firstNode, int secondNode) { // union of the component set containing firstNode and secondNode
        if (firstNode < 0 || secondNode < 0 || firstNode >= this.numOfObjects || secondNode >= this.numOfObjects) {
            throw new IllegalArgumentException("Invalid node arguments");
        }

        int firstRoot = getRoot(firstNode);
        int secondRoot = getRoot(secondNode);

        if (firstRoot == secondRoot) {
            return; // they are already connected
        }

        int firstRank = rank[firstRoot];
        int secondRank = rank[secondRoot];

        if (firstRank < secondRank) {
            parent[firstRoot] = secondRoot;
            rank[secondRoot] += firstRank;
        } else {
            parent[secondRoot] = firstRoot;
            rank[firstRoot] += secondRank;
        }
    }

    public boolean isConnected(int firstNode, int secondNode) {
        if (firstNode < 0 || secondNode < 0 || firstNode >= this.numOfObjects || secondNode >= this.numOfObjects) {
            throw new IllegalArgumentException("Invalid node arguments");
        }

        return getRoot(firstNode) == getRoot(secondNode);
    }
}

public class Percolation {
    private final int gridSize;
    private final quickunion grid;
    private final boolean[] siteOpen;
    private int numOfOpenSites;
    private final int topVirtualSite;
    private final int bottomVirtualSite;

    public Percolation(int gridSize) {
        if (gridSize <= 0) {
            throw new IllegalArgumentException("Invalid grid size; Must be positive!");
        }

        this.gridSize = gridSize;
        grid = new quickunion(gridSize * gridSize + 2); // + 2 for two virtual nodes

        topVirtualSite = gridSize * gridSize;
        bottomVirtualSite = gridSize * gridSize + 1;

        // all the top row sites are connected to the topVirtualSite
        // and all the bottom row sites are connected to the bottomVirtualSite
        for (int index = 0; index < gridSize; index++) {
            grid.union(topVirtualSite, index);
            grid.union(bottomVirtualSite, gridSize * gridSize - index - 1);
        }

        siteOpen = new boolean[gridSize * gridSize]; // automatically initialized to all false
        numOfOpenSites = 0;
    }

    public boolean isOpen(int row, int column) {
        row--; column--; // coversion to 0-based indexing
        if (row < 0 || row >= gridSize || column < 0 || column >= gridSize) {
            throw new IllegalArgumentException("Invalid row and column arguments");
        }

        int index = row * this.gridSize + column;

        return siteOpen[index];
    }

    public void open(int row, int column) { // row and column are given in 1-based indexing
        row--; column--; // coversion to 0-based indexing
        if (row < 0 || row >= gridSize || column < 0 || column >= gridSize) {
            throw new IllegalArgumentException("Invalid row and column arguments");
        }

        int index = row * this.gridSize + column;

        if (siteOpen[index]) {
            return;
        }

        siteOpen[index] = true;
        numOfOpenSites++;

        if (column - 1 >= 0 && siteOpen[index - 1]) {
            grid.union(index, index - 1);
        }

        if (column + 1 < this.gridSize && siteOpen[index + 1]) {
            grid.union(index, index + 1);
        }

        if (row - 1 >= 0 && siteOpen[index - this.gridSize]) {
            grid.union(index, index - this.gridSize);
        }

        if (row + 1 < this.gridSize && siteOpen[index + this.gridSize]) {
            grid.union(index, index + this.gridSize);
        }
    }

    public int numberOfOpenSites() {
        return this.numOfOpenSites;
    }

    public boolean isFull(int row, int column) {
        row--; column--; // coversion to 0-based indexing
        if (row < 0 || row >= gridSize || column < 0 || column >= gridSize) {
            throw new IllegalArgumentException("Invalid row and column arguments");
        }

        int index = row * this.gridSize + column;

        return grid.isConnected(topVirtualSite, index);
    }

    public boolean percolates() { // does the system percolate
        return grid.isConnected(topVirtualSite, bottomVirtualSite);
    }
}
