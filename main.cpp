#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Struct to store voucher information
struct Voucher {
    int id;
    string code;
    string category;
    string description;
    bool isClaimed;
};

// Function prototypes
void displayMenu();
void displayAllVouchers(const vector<Voucher>& vouchers);
void displayVouchersByCategory(const vector<Voucher>& vouchers, const string& category);
void claimVoucher(vector<Voucher>& vouchers);

int main() {
    // Initializing voucher inventory
    vector<Voucher> vouchers = {
        {1, "FS-100", "Free Shipping", "Free Shipping Min Spend RM15", false},
        {2, "FOOD-20", "Food & Beverage", "20% OFF Food Delivery", false},
        {3, "ELEC-50", "Electronics", "RM50 OFF Minimum Spend RM500", false},
        {4, "FASH-15", "Fashion", "15% OFF Apparel", false},
        {5, "FS-200", "Free Shipping", "Free Shipping Min Spend RM0", false}
    };

    int choice = 0;
    do {
        displayMenu();
        cout << "Enter choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayAllVouchers(vouchers);
                break;
            case 2: {
                cout << "\nSelect Category Navigation:\n";
                cout << "1. Free Shipping\n2. Food & Beverage\n3. Electronics\n4. Fashion\nChoice: ";
                int catChoice;
                cin >> catChoice;
                if (catChoice == 1) displayVouchersByCategory(vouchers, "Free Shipping");
                else if (catChoice == 2) displayVouchersByCategory(vouchers, "Food & Beverage");
                else if (catChoice == 3) displayVouchersByCategory(vouchers, "Electronics");
                else if (catChoice == 4) displayVouchersByCategory(vouchers, "Fashion");
                else cout << "Invalid category selection.\n";
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
    cout << "\n=========================================\n";
    cout << "   SHOPEE VOUCHER NAVIGATION SYSTEM      \n";
    cout << "=========================================\n";
    cout << "1. View All Vouchers\n";
    cout << "2. Navigate / Filter by Category\n";
    cout << "3. Claim Voucher\n";
    cout << "4. Exit\n";
    cout << "=========================================\n";
}

void displayAllVouchers(const vector<Voucher>& vouchers) {
    cout << "\n--- All Available Vouchers ---\n";
    for (const auto& v : vouchers) {
        cout << "[" << v.id << "] " << v.code << " | Category: " << v.category 
             << " | " << v.description << " | Status: " << (v.isClaimed ? "CLAIMED" : "AVAILABLE") << "\n";
    }
}

void displayVouchersByCategory(const vector<Voucher>& vouchers, const string& category) {
    cout << "\n--- Category: " << category << " ---\n";
    bool found = false;
    for (const auto& v : vouchers) {
        if (v.category == category) {
            cout << "[" << v.id << "] " << v.code << " | " << v.description 
                 << " | Status: " << (v.isClaimed ? "CLAIMED" : "AVAILABLE") << "\n";
            found = true;
        }
    }
    if (!found) cout << "No vouchers found in this category.\n";
}

void claimVoucher(vector<Voucher>& vouchers) {
    int id;
    cout << "Enter Voucher ID to claim: ";
    cin >> id;
    for (auto& v : vouchers) {
        if (v.id == id) {
            if (v.isClaimed) {
                cout << "Voucher has already been claimed!\n";
            } else {
                v.isClaimed = true;
                cout << "Success! Claimed voucher: " << v.code << "\n";
            }
            return;
        }
    }
    cout << "Voucher ID not found.\n";
}