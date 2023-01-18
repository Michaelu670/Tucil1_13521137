#include<bits/stdc++.h>

using namespace std;

string daftarOperasi = "+-/*";
map<string, int> daftarNilaiKartu;

const int JENIS_KARTU = 13;

void init() {
    // kartu angka 2-9
    string tmp = "1";
    for(int i = 2; i <= 9; i++) {
        tmp[0] = i + '0';
        daftarNilaiKartu[tmp] = i;
    }
    
    // kartu angka 10
    daftarNilaiKartu["10"] = 10;

    // kartu huruf senilai 10
    daftarNilaiKartu["J"] = 11;
    daftarNilaiKartu["Q"] = 12;
    daftarNilaiKartu["K"] = 13;

    // kartu as
    daftarNilaiKartu["A"] = 1;
}

bool isKartuValid(string c) {
    string kartuValid[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    for(auto x : kartuValid) {
        if(c == x) return true;
    }
    return false;
}

double operate(double a, double b, char op) {
    if(op == '+') return a + b;
    if(op == '-') return a - b;
    if(op == '*') return a * b;
    if(op == '/') return a / b;
    assert(0);
    return -1;
}

void hitungJawaban(vector<char> &op, vector<int> &nilaiKartu, vector<string> &ans) {
    double a = nilaiKartu[0], b = nilaiKartu[1], c = nilaiKartu[2], d = nilaiKartu[3];
    // Lakukan seluruh kemungkinan urutan
    // ((a op b) op c) op d
    if ((int)operate(operate(operate(a, b, op[0]), c, op[1]), d, op[2]) == 24) {
        stringstream ss;
        ss << "((" << a << " " << op[0] << " " << b << ") " << op[1] << " " << c << ") " << op[2] << " " << d << "";
        ans.push_back(ss.str());
    }
    // (a op (b op c)) op d
    if ((int)operate(operate(a, operate(b, c, op[1]), op[0]), d, op[2]) == 24) {
        stringstream ss;
        ss << "(" << a << " " << op[0] << " (" << b << " " << op[1] << " " << c << ")) " << op[2] << " " << d << "";
        ans.push_back(ss.str());
    }
    // a op (b op (c op d))
    if ((int)operate(a, operate(b, operate(c, d, op[2]), op[1]), op[0]) == 24) {
        stringstream ss;
        ss << "" << a << " " << op[0] << " (" << b << " " << op[1] << " (" << c << " " << op[2] << " " << d << "))";
        ans.push_back(ss.str());
    }
    // a op ((b op c) op d)
    if ((int)operate(a, operate(operate(b, c, op[1]), d, op[2]), op[0]) == 24) {
        stringstream ss;
        ss << "" << a << " " << op[0] << " ((" << b << " " << op[1] << " " << c << ") " << op[2] << " " << d << ")";
        ans.push_back(ss.str());
    }
    // (a op b) op (c op d)
    if ((int)operate(operate(a, b, op[0]), operate(c, d, op[2]), op[1]) == 24) {
        stringstream ss;
        ss << "(" << a << " " << op[0] << " " << b << ") " << op[1] << " (" << c << " " << op[2] << " " << d << ")";
        ans.push_back(ss.str());
    }
}

void searchKemungkinanOperasi(int opNum, vector<char> op, vector<int> &nilaiKartu, vector<string> &ans) {
    if(opNum == 3) {
        hitungJawaban(op, nilaiKartu, ans);
        return;
    }
    op.push_back('*');
    for(char c: daftarOperasi) {
        op[opNum] = c;
        searchKemungkinanOperasi(opNum+1, op, nilaiKartu, ans);
    }
}

void permutasiNilaiKartu(int idx, vector<int> nilaiKartu, vector<int> jumlahKartu, vector<string> &ans) {
    if(idx == 4) {
        searchKemungkinanOperasi(0, vector<char>(0), nilaiKartu, ans);
        return;
    }
    nilaiKartu.push_back(0);
    for (int i = 1; i <= JENIS_KARTU; i++) {
        if (jumlahKartu[i]) {
            jumlahKartu[i]--;
            nilaiKartu[idx] = i;
            permutasiNilaiKartu(idx + 1, nilaiKartu, jumlahKartu, ans);
            jumlahKartu[i]++;
        }
    }
}

int32_t main(int argc, char *argv[]) {
    init();
    string path_prefix = "../test/";
    if(argc == 2) {
        string path_output = path_prefix;
        path_output.append(argv[1]);
        freopen(path_output.c_str(), "w", stdout);
    }
    else if(argc == 3) {
        string path_input = path_prefix, path_output = path_prefix;
        path_input.append(argv[1]);
        path_output.append(argv[2]);
        freopen(path_input.c_str(), "r", stdin);
        freopen(path_output.c_str(), "w", stdout);
    }
    vector<string> kartu(4);
    vector<int> jumlahKartu(JENIS_KARTU + 1, 0);
    for(int i = 0; i < 4; i++) {
        cin >> kartu[i];
        assert(isKartuValid(kartu[i]));
        jumlahKartu[daftarNilaiKartu[kartu[i]]]++;
    }

    vector<string> ans;
    permutasiNilaiKartu(0, vector<int>(), jumlahKartu, ans);

    if (ans.size() == 0) {
        cout << "no solution found\n";
    }
    else if (ans.size() == 1) {
        cout << ans.size() << " solution found\n";
    }
    else {
        cout << ans.size() << " solutions found\n";
    }
    
    for(string s: ans) {
        cout << s << '\n';
    }
}