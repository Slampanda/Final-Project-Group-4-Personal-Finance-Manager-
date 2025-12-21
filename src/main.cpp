#include "common.h"
#include "financeManager.h"

int main(){
    try{
        cout << "=========================================" << endl;
        cout << "   PERSONAL FINANCE MANAGER v1.0" <<endl;
        cout << "=========================================" << endl;
        
        FinanceManager financeManager;
        financeManager.run();
        
        cout << "\nThank you for using Personal Finance Manager!" << endl;
        
    } catch (const exception& e) {
        cerr << "\n*** FATAL ERROR ***" << endl;
        cerr << "Error: " << e.what() << endl;
        cerr << "Program will now exit." << endl;
        return 1;
    } catch (...) {
        cerr << "\n*** UNKNOWN ERROR ***" << endl;
        cerr << "Program will now exit." << endl;
        return 1;
    }
    return 0;
}
