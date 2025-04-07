package main

import (
	"bufio"
	"errors"
	"fmt"
	"math/rand"
	"os"
	"time"
)

const defaultGraphSize = 10

type graph_t struct {
	nodes map[int]*node_t // maps node values to their actual node structure
}

type node_t struct {
	value       int
	connections map[int]*node_t // maps the values which are connected to the current node value to the actual node structure of the former
}

func createGraph() *graph_t {
	nodes := make(map[int]*node_t)
	graph := graph_t{nodes: nodes}
	return &graph
}

func (graph *graph_t) print() {
	if graph == nil {
		fmt.Println("Graph is nil")
		return
	}

	for _, node := range graph.nodes {
		fmt.Printf("Node %d -> ", node.value)
		for neighborID := range node.connections {
			fmt.Printf("%d ", neighborID)
		}
		fmt.Println()
	}
}

func search(graph *graph_t, visited map[int]bool, start, end int, found *bool) {
	if start == end {
		*found = true
	}

	if visited[start] {
		return
	}

	visited[start] = true

	curr_node := graph.nodes[start]
	for neighbour := range curr_node.connections {
		if !visited[neighbour] {
			search(graph, visited, neighbour, end, found)
		}
	}
}

func (graph *graph_t) pathExists(firstNode, secondNode int) (bool, error) {
	if graph == nil {
		return false, errors.New("ERROR: the graph instance is uninitialized")
	}

	_, ok := graph.nodes[firstNode]
	_, yes := graph.nodes[secondNode]

	if !ok || !yes { // if any one of the nodes doesn't exist, we are done, there is no path between them
		return false, nil
	}

	visited := make(map[int]bool)
	for val := range graph.nodes { // initialize the map with all the nodes as false (since we haven't visited any of them yet)
		visited[val] = false
	}

	found := false

	search(graph, visited, firstNode, secondNode, &found)
	if found {
		return true, nil
	}

	return false, nil
}

func (graph *graph_t) load(filePath string) (bool, error) {
	file, err := os.Open(filePath)
	if err != nil {
		return false, err
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		line := scanner.Text()
		var first, second int
		_, err := fmt.Sscanf(line, "%d %d", &first, &second)
		if err != nil {
			return false, fmt.Errorf("invalid line format: %q", line)
		}
		graph.addConnection(first, second)
	}

	if err = scanner.Err(); err != nil {
		return false, err
	}

	return true, nil
}

func (graph *graph_t) addConnection(firstNode, secondNode int) error {
	if graph == nil {
		return errors.New("ERROR: the graph instance is uninitialized")
	}

	first, ok := (*graph).nodes[firstNode]
	if !ok {
		first = &node_t{
			connections: make(map[int]*node_t),
			value:       firstNode,
		}

		(*graph).nodes[firstNode] = first
	}

	second, yes := (*graph).nodes[secondNode]
	if !yes {
		second = &node_t{
			connections: make(map[int]*node_t),
			value:       secondNode,
		}

		(*graph).nodes[secondNode] = second
	}

	first.connections[secondNode] = second
	second.connections[firstNode] = first

	return nil
}

func main() {
	file, err := os.Create("graph.txt")
	if err != nil {
		panic(err)
	}
	defer file.Close()

	rand.Seed(time.Now().UnixNano())
	edges := 1000000
	nodeCount := 500000

	for i := 0; i < edges; i++ {
		a := rand.Intn(nodeCount)
		b := rand.Intn(nodeCount)
		if a == b {
			b = (b + 1) % nodeCount // avoid self-loop
		}
		fmt.Fprintf(file, "%d %d\n", a, b)
	}

	graph := createGraph()
	graph.load("graph.txt")

	found, err := graph.pathExists(2, 800)
	fmt.Println(found)
}
