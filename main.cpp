#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include "Patient.h"
#include "Comparator.h"

using namespace std;

std::vector<std::string> patientInformation;
vector<Patient> patients;
vector<Patient> treatedPatients;

bool debugMode = false;

void toggleDebugMode() {
    debugMode = true;
    cout << "enabled debug mode";
}

// As a sys admin, I want all operations of the system by each user to be logged to a file in normal mode.
// As a sys admin, I want some way to turn on debug mode.
// As a sys admin, I want all operations of the system by each user to be logged to the console in debug mode
void logCommand(const std::string &str) {
    std::fstream log("hospital_system_log.txt", std::ios::app);
    if (debugMode) {
        log << "debug mode\n";
    } else {
        log << "normal mode \n";
    }
    log << str;
    log.close();
    if (debugMode == 1)
        std::cout << "DEBUG: " << str;
}


//As a nurse, I want to add a patient to the system
void addPatient(vector<Patient>& patients) {

    logCommand("[Add Patient Logged] \n");

    std::string input;
    int input2;

    std::string fName;
    std::string mName;
    std::string lName;
    std::string suffix;
    std::vector<std::string> ailments;
    std::string doctor;
    int treated;
    int priority;

    // user first name
    while (true) {
        std::cout << "patient's first name:";
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input\n";
        } else break;
    }
    fName = input;
    patientInformation.push_back(fName);

    // user middle name
    while (true) {
        std::cout << "patient's middle name:";
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input\n";
        } else break;
    }
    mName = input;
    patientInformation.push_back(mName);

    // user last name
    while (true) {
        std::cout << "patient's last name:";
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input\n";
        } else break;
    }
    lName = input;
    patientInformation.push_back(lName);

    // suffix
    while (true) {
        std::cout << "suffix:";
        std::cin >> input;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input\n";
        } else break;
    }
    suffix = input;
    patientInformation.push_back(suffix);

    // number of ailments
    while (true) {
        cout << "number of ailments:";
        cin >> input2;
        if (cin.fail() || input2 <= 0 || input2 > 9) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
        } else break;
    }
    int num = input2;

    // ailments
    for (int i = 1; i <= num; i++) {
        while (true) {
            cout << "ailment " << i << ":";
            cin.clear();
            cin.sync();
            getline(cin, input);
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input\n";
            } else break;
        }
        ailments.push_back(input);
    }

    // doctor
    while (true) {
        cout << "patient's doctor:";
        cin.clear();
        cin.sync();
        getline(cin, input);
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
        } else break;
    }
    doctor = input;
    patientInformation.push_back(doctor);

    // treated
    while (true) {
        cout << "Enter 0 if patient has not yet been treated or 1 if patient has been treated:";
        cin >> input2;
        if (cin.fail() || (input2 != 0 && input2 != 1)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
        } else break;
    }
    treated = input2;

    // user priority
    while (true) {
        cout << "Enter patient's priority (1 - 999):";
        cin >> input2;
        if (cin.fail() || input2 < 1 || input2 > 999) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input\n";
        } else break;
    }
    priority = input2;

    // Create a new Patient object using the default constructor
    Patient newPatient;
    newPatient.setFName(fName);
    newPatient.setMName(mName);
    newPatient.setLName(lName);
    newPatient.setSuffix(suffix);
    newPatient.setAilments(ailments);
    newPatient.setDoctor(doctor);
    newPatient.setTreated(treated);
    newPatient.setPriority(priority);

    // Add new patient to vector of patients
    patients.push_back(newPatient);
}

// As a sys admin, I want to bulk add patients into the system from a file (see patients.txt)
void bulkAdd(const vector<Patient>& patients) {

    logCommand("[Bulk Add Logged] \n");

    for (const Patient& patient : patients) {
        cout << "First Name: " << patient.getFName() << endl;
        cout << "Middle Name: " << patient.getMName() << endl;
        cout << "Last Name: " << patient.getLName() << endl;
        cout << "Suffix: " << patient.getSuffix() << endl;

        vector<string> ailments = patient.getAilments();
        for (size_t i = 0; i < ailments.size(); i++) {
            cout << "Ailment " << i + 1 << ": " << ailments[i] << endl;
        }

        cout << "Doctor: " << patient.getDoctor() << endl;
        cout << "Treated: " << patient.getTreated() << endl;
        cout << "Priority: " << patient.getPriority() << endl;
    }
}

// Comparison function for sorting patients by priority
bool comparePriority(const Patient& p1, const Patient& p2) {

    logCommand("[Compare Priority Logged] \n");

    return p1.getPriority() < p2.getPriority();
}

// As a hospital admin, I want a single command to treat all patients.
void treatPatients(vector<Patient>& patients) {

    logCommand("[Treat Patients Logged] \n");

    // Sort the patients based on their priority
    sort(patients.begin(), patients.end(), comparePriority);

    // Treat patients in the sorted order
    for (Patient& patient : patients) {
        if (patient.getTreated() == 0) {
            // You can add your code here to treat the patient
            cout << "Treating patient: " << patient.getFName() << " " << patient.getLName() << " (Priority: " << patient.getPriority() << ")" << endl;

            // Set the treated attribute to 1 for the treated patient
            patient.setTreated(1);
        }
        treatedPatients.push_back(patient);
    }
}

