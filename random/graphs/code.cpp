#include <bits/stdc++.h>
using namespace std;

// A undirected (simple) graph G is an ordered pair (V, E) where V is a (non-empty)subset of N (the natural numbers)
// and E is a subset of the set F = {{u, v} such that u, v are in V and u != v}.
// The elements of V are called the vertices of G and each element {u, v} in E
// is called an edge of G and is denoted u-v (or v-u).

// A directed (simple) graph G is an ordered pair (V, E) where V is a (non-empty) subset of N (the natural numbers)
// and E is a subset of the cartesian product V x V.
// The elements of V are called the vertices of G and each element (u, v) in E 
// is called an edge of G and is denoted u->v.

// Let G is an undirected graph
// The degree of a vertex v of G is the number of edges v-u in G
// where u is a vertex of G.
// The sum of degrees of all the vertices of G = 2 * number of edges in G,
// since any edge of G contributes 2 to this sum (one for each of its endpoints). 

// Let G is a directed graph
// The indegree (outdegree) of a vertex v of G is the number of edges u->v (v->u) in G where u is a
// vertex of G.
// The number of edges of G (i.e., |E|) is equal to the sum of outdegrees (or indegrees) of all nodes
// of G.

// DFS visits each node exactly once. Thus, the DFS function is called exactly |V| times (once for each node).
// In a DFS call for node v, some O(1) operations are done along with a loop that iterates deg(v) (or outdegree(v), for
// directed graphs) times, doing O(1)
// operations per iteration.
// Thus, the total running time of DFS is
// Summation(O(1) + O(deg(v)); for all v in V)) = O(|V| + |E|)
// since summation((out)deg(v); for all v in V) = 2 * |E| (or |E| for the directed case)

