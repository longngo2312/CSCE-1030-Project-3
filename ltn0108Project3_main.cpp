#include "ltn0108Project3_header.h"

int main() {
    Menu choice;
    int userChoice;
    do {
        cout << "\n==== Student Records Menu ====\n";
        cout << "1. Add a new student record\n";
        cout << "2. Remove an existing student record\n";
        cout << "3. Display all records\n";
        cout << "4. Search for a student record by ID\n";
        cout << "5. Export results to disk file\n";
        cout << "6. Quit\n";
        cout << "Enter your choice: ";
        cin >> userChoice;

        // Validate input
        while (cin.fail() || userChoice < 1 || userChoice > 6) {
            cin.clear();
            cin.ignore(10000);
            cout << "Invalid input. Please enter a number between 1 and 6: ";
            cin >> userChoice;
        }

        choice = static_cast<Menu>(userChoice);

        switch (choice) {
            case Add:
                addStudent();
                break;
            case Remove: {
                int id;
                cout << "Enter student ID to remove: ";
                cin >> id;
                removeStudent(id);
                break;
            }
            case Display:
                display();
                break;
            case Search: {
                int id;
                cout << "Enter student ID to search: ";
                cin >> id;
                search(id);
                break;
            }
            case Results:
                exportResults();
                break;
            case Quit:
                cout << "Exiting program. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice, try again.\n";
        }

    } while (choice != Quit);

    return 0;
}