void readPatientsFromFile(vector<Patient>& patients) {

    logCommand("[Read Patient From File Logged] \n");

    fstream patientFile;
    patientFile.open("patients.txt");
    if (patientFile.is_open()) {
        cout << "file opened successfully" << endl;
    }

    string line, fName, mName, lName, suffix, doctor, treated, priority;
    vector<string> ailments;  // holds list of a patient's ailments

    while (getline(patientFile, line)) {
        // Read input for one patient
        if ((line.find("firstName")) != string::npos) {
            fName = line.substr(10, line.length() - 10);
        } else if ((line.find("middleName")) != string::npos) {
            mName = line.substr(11, line.length() - 11);
        } else if ((line.find("lastName")) != string::npos) {
            lName = line.substr(9, line.length() - 9);
        } else if ((line.find("suffix")) != string::npos) {
            suffix = line.substr(7, line.length() - 7);
        } else if ((line.find("ailment")) != string::npos) {
            ailments.push_back(line.substr(8, line.length() - 8));
        } else if ((line.find("doctor")) != string::npos) {
            doctor = line.substr(7, line.length() - 7);
        } else if ((line.find("treated")) != string::npos) {
            treated = line.substr(8, line.length() - 8);
        } else if ((line.find("priority")) != string::npos) {
            priority = line.substr(9, line.length() - 9);
            patients.emplace_back(fName, mName, lName, suffix, ailments, doctor, stoi(treated), stoi(priority));
            ailments.clear();
        } else if (patientFile.eof()) {
            patients.emplace_back(fName, mName, lName, suffix, ailments, doctor, stoi(treated), stoi(priority));
            ailments.clear();
        }
    }
}

// As a doctor, I want to print out a patient’s information as a report
void printPatientReport(const vector<Patient>& patients) {

    logCommand("[Print Report Logged] \n");

    for (const Patient& patient : patients) {
        cout << "First Name: " << patient.getFName() << endl;
        cout << "Middle Name: " << patient.getMName() << endl;
        cout << "Last Name: " << patient.getLName() << endl;
        cout << "Suffix: " << patient.getSuffix() << endl;

        vector<string> ailments = patient.getAilments();
        for (size_t i = 0; i < ailments.size(); i++) {
            cout << "Ailment " << i + 1 << ": " << ailments[i] << endl;
        }

        cout << "Doctor: " << patient.getDoctor() << endl;
        cout << "Treated: " << patient.getTreated() << endl;
        cout << "Priority: " << patient.getPriority() << endl;
    }
}

// Function to print treated patient report
void printTreatedPatientReport(const vector<Patient>& patients) {

    logCommand("[Print Treated Patient Report Logged] \n");

    for (const Patient& patient : patients) {
        if (patient.getTreated() == 1) {
            cout << "First Name: " << patient.getFName() << endl;
            cout << "Middle Name: " << patient.getMName() << endl;
            cout << "Last Name: " << patient.getLName() << endl;
            cout << "Suffix: " << patient.getSuffix() << endl;

            vector<string> ailments = patient.getAilments();
            for (size_t i = 0; i < ailments.size(); i++) {
                cout << "Ailment " << i + 1 << ": " << ailments[i] << endl;
            }

            cout << "Doctor: " << patient.getDoctor() << endl;
            cout << "Treated: " << patient.getTreated() << endl;
            cout << "Priority: " << patient.getPriority() << endl;
        }
    }
}

//As a doctor, I want to know the next patient to be treated.
void printNextPatientToBeTreated(vector<Patient>& patients) {

    logCommand("[Print Next Patient To Be Treated Logged] \n");

    // Sort the patients based on their priority
    sort(patients.begin(), patients.end(), comparePriority);

    // Initialize the next patient to be treated as nullptr
    Patient* nextPatient = nullptr;

    for (Patient& patient : patients) {
        if (patient.getTreated() == 0) {
            nextPatient = &patient;
            break;
        }
    }

    if (nextPatient != nullptr) {
        cout << "Next patient to be treated:" << endl;
        cout << "First Name: " << nextPatient->getFName() << endl;
        cout << "Middle Name: " << nextPatient->getMName() << endl;
        cout << "Last Name: " << nextPatient->getLName() << endl;
        cout << "Suffix: " << nextPatient->getSuffix() << endl;
        cout << "Priority: " << nextPatient->getPriority() << endl;
    } else {
        cout << "No untreated patients found." << endl;
    }
}

