#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iomanip>

using namespace std;

// Struct to store voucher information
struct Voucher {
    int id;
    string code;
    string category;
    string description;
    double minSpend;
    bool isClaimed;

    Voucher(int i, string c, string cat, string desc, double spend, bool claimed)
        : id(i), code(c), category(cat), description(desc), minSpend(spend), isClaimed(claimed) {}
};

// Function prototypes
void displayMenu();
void displayAllVouchers(const vector<Voucher>& vouchers);
void displayVouchersByCategory(const vector<Voucher>& vouchers,const string& category,double spendingAmount);
void claimVoucher(vector<Voucher>& vouchers);
void printVoucherRow(const Voucher& v);

int main() {
    vector<Voucher> vouchers;
    vouchers.push_back(Voucher(1, "FS-100", "Free Shipping",
        "Free Shipping Min Spend RM15", 15, false));

    vouchers.push_back(Voucher(2, "FOOD-20", "Food & Beverage",
        "20% OFF Food Delivery", 0, false));

    vouchers.push_back(Voucher(3, "ELEC-50", "Electronics",
        "RM50 OFF Minimum Spend RM500", 500, false));

    vouchers.push_back(Voucher(4, "FASH-15", "Fashion",
        "15% OFF Apparel", 0, false));

    vouchers.push_back(Voucher(5, "FS-200", "Free Shipping",
        "Free Shipping Min Spend RM0", 0, false));

    int choice = 0;
    do {
        displayMenu();
        cout << "Enter choice (1-4): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid selection! Please enter a number between 1 and 4.\n";
            continue;
        }

        switch (choice) {
            case 1:
                displayAllVouchers(vouchers);
                break;
            case 2: {
                // Dynamic Category Extraction
                set<string> categories;
                for (const auto& v : vouchers) {
                    categories.insert(v.category);
                }

                vector<string> catList(categories.begin(), categories.end());
                cout << "\n--- Category Navigation ---\n";
                for (size_t i = 0; i < catList.size(); ++i) {
                    cout << i + 1 << ". " << catList[i] << "\n";
                }
                cout << "0. Back to Main Menu\n";
                cout << "Choice: ";

                int catChoice;
                cin >> catChoice;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid choice!\n";
                    break;
                }
                if (catChoice == 0) break;
                if (catChoice >= 1 && catChoice <= (int)catList.size()) {
                    double spendingAmount;

                    cout << "Enter your spending amount (RM): ";
                    cin >> spendingAmount;

                    if (cin.fail() || spendingAmount < 0) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "Invalid spending amount.\n";
                        break;
                    }

                    displayVouchersByCategory(
                        vouchers,
                        catList[catChoice - 1],
                        spendingAmount
                    );
                } else {
                    cout << "Invalid category selection.\n";
                }
                break;
            }
            case 3:
                claimVoucher(vouchers);
                break;
            case 4:
                cout << "Exiting Shopee Voucher System. Thank you!\n";
                break;
            default:
                cout << "Invalid menu selection. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}

void displayMenu() {
    cout << "\n\n\n\n\n\n=========================================\n";
    cout << "   SHOPEE VOUCHER NAVIGATION SYSTEM      \n";
    cout << "=========================================\n";
    cout << "1. View All Vouchers\n";
    cout << "2. Navigate / Filter by Category\n";
    cout << "3. Claim Voucher\n";
    cout << "4. Exit\n";
    cout << "=========================================\n\n\n\n\n\n";
}

void printVoucherRow(const Voucher& v) {
    string status = v.isClaimed ? "[CLAIMED]  " : "[AVAILABLE]";
    cout << left << setw(4) << v.id
         << setw(12) << v.code
         << setw(18) << v.category
         << setw(30) << v.description
         << status << "\n";
}

void displayAllVouchers(const vector<Voucher>& vouchers) {
    cout << "\n\n\n\n\n\n--- All Claimed Vouchers ---\n\n";
    cout << left << setw(4) << "ID"
         << setw(12) << "Code"
         << setw(18) << "Category"
         << setw(30) << "Description"
         << "Status\n";
    cout << string(70, '-') << "\n";

    bool found = false;

    for (const auto& v : vouchers) {
        if (v.isClaimed) {
            printVoucherRow(v);
            found = true;
        }
    }

    if (!found) {
        cout << "No claimed vouchers found.\n";
    }
}


void displayVouchersByCategory(
    const vector<Voucher>& vouchers,
    const string& category,
    double spendingAmount
) {
    cout << "\n--- Matching Vouchers: " << category << " ---\n";
    cout << "Your Spending: RM"
         << fixed << setprecision(2)
         << spendingAmount << "\n";

    cout << left
         << setw(4) << "ID"
         << setw(12) << "Code"
         << setw(30) << "Description"
         << "Minimum Spend\n";

    cout << string(65, '-') << "\n";

    bool found = false;

    for (const auto& v : vouchers) {

        if (v.category == category &&
            v.isClaimed &&
            spendingAmount >= v.minSpend) {

            cout << left
                 << setw(4) << v.id
                 << setw(12) << v.code
                 << setw(30) << v.description
                 << "RM" << fixed << setprecision(2)
                 << v.minSpend << "\n";

            found = true;
        }
    }

    if (!found) {
        cout << "No matching claimed vouchers found.\n";
    }
}

void claimVoucher(vector<Voucher>& vouchers) {
    cout << "\n--- Claim Voucher ---\n";

    cout << left
         << setw(4) << "ID"
         << setw(12) << "Code"
         << setw(18) << "Category"
         << setw(30) << "Description"
         << "Status\n";

    cout << string(75, '-') << "\n";

    bool found = false;

    // Display only vouchers that have NOT been claimed
    for (const auto& v : vouchers) {
        if (!v.isClaimed) {
            printVoucherRow(v);
            found = true;
        }
    }

    if (!found) {
        cout << "No available vouchers to claim.\n";
        return;
    }

    int id;
    cout << "\nEnter voucher ID to claim (0 to cancel): ";
    cin >> id;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid ID.\n";
        return;
    }

    if (id == 0) {
        cout << "Claim cancelled.\n";
        return;
    }

    for (auto& v : vouchers) {
        if (v.id == id) {

            if (v.isClaimed) {
                cout << "This voucher has already been claimed.\n";
            } else {
                v.isClaimed = true;
                cout << "Voucher " << v.code << " claimed successfully!\n";
            }

            return;
        }
    }

    cout << "Voucher ID not found.\n";
}