#include "ltn0108Project3_header.h"

void addStudent() {
    Student s;
    string lastName;
    string firstName;
    cout << "Enter student first name: ";
    cin >> firstName;
    cout << "Enter the student's last name: ";
    cin >> lastName;

    cout << "Enter student ID: ";
    cin >> s.studentID;

    cout << "Enter number of tests taken: ";
    cin >> s.numTests;

    // Validate number of tests
    while (s.numTests <= 0) {
        cout << "Number of tests must be greater than 0. Enter again: ";
        cin >> s.numTests;
    }

    s.testScores = new int[s.numTests];

    for (int i = 0; i < s.numTests; ++i) {
        cout << "Enter score for test " << i + 1 << ": ";
        cin >> s.testScores[i];

        // Validate test scores
        while (s.testScores[i] < 0) {
            cout << "Test score must be non-negative. Enter again: ";
            cin >> s.testScores[i];
        }
    }

    ofstream outFile("student.dat", ios::app);
    if (!outFile.is_open()) {
        cout << "Error opening student.dat file.\n";
        delete[] s.testScores;
        return;
    }
    outFile << endl << lastName <<","<< firstName << ","<< s.studentID <<","<<s.numTests<<",";
    for (int i = 0; i < s.numTests; ++i)
        outFile << s.testScores[i] << ",";
    outFile.close();
    delete[] s.testScores;

    cout << "Student added successfully!" << endl;
}

void removeStudent(int id) {
    int numStudents = getNumber();
    ifstream inFile("student.dat");
    if (!inFile.is_open()) {
        cout << "Error opening student.dat file.\n";
        return;
    }

    Student* students = new Student[numStudents];
    bool found = false;
    int index = 0;

    while (!inFile.eof() && index < numStudents) {
        string line;
        getline(inFile, line);
        if (line.empty()){ 
            continue; // skip blank lines
        }
        stringstream ss(line);
        string temp;

        // Read first two parts (name)
        getline(ss, temp, ',');
        students[index].name = temp;
        getline(ss, temp, ',');
        students[index].name += "," + temp;

        // Read ID
        getline(ss, temp, ',');
        students[index].studentID = stoi(temp);

        // Read number of tests
        getline(ss, temp, ',');
        students[index].numTests = stoi(temp);

        // Allocate memory for test scores
        students[index].testScores = new int[students[index].numTests];

        // Read all test scores
        for (int j = 0; j < students[index].numTests; ++j) {
            getline(ss, temp, ',');
            students[index].testScores[j] = stoi(temp);
        }

        if (students[index].studentID == id){
            found = true;
        }
        index++;
    }
    inFile.close();

    if (found) {
        ofstream outFile("student.dat");
        if (!outFile.is_open()) {
            cout << "Error opening student.dat file for writing.\n";
            for (int i = 0; i < numStudents; ++i)
                delete[] students[i].testScores;
            delete[] students;
            return;
        }

        for (int i = 0; i < numStudents; ++i) {
            if (students[i].studentID != id) {
                outFile << students[i].name << ",";
                outFile << students[i].studentID << ",";
                outFile << students[i].numTests << ",";
                for (int j = 0; j < students[i].numTests; ++j) {
                    outFile << students[i].testScores[j];
                    if (j != students[i].numTests - 1)
                        outFile << ",";
                }
                outFile << "," << endl;
            }
        }
        cout << "Student removed successfully!\n";
        outFile.close();
    } else {
        cout << "Student ID not found.\n";
    }

    for (int i = 0; i < numStudents; ++i)
        delete[] students[i].testScores;
    delete[] students;
}

void display() {
    int numStudents = getNumber();
    ifstream inFile("student.dat");
    if (!inFile) {
        cout << "Error opening student.dat file.\n";
        return;
    }

    Student* students = new Student[numStudents];
    string line;

    for (int i = 0; i < numStudents; ++i) {
        if (!getline(inFile, line)) {
            cout << "Error reading line.\n";
            break;
        }

        stringstream ss(line);
        string part;

        // Read first and last name (combined into one "name" field)
        getline(ss, part, ','); // Last name
        students[i].name = part;
        getline(ss, part, ','); // First name
        students[i].name += "," + part; // full name: Last, First

        // Now read ID
        getline(ss, part, ',');
        students[i].studentID = stoi(part);

        // Now read number of tests
        getline(ss, part, ',');
        students[i].numTests = stoi(part);

        // Now read each test score
        students[i].testScores = new int[students[i].numTests];
        for (int j = 0; j < students[i].numTests; ++j) {
            if (getline(ss, part, ',')) {
                students[i].testScores[j] = stoi(part);
            } else {
                cout << "Error reading test scores for student " << students[i].name << endl;
                break;
            }
        }
    }
    inFile.close();

    // Print header
    cout << left << setw(30) << "Name" << right << setw(12) << "ID";
    cout << "   Scores" << endl;

    // Print all students
    for (int i = 0; i < numStudents; ++i) {
        cout << left << setw(30) << students[i].name
             << right << setw(12) << students[i].studentID;

        // Print the test scores, ensuring that each score is printed with proper spacing
        for (int j = 0; j < students[i].numTests; ++j) {
            cout << setw(5) << students[i].testScores[j];
        }
        cout << endl;
    }

    // Clean up
    for (int i = 0; i < numStudents; ++i)
        delete[] students[i].testScores;
    delete[] students;
}


