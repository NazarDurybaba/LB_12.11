#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// Структура для представлення кожної заявки
struct TicketRequest {
    string destination;
    int flightNumber;
    string passengerName;
    string departureDate;
    TicketRequest* left;
    TicketRequest* right;
};

// Додати нову заявку до бінарного дерева
void addTicketRequest(TicketRequest*& root, TicketRequest* newRequest) {
    if (root == nullptr) {
        root = newRequest;
    }
    else {
        if (newRequest->flightNumber < root->flightNumber) {
            addTicketRequest(root->left, newRequest);
        }
        else {
            addTicketRequest(root->right, newRequest);
        }
    }
}

// Видалити заявку за номером рейсу та датою
TicketRequest* removeTicketRequest(TicketRequest* root, int flightNumber, const string& departureDate) {
    if (root == nullptr) {
        return nullptr;
    }

    if (flightNumber < root->flightNumber) {
        root->left = removeTicketRequest(root->left, flightNumber, departureDate);
    }
    else if (flightNumber > root->flightNumber) {
        root->right = removeTicketRequest(root->right, flightNumber, departureDate);
    }
    else {
        if (root->departureDate != departureDate) {
            root->left = removeTicketRequest(root->left, flightNumber, departureDate);
            root->right = removeTicketRequest(root->right, flightNumber, departureDate);
        }
        else {
            if (root->left == nullptr) {
                TicketRequest* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                TicketRequest* temp = root->left;
                delete root;
                return temp;
            }

            TicketRequest* temp = root->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }

            root->flightNumber = temp->flightNumber;
            root->departureDate = temp->departureDate;
            root->destination = temp->destination;
            root->passengerName = temp->passengerName;

            root->right = removeTicketRequest(root->right, temp->flightNumber, temp->departureDate);
        }
    }

    return root;
}

// Вивести всі заявки
void printAllTicketRequests(TicketRequest* root) {
    if (root != nullptr) {
        printAllTicketRequests(root->left);
        cout << "Destination: " << root->destination << ", Flight Number: " << root->flightNumber << ", Passenger: " << root->passengerName << ", Departure Date: " << root->departureDate << endl;
        printAllTicketRequests(root->right);
    }
}

// Звільнити пам'ять, зв'язану з бінарним деревом
void deleteTree(TicketRequest* root) {
    if (root != nullptr) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }
}

// Функція для рекурсивного запису заявок у файл
void saveTicketRequests(TicketRequest* root, ofstream& outFile) {
    if (root != nullptr) {
        saveTicketRequests(root->left, outFile);
        outFile << root->destination << "|" << root->flightNumber << "|" << root->passengerName << "|" << root->departureDate << endl;
        saveTicketRequests(root->right, outFile);
    }
}

int main() {
    TicketRequest* root = nullptr;

    int choice;
    do {
        cout << "Menu:" << endl;
        cout << "1. Add a ticket request" << endl;
        cout << "2. Remove ticket requests by flight number and departure date" << endl;
        cout << "3. Print all ticket requests" << endl;
        cout << "4. Save ticket requests to file" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            TicketRequest* newRequest = new TicketRequest;
            cout << "Enter destination: ";
            cin.ignore();
            getline(cin, newRequest->destination);
            cout << "Enter flight number: ";
            cin >> newRequest->flightNumber;
            cout << "Enter passenger name: ";
            cin.ignore();
            getline(cin, newRequest->passengerName);
            cout << "Enter departure date: ";
            getline(cin, newRequest->departureDate);
            newRequest->left = nullptr;
            newRequest->right = nullptr;
            addTicketRequest(root, newRequest);
            break;
        }
        case 2: {
            int flightNumber;
            string departureDate;
            cout << "Enter flight number: ";
            cin >> flightNumber;
            cout << "Enter departure date: ";
            cin >> departureDate;
            root = removeTicketRequest(root, flightNumber, departureDate);
            break;
        }
        case 3: {
            cout << "All ticket requests:" << endl;
            printAllTicketRequests(root);
            break;
        }
        case 4: {
            string filename;
            cout << "Enter filename to save: ";
            cin >> filename;
            ofstream outFile(filename);
            if (outFile.is_open()) {
                saveTicketRequests(root, outFile);
                outFile.close();
                cout << "Ticket requests saved to file successfully." << endl;
            }
            else {
                cout << "Unable to open file for writing." << endl;
            }
            break;
        }
        case 5: {
            break;
        }
        default: {
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }
        }
    } while (choice != 5);

    // Звільнення пам'яті
    deleteTree(root);

    return 0;
}
