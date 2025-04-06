package main

import (
	"errors"
	"fmt"
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

func (graph *graph_t) pathExists(firstNode, secondNode int) (bool, error) {
	if graph == nil {
		return false, errors.New("ERROR: the graph instance is uninitialized")
	}

	first, ok := graph.nodes[firstNode]
	second, yes := graph.nodes[secondNode]

	if !ok && !yes {
		return false, nil
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
	graph := createGraph()
	graph.addConnection(1, 3)
	graph.addConnection(1, 2)
	graph.addConnection(2, 3)
	graph.print()
}
