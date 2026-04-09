#include <bits/stdc++.h>

// Function to apply a permutation `p_map` to a string `s_orig`
// `p_map` defines the mapping from new face positions to old face positions.
// Specifically, `s_res[new_pos] = s_orig[p_map[new_pos]]`.
std::string apply_permutation_to_string(const std::string& s_orig, const std::vector<int>& p_map) {
    std::string s_res = s_orig; // Initialize with original string, then copy character by character
    for (int i = 0; i < 6; ++i) {
        s_res[i] = s_orig[p_map[i]];
    }
    return s_res;
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    std::string s;
    std::cin >> s;

    // Define the face indexing for a cube:
    // 0: +X (Right face)
    // 1: -X (Left face)
    // 2: +Y (Top face)
    // 3: -Y (Bottom face)
    // 4: +Z (Front face)
    // 5: -Z (Back face)
    // The input string s[i] corresponds to the color on face i initially.

    // Basic 90-degree clockwise rotations about the axes.
    // Each permutation vector `p_rot` is defined such that if applied to a string `s_old`,
    // `s_new[i] = s_old[p_rot[i]]`. This represents what was on `p_rot[i]` is now on `i`.

    // Rotation about X-axis (+X face towards +Y face, i.e., top rotates to front)
    // (+Y -> +Z, -Y -> -Z, +Z -> -Y, -Z -> +Y)
    // Indices: 2->4, 3->5, 4->3, 5->2. Faces 0,1 (+X,-X) remain.
    std::vector<int> p_x_p90 = {0,1,4,5,3,2};

    // Rotation about Y-axis (+Y face towards +Z face, i.e., front rotates to right)
    // (+X -> +Z, -X -> -Z, +Z -> -X, -Z -> +X)
    // Indices: 0->4, 1->5, 4->1, 5->0. Faces 2,3 (+Y,-Y) remain.
    std::vector<int> p_y_p90 = {4,5,2,3,1,0};

    // Rotation about Z-axis (+Z face towards +X face, i.e., right rotates to top)
    // (+X -> +Y, -X -> -Y, +Y -> -X, -Y -> +X)
    // Indices: 0->2, 1->3, 2->1, 3->0. Faces 4,5 (+Z,-Z) remain.
    std::vector<int> p_z_p90 = {2,3,1,0,4,5};

    // Use BFS to generate all 24 unique rotation permutations by composing the basic rotations.
    // The set `all_perms_set` will store `std::vector<int>` representations of these permutations.
    std::set<std::vector<int>> all_perms_set;
    std::queue<std::vector<int>> q;

    std::vector<int> identity_perm = {0,1,2,3,4,5}; // Identity permutation
    all_perms_set.insert(identity_perm);
    q.push(identity_perm);

    while (!q.empty()) {
        std::vector<int> current_p = q.front();
        q.pop();

        // Try composing current_p with each of the three basic 90-degree rotations
        std::vector<std::vector<int>> rotations_to_apply = {p_x_p90, p_y_p90, p_z_p90};
        
        for (const auto& r_op : rotations_to_apply) {
            std::vector<int> next_p(6);
            // Composition: new_perm[i] = current_perm[r_op[i]]
            // This means apply r_op first, then current_p.
            for (int idx = 0; idx < 6; ++idx) {
                next_p[idx] = current_p[r_op[idx]];
            }
            if (all_perms_set.find(next_p) == all_perms_set.end()) {
                all_perms_set.insert(next_p);
                q.push(next_p);
            }
        }
    }
    
    // Convert the set of permutations to a vector for easier iteration
    std::vector<std::vector<int>> all_permutations_of_faces(all_perms_set.begin(), all_perms_set.end());

    // This set will store the lexicographically smallest (canonical) string representation
    // for each unique cube coloring.
    std::set<std::string> unique_cube_colorings;

    // To handle indistinguishable gems of the same color, we sort the input string.
    // Then, `std::next_permutation` will generate all unique permutations of this multiset.
    std::sort(s.begin(), s.end());

    do {
        std::string current_coloring = s; // The current arrangement of colors on fixed faces
        std::string canonical_form = "~"; // Initialize with a lexicographically large string

        // For each arrangement, apply all 24 rotations and find the lexicographically smallest string
        // This smallest string is the canonical representation for this specific cube coloring type.
        for (const auto& p_map : all_permutations_of_faces) {
            std::string rotated_config = apply_permutation_to_string(current_coloring, p_map);
            canonical_form = std::min(canonical_form, rotated_config);
        }
        unique_cube_colorings.insert(canonical_form); // Add the canonical form to the set
        
    } while (std::next_permutation(s.begin(), s.end())); // Iterate through all unique permutations of the input colors

    // The size of the set is the number of distinct ways to decorate the box.
    std::cout << unique_cube_colorings.size() << std::endl;

    return 0;
}