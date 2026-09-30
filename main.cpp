#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Struct to store voucher information
struct Voucher {
    int id;
    string code;
    string category;
    string description;
    double minSpend;
    bool isClaimed;
    bool isUsed;

    Voucher(int i, string c, string cat, string desc, double spend, bool claimed)
        : id(i), code(c), category(cat), description(desc), minSpend(spend), isClaimed(claimed), isUsed(false) {}
};

// Helper function to clear terminal screen across OS platforms
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function prototypes
void displayMenu();
void displayAllVouchers(const vector<Voucher>& vouchers);
void displayVouchersByCategory(const vector<Voucher>& vouchers, const string& category, double spendingAmount);
void claimVoucher(vector<Voucher>& vouchers);
void useVoucher(vector<Voucher>& vouchers);
void printTableHeader(bool includeCategory = true);
void printVoucherRow(const Voucher& v, bool includeCategory = true);
void pauseConsole();

int main() {
    vector<Voucher> vouchers;
    vouchers.push_back(Voucher(1, "FS-100",  "Free Shipping",   "Free Shipping Min Spend RM15", 15.00, false));
    vouchers.push_back(Voucher(2, "FOOD-20", "Food & Beverage", "20% OFF Food Delivery",        0.00,  false));
    vouchers.push_back(Voucher(3, "ELEC-50", "Electronics",     "RM50 OFF Minimum Spend RM500", 500.00,false));
    vouchers.push_back(Voucher(4, "FASH-15", "Fashion",         "15% OFF Apparel",               0.00,  false));
    vouchers.push_back(Voucher(5, "FS-200",  "Free Shipping",   "Free Shipping Min Spend RM0",  0.00,  false));

    int choice = 0;
    do {
        clearScreen();
        displayMenu();
        cout << "  Enter choice (1-4): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "\n  [!] Invalid selection! Please enter a number between 1 and 4.\n";
            pauseConsole();
            continue;
        }

        switch (choice) {
            case 1:
                clearScreen();
                displayAllVouchers(vouchers);
                pauseConsole();
                break;
            case 2: {
                clearScreen();
                // Dynamic Category Extraction
                set<string> categories;
                for (const auto& v : vouchers) {
                    categories.insert(v.category);
                }

                vector<string> catList(categories.begin(), categories.end());
                cout << "=========================================================================================\n";
                cout << "                               CATEGORY NAVIGATION MENU                                  \n";
                cout << "=========================================================================================\n\n";
                for (size_t i = 0; i < catList.size(); ++i) {
                    cout << "  [" << i + 1 << "] " << catList[i] << "\n";
                }
                cout << "  [0] Back to Main Menu\n\n";
                cout << "  Select Category: ";

                int catChoice;
                cin >> catChoice;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\n  [!] Invalid choice!\n";
                    pauseConsole();
                    break;
                }
                if (catChoice == 0) break;

                if (catChoice >= 1 && catChoice <= (int)catList.size()) {
                    double spendingAmount;
                    cout << "  Enter your planned spending amount (RM): ";
                    cin >> spendingAmount;

                    if (cin.fail() || spendingAmount < 0) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "\n  [!] Invalid spending amount.\n";
                        pauseConsole();
                        break;
                    }

                    clearScreen();
                    displayVouchersByCategory(vouchers, catList[catChoice - 1], spendingAmount);
                } else {
                    cout << "\n  [!] Invalid category selection.\n";
                }
                pauseConsole();
                break;
            }
            case 3:
                clearScreen();
                claimVoucher(vouchers);
                pauseConsole();
                break;
            case 4:
                clearScreen();
                useVoucher(vouchers);
                pauseConsole();
                break;
            case 5:
                clearScreen();
                cout << "=========================================================================================\n";
                cout << "                Thank you for using Shopee Voucher Navigation System!                    \n";
                cout << "=========================================================================================\n\n";
                break;
            default:
                cout << "\n  [!] Invalid menu selection. Try again.\n";
                pauseConsole();
        }
    } while (choice != 5);

    return 0;
}

void displayMenu() {
    cout << "\n=========================================\n";
    cout << "   SHOPEE VOUCHER NAVIGATION SYSTEM      \n";
    cout << "=========================================\n";
    cout << "1. View All Vouchers\n";
    cout << "2. Navigate / Filter by Category\n";
    cout << "3. Claim Voucher\n";
    cout << "4. Use Voucher\n";
    cout << "5. Exit\n";
    cout << "=========================================\n";
}

void printTableHeader(bool includeCategory) {
    if (includeCategory) {
        cout << left << setw(6)  << "ID"
             << setw(12) << "CODE"
             << setw(20) << "CATEGORY"
             << setw(14) << "MIN SPEND"
             << setw(32) << "DESCRIPTION"
             << setw(12) << "STATUS" << "\n";
    } else {
        cout << left << setw(6)  << "ID"
             << setw(12) << "CODE"
             << setw(14) << "MIN SPEND"
             << setw(36) << "DESCRIPTION"
             << setw(12) << "STATUS" << "\n";
    }
    cout << "-----------------------------------------------------------------------------------------\n";
}

