#include <bits/stdc++.h>

// Cast of characters
// 1. Programmer needs to develop a working solution
// 2. Client wants to solve problem efficiently
// 3. Theoretician wants to understand
// 4. Basic blocking and tackling is sometimes necessary
// A student might play any or all of these roles someday

// Reasons to analyze algorithms
// 1. Predict performance
// 2. Compare algorithms
// 3. Provide guarantees
// 4. Understand theoretical basis
// Primary practical reason -> avoid performance bugs
// Client gets poor performance because programmer did not understand performance characteristics

// Scientific Method applied to Analysis to Algorithms
// A framework for predicting performance and comparing algorithms
// Scientific Method
// 1. Observe some feature of the natural world
// 2. Hypothesize a model that is consistent with the observations
// 3. Predict events using the hypothesis
// 4. Verify the predictions by making further observations
// 5. Validate by repeating until the hypothesis and observations agree

// Principles
// 1. Experiments must be reproducible
// 2. Hypotheses must be falsifiable

// Feature of the natural world we're studying is the computer itself

// Mathematical Models for running time
// Total running time -> sum of cost * frequency for all operations
// 1. Need to analyze program to determine set of operations
// 2. Cost depends on machine, compiler.
// 3. Frequency depends on algorithm, input data
// In principle, accurate mathematical models are available

// Simplification 1: cost model
// Use some basic operation as a proxy for running time
// This operation should be the one for which cost * frequency is the highest

// Simplification 2: tilde notation
// Estimate running time (or memory) as a function of input size n (using the cost model)
// Ignore lower order terms
// - when N is large, these terms are negligible
// - when N is small, we don't care
// Technical definition -> f(n) ~ g(n) iff lim(n->inf) (f(n)/g(n)) = 1

// Bottom line -> use cost model and tilde notation to simplify counts

// Estimating a discrete sum (for n -> inf)
// Replace the sum with an integral, and use calculus
// 1 + 2 + 3 + ... + n ~ integral(1, n) of xdx ~ n^2
// 1 + 1 / 2 + 1 / 3 + ... + 1 / n ~ integral(1, n) of (dx/x) ~ log(n)

// In principle, accurate mathematical models are available
// In practice
// 1. Formulas can be complicated
// 2. Advanced mathematics might be required
// 3. Exact models best left for experts

// Bottom Line -> we use approximate models in this course

// Types of analyses
// 1. Best Case -> Lower bound on cost
// - Determined by "easiest" input
// - Provides a goal for all inputs

// 2. Worst Case -> Upper bound on cost
// - Determined by "most difficult" input
// - Provides a guarantee for all inputs

// 3. Average Case -> Expected cost for random input
// - Need a model for "random" input
// - Provides a way to predict performance