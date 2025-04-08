class quickUnion {
    private final int[] parent; // parent[i] contains the parent of the node i
    private final int[] rank; // rank[i] contains the number of elements in the tree rooted at i
    private final int numOfObjects;

    public quickUnion(int numOfObjects) {
        parent = new int[numOfObjects];
        rank = new int[numOfObjects];
        this.numOfObjects = numOfObjects;

        for (int index = 0; index < numOfObjects; index++) {
            parent[index] = index;
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

    public void union(int firstNode, int secondNode) {
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