void printVoucherRow(const Voucher& v, bool includeCategory) {
    string status;
    if (v.isUsed) status = "[USED]";
    else if (v.isClaimed) status = "[CLAIMED]";
    else status = "[AVAILABLE]";

    if (includeCategory) {
        cout << left << setw(6)  << v.id
             << setw(12) << v.code
             << setw(20) << v.category
             << "RM " << fixed << setprecision(2) << setw(11) << v.minSpend
             << setw(32) << v.description
             << setw(12) << status << "\n";
    } else {
        cout << left << setw(6)  << v.id
             << setw(12) << v.code
             << "RM " << fixed << setprecision(2) << setw(11) << v.minSpend
             << setw(36) << v.description
             << setw(12) << status << "\n";
    }
}

void displayAllVouchers(const vector<Voucher>& vouchers) {
    cout << "=========================================================================================\n";
    cout << "                                  ALL CLAIMED VOUCHERS                                   \n";
    cout << "=========================================================================================\n";
    printTableHeader(true);

    bool found = false;
    for (const auto& v : vouchers) {
        if (v.isClaimed) {
            printVoucherRow(v, true);
            found = true;
        }
    }

    if (!found) {
        cout << "  No claimed vouchers found in your inventory.\n";
    }
    cout << "-----------------------------------------------------------------------------------------\n";
}

void displayVouchersByCategory(const vector<Voucher>& vouchers, const string& category, double spendingAmount) {
    cout << "=========================================================================================\n";
    cout << "  CATEGORY: " << category << " | YOUR SPENDING: RM " << fixed << setprecision(2) << spendingAmount << "\n";
    cout << "=========================================================================================\n";
    printTableHeader(false);

    bool found = false;
    for (const auto& v : vouchers) {
        if (v.category == category && v.isClaimed && spendingAmount >= v.minSpend) {
            printVoucherRow(v, false);
            found = true;
        }
    }

    if (!found) {
        cout << "  No matching claimed vouchers found for this category and spending limit.\n";
    }
    cout << "-----------------------------------------------------------------------------------------\n";
}

void claimVoucher(vector<Voucher>& vouchers) {
    cout << "=========================================================================================\n";
    cout << "                                 CLAIM AVAILABLE VOUCHERS                                \n";
    cout << "=========================================================================================\n";
    printTableHeader(true);

    bool found = false;
    for (const auto& v : vouchers) {
        if (!v.isClaimed) {
            printVoucherRow(v, true);
            found = true;
        }
    }

    if (!found) {
        cout << "  No available vouchers remaining to claim.\n";
        cout << "-----------------------------------------------------------------------------------------\n";
        return;
    }

    cout << "-----------------------------------------------------------------------------------------\n";
    int id;
    cout << "\n  Enter Voucher ID to claim (0 to cancel): ";
    cin >> id;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n  [!] Invalid input ID.\n";
        return;
    }

    if (id == 0) {
        cout << "\n  Claim request cancelled.\n";
        return;
    }

    for (auto& v : vouchers) {
        if (v.id == id) {
            if (v.isClaimed) {
                cout << "\n  [!] Notice: This voucher has already been claimed!\n";
            } else {
                v.isClaimed = true;
                cout << "\n  [SUCCESS] Voucher " << v.code << " claimed successfully!\n";
            }
            return;
        }
    }

    cout << "\n  [!] Error: Voucher ID not found.\n";
}

void pauseConsole() {
    cout << "\n  Press ENTER to continue...";
    cin.ignore(10000, '\n');
    cin.get();
}
void useVoucher(vector<Voucher>& vouchers) {
    cout << "=========================================================================================\n";
    cout << "                                 USE CLAIMED VOUCHERS                                   \n";
    cout << "=========================================================================================\n";
    printTableHeader(true);

    bool found = false;
    for (const auto& v : vouchers) {
        if (v.isClaimed && !v.isUsed) {
            printVoucherRow(v, true);
            found = true;
        }
    }

    if (!found) {
        cout << "  No claimed and available vouchers found in your inventory.\n";
        cout << "-----------------------------------------------------------------------------------------\n";
        return;
    }

    cout << "-----------------------------------------------------------------------------------------\n";
    int id;
    cout << "\n  Enter Voucher ID to use (0 to cancel): ";
    cin >> id;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n  [!] Invalid input ID.\n";
        return;
    }

    if (id == 0) {
        cout << "\n  Operation cancelled.\n";
        return;
    }

    for (auto& v : vouchers) {
        if (v.id == id) {
            if (!v.isClaimed) {
                cout << "\n  [!] Error: This voucher has not been claimed yet!\n";
            } else if (v.isUsed) {
                cout << "\n  [!] Error: This voucher has already been used!\n";
            } else {
                double spendingAmount;
                cout << "  Enter your current order total (RM): ";
                cin >> spendingAmount;

                if (cin.fail() || spendingAmount < 0) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\n  [!] Invalid order total.\n";
                    return;
                }

                if (spendingAmount >= v.minSpend) {
                    v.isUsed = true;
                    cout << "\n  [SUCCESS] Voucher " << v.code << " applied successfully to your order!\n";
                } else {
                    cout << "\n  [!] Error: Minimum spend of RM " << fixed << setprecision(2) << v.minSpend << " not met!\n";
                }
            }
            return;
        }
    }

    cout << "\n  [!] Error: Voucher ID not found.\n";
}
