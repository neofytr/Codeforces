#include <bits/stdc++.h>

int main() {
    // Enable fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long total_traffic = 0;
    int current_participants_count = 0;
    std::string line;

    // Read commands line by line until end of input
    while (std::getline(std::cin, line)) {
        // According to problem constraints, input lines are valid commands
        // and won't be empty if a command is expected.

        if (line[0] == '+') {
            // Add command: +<name>
            // No traffic generated, just update participant count.
            current_participants_count++;
        } else if (line[0] == '-') {
            // Remove command: -<name>
            // No traffic generated, just update participant count.
            current_participants_count--;
        } else {
            // Send command: <sender_name>:<message_text>
            // Find the position of the colon to separate sender name and message text.
            size_t colon_pos = line.find(':');
            
            // The length of the message text is the total length of the line
            // minus the part before and including the colon.
            // (colon_pos + 1) gives the index of the first character of the message.
            // So, line.length() - (colon_pos + 1) is the length of the message text.
            size_t message_text_length = line.length() - (colon_pos + 1);

            // Traffic is generated only if there are participants in the chat.
            // Even if current_participants_count is 0, message_text_length * 0 will be 0,
            // so an explicit check `if (current_participants_count > 0)` is not strictly
            // necessary but can conceptually clarify the logic.
            total_traffic += (long long)message_text_length * current_participants_count;
        }
    }

    // Print the total calculated outgoing traffic
    std::cout << total_traffic << std::endl;

    return 0;
}