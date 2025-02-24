#include <iostream>
#include <vector>
#include <cctype>
#include <unordered_set>
using namespace std;

const int KICH_THUOC = 5;
char ma_tran[KICH_THUOC][KICH_THUOC];

void taoMaTran(const char *khoa) {
    unordered_set<char> da_dung;
    char khoa_xu_ly[26];
    int do_dai_khoa = 0;
    
    for (int i = 0; khoa[i] != '\0'; i++) {
        char c = khoa[i];
        if (c == 'J') c = 'I';
        if (da_dung.find(c) == da_dung.end()) {
            da_dung.insert(c);
            khoa_xu_ly[do_dai_khoa++] = c;
        }
    }
    
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue;
        if (da_dung.find(c) == da_dung.end()) {
            da_dung.insert(c);
            khoa_xu_ly[do_dai_khoa++] = c;
        }
    }
    
    int chi_so = 0;
    for (int i = 0; i < KICH_THUOC; i++) {
        for (int j = 0; j < KICH_THUOC; j++) {
            ma_tran[i][j] = khoa_xu_ly[chi_so++];
        }
    }
}

void timViTri(char c, int &dong, int &cot) {
    if (c == 'J') c = 'I';
    for (int i = 0; i < KICH_THUOC; i++) {
        for (int j = 0; j < KICH_THUOC; j++) {
            if (ma_tran[i][j] == c) {
                dong = i;
                cot = j;
                return;
            }
        }
    }
}

void chuanBiVanBan(const char *van_ban, char *van_ban_xu_ly) {
    int do_dai = 0;
    for (int i = 0; van_ban[i] != '\0'; i++) {
        if (isalpha(van_ban[i])) van_ban_xu_ly[do_dai++] = toupper(van_ban[i]);
    }
    for (int i = 1; i < do_dai; i += 2) {
        if (van_ban_xu_ly[i] == van_ban_xu_ly[i - 1]) {
            for (int j = do_dai; j > i; j--) {
                van_ban_xu_ly[j] = van_ban_xu_ly[j - 1];
            }
            van_ban_xu_ly[i] = 'X';
            do_dai++;
        }
    }
    if (do_dai % 2 != 0) van_ban_xu_ly[do_dai++] = 'X';
    van_ban_xu_ly[do_dai] = '\0';
}

void maHoa(const char *van_ban, const char *khoa, char *ban_ma) {
    taoMaTran(khoa);
    char van_ban_xu_ly[100];
    chuanBiVanBan(van_ban, van_ban_xu_ly);
    int chi_so = 0;
    
    for (int i = 0; van_ban_xu_ly[i] != '\0'; i += 2) {
        int d1, c1, d2, c2;
        timViTri(van_ban_xu_ly[i], d1, c1);
        timViTri(van_ban_xu_ly[i + 1], d2, c2);
        
        if (d1 == d2) {
            ban_ma[chi_so++] = ma_tran[d1][(c1 + 1) % KICH_THUOC];
            ban_ma[chi_so++] = ma_tran[d2][(c2 + 1) % KICH_THUOC];
        } else if (c1 == c2) {
            ban_ma[chi_so++] = ma_tran[(d1 + 1) % KICH_THUOC][c1];
            ban_ma[chi_so++] = ma_tran[(d2 + 1) % KICH_THUOC][c2];
        } else {
            ban_ma[chi_so++] = ma_tran[d1][c2];
            ban_ma[chi_so++] = ma_tran[d2][c1];
        }
    }
    ban_ma[chi_so] = '\0';
}

int main() {
    char van_ban[100], khoa[100], ban_ma[100];
    cout << "Nhap ban ro: ";
    cin.getline(van_ban, 100);
    cout << "Nhap khoa: ";
    cin.getline(khoa, 100);
    
    maHoa(van_ban, khoa, ban_ma);
    cout << "Ban ma: " << ban_ma << endl;
    return 0;
}
