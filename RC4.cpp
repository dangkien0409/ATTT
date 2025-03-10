#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

void ksa(vector<int>& S, const string& key) {
    int j = 0;
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key.length()]) % 256;
        swap(S[i], S[j]);
    }
}

vector<int> prga(const vector<int>& S, const string& plaintext) {
    vector<int> ciphertext;
    int i = 0, j = 0;
    vector<int> S_temp = S;
    for (char c : plaintext) {
        i = (i + 1) % 256;
        j = (j + S_temp[i]) % 256;
        swap(S_temp[i], S_temp[j]);
        int k = S_temp[(S_temp[i] + S_temp[j]) % 256];
        ciphertext.push_back(c ^ k);
    }
    return ciphertext;
}

int main() {
    string key = "mysecretkey";
    string plaintext = "Hanoi University of Science and Technology";

    vector<int> S(256);
    ksa(S, key);

    vector<int> ciphertext = prga(S, plaintext);

    cout << "Dòng khóa (S-box sau KSA):\n";
    for (int i = 0; i < 256; i++) {
        cout << setw(3) << S[i] << ((i + 1) % 16 == 0 ? "\n" : " ");
    }

    cout << "\nBản mã (dạng hex):\n";
    for (int c : ciphertext) {
        cout << hex << setw(2) << setfill('0') << c << " ";
    }

    cout << endl;
    return 0;
}
