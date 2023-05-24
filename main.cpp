#include "hash_table.h"

int main() {
    HashTable users(100);

    // Add Administrator user with password 123
    std::string admin_username = "Administrator";
    std::string admin_password = "123";
    std::hash<std::string> hasher;
    std::string hashed_admin_password = std::to_string(hasher(admin_password));
    users.insert(admin_username, hashed_admin_password);

    bool is_running = true;
    while (is_running) {
        std::cout << "\nChoose an action:\n";
        std::cout << "1 - Register\n";
        std::cout << "2 - Log in\n";
        std::cout << "3 - Exit\n";
        std::string choice;
        std::cin >> choice;

        if (choice == "1") {
            std::cout << "Enter username: ";
            std::string username;
            std::cin >> username;

            std::cout << "Enter password: ";
            std::string password;
            std::cin >> password;

            std::string hashed_password = std::to_string(hasher(password));
            users.insert(username, hashed_password);

            std::cout << "User registered.\n";
        }
        else if (choice == "2") {
            std::cout << "Enter username: ";
            std::string username;
            std::cin >> username;

            std::cout << "Enter password: ";
            std::string password;
            std::cin >> password;

            // Hash the password and check if it matches the stored hash.
            std::string hashed_password = std::to_string(hasher(password));
            if (hashed_password == users.get(username)) {
                std::cout << "Log in successful.\n";

                // If logged in as Administrator, show all users and their passwords
                if (username == admin_username) {
                    std::cout << "Enter 'i' to view user data: ";
                    std::string input;
                    std::cin >> input;
                    if (input == "i") {
                        int count;
                        auto all_entries = users.get_all(count);
                        for (int i = 0; i < count; ++i) {
                            // Output only non-administrator entries
                            if (all_entries[i].first != admin_username) {
                                std::cout << all_entries[i].first << " " << all_entries[i].second << "\n";
                            }
                        }
                        delete[] all_entries; // Free the dynamically allocated array
                    }
                }
            }
            else {
                std::cout << "Login failed. Incorrect username or password.\n";
            }
        }
        else if (choice == "3") {
            std::cout << "Exiting program.\n";
            is_running = false;
        }
        else {
            std::cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
    }

    return 0;
}