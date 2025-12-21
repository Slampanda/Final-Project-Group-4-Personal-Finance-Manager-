#include "common.h"
#include "numberUtils.h"

string formatNumber(double number){
    stringstream ss;
    
    // Chia thành phần nguyên và phần thập phân
    long long intPart = static_cast<long long>(number);
    double fracPart = number - intPart;
    
    // Format phần nguyên với dấu phẩy
    string intStr = to_string(intPart);
    string formatted = "";
    
    int len = int(intStr.length());
    for (int i = len - 1, count = 0; i >= 0; i--, count++){
        if (count > 0 && count%3 == 0){
            formatted = "," + formatted;
        }
        formatted = intStr[i] + formatted;
    }
    
    // Thêm phần thập phân nếu có
    if (fracPart > 0.0001) {  // Có phần thập phân
        ss << fixed << setprecision(2) << number;
        string fullStr = ss.str();
        size_t dotPos = fullStr.find('.');
        if (dotPos != string::npos) {
            string intPartStr = fullStr.substr(0, dotPos);
            string fracPartStr = fullStr.substr(dotPos);
            
            // Format phần nguyên
            formatted = "";
            len = int(intPartStr.length());
            for (int i = len - 1, count = 0; i >= 0; i--, count++) {
                if (count > 0 && count%3 == 0) {
                    formatted = "," + formatted;
                }
                formatted = intPartStr[i] + formatted;
            }
            
            // Thêm phần thập phân
            formatted += fracPartStr;
        }
    }
    return formatted;
}
