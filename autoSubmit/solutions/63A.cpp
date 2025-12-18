#include <bits/stdc++.h>

// Structure to hold crew member data
struct CrewMember {
    std::string name;
    int priority; // Lower number means higher priority to leave
    int original_index; // To break ties by original position (0-based)

    // Constructor for convenience
    CrewMember(std::string n, int p, int idx) : name(n), priority(p), original_index(idx) {}
};

// Custom comparison function for sorting
// Returns true if 'a' should come before 'b' in the evacuation order
bool compareCrewMembers(const CrewMember& a, const CrewMember& b) {
    // Primary sorting key: priority (lower priority number means higher actual priority)
    if (a.priority != b.priority) {
        return a.priority < b.priority;
    }
    // Secondary sorting key (tie-breaker): original index (smaller index leaves first)
    return a.original_index < b.original_index;
}

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<CrewMember> crew;
    crew.reserve(n); // Pre-allocate memory for efficiency

    for (int i = 0; i < n; ++i) {
        std::string name;
        std::string status;
        std::cin >> name >> status;

        int priority_val;
        if (status == "rat") {
            priority_val = 0; // Rats leave first
        } else if (status == "woman" || status == "child") {
            priority_val = 1; // Women and children leave next (same priority)
        } else if (status == "man") {
            priority_val = 2; // Men leave after women and children
        } else if (status == "captain") {
            priority_val = 3; // Captain leaves last
        } 
        // No else case needed, problem guarantees valid statuses

        // Create a CrewMember object and add it to the vector
        // 'i' serves as the 0-based original index in the line
        crew.emplace_back(name, priority_val, i);
    }

    // Sort the vector of crew members using the custom comparison function
    std::sort(crew.begin(), crew.end(), compareCrewMembers);

    // Print the names of the crew members in the determined evacuation order
    for (const auto& member : crew) {
        std::cout << member.name << "\n";
    }

    return 0;
}