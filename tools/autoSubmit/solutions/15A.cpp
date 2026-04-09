#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <iomanip> // Not strictly necessary for output, but good for consistent double output precision if debugging

// Using a struct to represent houses for better readability and to precompute edge coordinates.
struct House {
    double x_center;      // x-coordinate of the center of the house
    double side_length;   // side length of the square house
    double left_edge;     // x-coordinate of the left edge (x_center - side_length / 2.0)
    double right_edge;    // x-coordinate of the right edge (x_center + side_length / 2.0)

    // Constructor to initialize house properties and calculate edge coordinates.
    // Inputs are integers as per problem statement, but internal storage is double for precision.
    House(int center_x_int, int side_a_int) 
        : x_center(static_cast<double>(center_x_int)), 
          side_length(static_cast<double>(side_a_int)) {
        
        left_edge = x_center - side_length / 2.0;
        right_edge = x_center + side_length / 2.0;
    }
};

int main() {
    // Enable fast I/O for competitive programming.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;         // Number of existing houses
    double t_new;  // Side length of the new house

    std::cin >> n >> t_new;

    std::vector<House> houses;
    houses.reserve(n); // Pre-allocate memory for efficiency

    // Read details of all existing houses
    for (int i = 0; i < n; ++i) {
        int xi, ai;
        std::cin >> xi >> ai;
        houses.emplace_back(xi, ai); // Construct House objects directly in the vector
    }

    // A std::set is used to store unique x-coordinates of possible new house centers.
    // Using double directly in a set works reliably here because all coordinates 
    // and half-lengths (a_i/2, t/2) will result in values ending in .0 or .5, 
    // which are exactly representable in binary floating-point.
    std::set<double> possible_x_centers;

    // Iterate through each existing house to determine potential positions
    // for the new house that touch it.
    for (int i = 0; i < n; ++i) {
        // Calculate the half-length of the new house.
        double new_house_half_side = t_new / 2.0;

        // --- Candidate 1: New house touches the left edge of existing house 'i' ---
        // The right edge of the new house would be exactly at houses[i].left_edge.
        // The center of this new house would be: houses[i].left_edge - new_house_half_side.
        double x_new_candidate_1 = houses[i].left_edge - new_house_half_side;
        double new_house_left_1 = x_new_candidate_1 - new_house_half_side;  // Leftmost point of new house
        double new_house_right_1 = x_new_candidate_1 + new_house_half_side; // Rightmost point of new house (equals houses[i].left_edge)

        bool overlaps_any_1 = false;
        // Check if this candidate new house position strictly overlaps with any existing house.
        for (int j = 0; j < n; ++j) {
            // Condition for no overlap (touching is allowed):
            // The new house is entirely to the right of house j OR
            // The new house is entirely to the left of house j.
            // i.e., new_house_left_1 >= houses[j].right_edge || new_house_right_1 <= houses[j].left_edge
            // If this condition is FALSE, it means there is a strict overlap.
            if (!(new_house_left_1 >= houses[j].right_edge || new_house_right_1 <= houses[j].left_edge)) {
                overlaps_any_1 = true;
                break; // Found an overlap, this candidate is invalid
            }
        }
        if (!overlaps_any_1) {
            possible_x_centers.insert(x_new_candidate_1); // Add valid center to the set
        }

        // --- Candidate 2: New house touches the right edge of existing house 'i' ---
        // The left edge of the new house would be exactly at houses[i].right_edge.
        // The center of this new house would be: houses[i].right_edge + new_house_half_side.
        double x_new_candidate_2 = houses[i].right_edge + new_house_half_side;
        double new_house_left_2 = x_new_candidate_2 - new_house_half_side;  // Leftmost point of new house (equals houses[i].right_edge)
        double new_house_right_2 = x_new_candidate_2 + new_house_half_side; // Rightmost point of new house

        bool overlaps_any_2 = false;
        // Check for strict overlap with any existing house.
        for (int j = 0; j < n; ++j) {
            if (!(new_house_left_2 >= houses[j].right_edge || new_house_right_2 <= houses[j].left_edge)) {
                overlaps_any_2 = true;
                break; // Found an overlap, this candidate is invalid
            }
        }
        if (!overlaps_any_2) {
            possible_x_centers.insert(x_new_candidate_2); // Add valid center to the set
        }
    }

    // The size of the set gives the total count of unique possible positions.
    std::cout << possible_x_centers.size() << std::endl;

    return 0;
}