void search(int id) {
    ifstream readFile("student.dat");
    if (!readFile.is_open()) {
        cout << "Error opening student.dat file.\n";
        return;
    }

    Student* s = new Student; // Declare a pointer of type Student
    bool found = false;       // Boolean flag to indicate if a match is found

    string line;
    while (getline(readFile, line)) {
        if (line.empty()) {
            continue; // Skip blank lines
        }

        stringstream ss(line);
        string temp;

        // Read first and last name
        getline(ss, temp, ',');
        (*s).name = temp;
        getline(ss, temp, ',');
        (*s).name += "," + temp;

        // Read student ID
        getline(ss, temp, ',');
        (*s).studentID = stoi(temp);

        // Read number of tests
        getline(ss, temp, ',');
        (*s).numTests = stoi(temp);

        // Allocate memory for test scores
        (*s).testScores = new int[(*s).numTests];

        // Read test scores
        for (int i = 0; i < (*s).numTests; ++i) {
            getline(ss, temp, ',');
            (*s).testScores[i] = stoi(temp);
        }

        // Check if the student ID matches
        if ((*s).studentID == id) {
            found = true;

            // Display the matched student's data
            cout << left << setw(30) << (*s).name
                 << setw(15) << (*s).studentID;
            for (int i = 0; i < (*s).numTests; ++i) {
                cout << setw(5) << (*s).testScores[i];
            }
            cout << endl;

            delete[] (*s).testScores; // Free memory for test scores
            break; // Exit the loop as the student is found
        }

        delete[] (*s).testScores; // Free memory for test scores of non-matching students
    }

    if (!found) {
        cout << "Student ID not found.\n";
    }

    delete s; // Free memory for the Student pointer
    readFile.close();
}

int findMinimum(int arr[], int size) {
    if (size <= 0)
        return 0;

    int minVal = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] < minVal)
            minVal = arr[i];
    }
    return minVal;
}

void exportResults() {
    // Open the input file (student.dat) for reading
    ifstream inFile("student.dat");
    if (!inFile.is_open()) {
        cout << "Error opening student.dat file.\n";
        return;
    }

    // Open the output file (averages.dat) for writing
    ofstream outFile("averages.dat");
    if (!outFile.is_open()) {
        cout << "Error opening averages.dat file.\n";
        inFile.close();
        return;
    }

    // Get the number of students
    int numStudents = getNumber();

    // Create a dynamic array of type Student
    Student* students = new Student[numStudents];

    // Read the contents of student.dat into the dynamic array
    for (int i = 0; i < numStudents; ++i) {
        string line;
        getline(inFile, line);
        if (line.empty()) {
            --i; // Skip blank lines
            continue;
        }

        stringstream ss(line);
        string temp;

        // Read name
        getline(ss, temp, ',');
        students[i].name = temp;
        getline(ss, temp, ',');
        students[i].name += "," + temp;

        // Read student ID
        getline(ss, temp, ',');
        students[i].studentID = stoi(temp);

        // Read number of tests
        getline(ss, temp, ',');
        students[i].numTests = stoi(temp);

        // Allocate memory for test scores
        students[i].testScores = new int[students[i].numTests];

        // Read test scores
        for (int j = 0; j < students[i].numTests; ++j) {
            getline(ss, temp, ',');
            students[i].testScores[j] = stoi(temp);
        }
    }

    // Process each student to compute the average and write to averages.dat
    for (int i = 0; i < numStudents; ++i) {
        int sum = 0;

        // Compute the sum of test scores
        for (int j = 0; j < students[i].numTests; ++j) {
            sum += students[i].testScores[j];
        }

        // Find the minimum score and subtract it from the sum
        int minimum = findMinimum(students[i].testScores, students[i].numTests);
        sum -= minimum;

        // Compute the average (drop the minimum score)
        double avg;
        if (students[i].numTests > 1) {
            avg = (double)sum / (students[i].numTests - 1);
        } else {
            avg = 0.0;
        }

        // Write the student ID and average to averages.dat
        outFile << students[i].studentID << " ";
        outFile.setf(ios::fixed);
        outFile.precision(1);
        outFile << avg << endl;
    }

    // Clean up dynamically allocated memory
    for (int i = 0; i < numStudents; ++i) {
        delete[] students[i].testScores;
    }
    delete[] students;

    // Close the files
    inFile.close();
    outFile.close();
}