// As a hospital admin, I want to print out a report of all the patients in triage.
void printTriageReport(vector<Patient>& patients) {

    logCommand("[Print Triage Report Logged] \n");

    vector<Patient> untreatedPatients;

    for (const Patient& patient : patients) {
        if (patient.getTreated() == 0) {
            untreatedPatients.push_back(patient);
        }
    }

    // Sort the untreated patients by their priority
    sort(untreatedPatients.begin(), untreatedPatients.end(), [](const Patient& a, const Patient& b) {
        return a.getPriority() < b.getPriority();
    });

    // Print the triage report
    cout << "TRIAGE REPORT:" << endl;
    printPatientReport(untreatedPatients);
}
// As a doctor, I want to treat a patient in triaged order
Patient treatNextPatient(vector<Patient>& patients) {

    logCommand("[Treat Next Patient Logged] \n");

    // Find the next untreated patient with the highest priority
    Patient* nextPatient = nullptr;

    for (Patient& patient : patients) {
        if (patient.getTreated() == 0) {
            if (nextPatient == nullptr || patient.getPriority() < nextPatient->getPriority()) {
                nextPatient = &patient;
            }
        }
    }

    if (nextPatient != nullptr) {
        // Treat the patient
        cout << "Treating patient: " << nextPatient->getFName() << " " << nextPatient->getLName()
             << " (Priority: " << nextPatient->getPriority() << ")" << endl;

        // Update the treated status
        nextPatient->setTreated(1);

        return *nextPatient;
    } else {
        throw runtime_error("No untreated patients left.");
    }
}

// As a hospital admin, I want a print out of all patients by doctor.
void treatPatientsByDoctor(const vector<Patient>& patients, const string& doctor) {

    logCommand("[Treat Patients By Doctor Logged] \n");

    int found = 0;
    cout << "The following are patients that have been assigned to Dr. " << doctor << ":\n\n";

    for (const Patient& patient : patients) {
        if (patient.getDoctor() == doctor) {
            cout << "  First Name: " << patient.getFName() << endl;
            cout << "  Middle Name: " << patient.getMName() << endl;
            cout << "  Last Name: " << patient.getLName() << endl;
            cout << "  Suffix: " << patient.getSuffix() << endl;
            cout << "  Treated: " << patient.getTreated() << endl;
            cout << "  Priority: " << patient.getPriority() << endl;
            cout << endl;
            found = 1;
        }
    }

    if (found == 0)
        cout << "Dr. " << doctor << " currently has no patients\n";
}

// As any user, I want to be able to print out a guide on each command the system offers. (eg "help" functionality).
void helpCommand() {
    cout << "List of available functions:\n";
    cout << "1. toggleDebugMode\n";
    cout << "2. logCommand\n";
    cout << "3. addPatient\n";
    cout << "4. bulkAdd\n";
    cout << "5. comparePriority\n";
    cout << "6. treatPatients\n";
    cout << "7. readPatientsFromFile\n";
    cout << "8. printPatientReport\n";
    cout << "9. printTreatedPatientReport\n";
    cout << "10. printNextPatientToBeTreated\n";
    cout << "11. printTriageReport\n";
    cout << "12. treatNextPatient\n";
    cout << "13. treatPatientsByDoctor\n";
}

int main() {
    cout << "Welcome to the Patient Triage System" << endl;

    vector<Patient> patients;
    readPatientsFromFile(patients);

    int choice;
    string doctor;

    while (true) {
        cout << "\nPlease choose an option:" << endl;
        cout << "1. Print patient report" << endl;
        cout << "2. Print triage report" << endl;
        cout << "3. Print next patient to be treated" << endl;
        cout << "4. Treat next patient" << endl;
        cout << "5. Treat all patients" << endl;
        cout << "6. Print treated patient report" << endl;
        cout << "7. Bulk add patients from file" << endl;
        cout << "8. Add a patient" << endl;
        cout << "9. Treat patients by doctor" << endl;
        cout << "10. Turn on debug mode" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "PATIENT REPORT:" << endl;
                printPatientReport(patients);
                break;

            case 2:
                cout << "REPORT IN TRIAGE ORDER:";
                printTriageReport(patients);
                break;

            case 3:
                cout << "NEXT PATIENT TO BE TREATED:" << endl;
                printNextPatientToBeTreated(patients);
                break;

            case 4:
                cout << "TREAT 1 PATIENT:" << endl;
                treatNextPatient(patients);
                break;

            case 5:
                treatPatients(patients); // Treat patients in triaged order
                break;

            case 6:
                cout << "AFTER TREATMENT PATIENTS:" << endl;
                printTreatedPatientReport(patients);
                break;

            case 7:
                cout << "BULK ADD PATIENTS FROM FILE:" << endl;
                bulkAdd(patients);
                break;

            case 8:
                cout << "ADD:" << endl;
                addPatient(patients);
                break;

            case 9:
                cout << "Enter doctor's name: ";
                cin.ignore();
                getline(cin, doctor);
                treatPatientsByDoctor(patients, doctor);
                break;

            case 10:
                debugMode = !debugMode;
                cout << "Debug mode is now " << (debugMode ? "ON" : "OFF") << "." << endl;
                break;

            case 11:
                cout << "Exiting the program." << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }

    return 0;
}



