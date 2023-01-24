#include<bits/stdc++.h>

using namespace std;

string daftarOperasi = "+-/*";
string kartuValid[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
map<string, int> daftarNilaiKartu;

const int JENIS_KARTU = 13;
const double EPS = 1e-6;

/**
 * @brief inisialisasi program
 * 
 */
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

    // randomize
    srand(time(NULL));
}

/**
 * @return string berupa kartu random
 */
string randomCard() {
    return kartuValid[rand() % JENIS_KARTU];
}

/**
 * @brief mengembalikan true jika kartu valid
 * 
 * @param c kartu
 * @return true 
 * @return false 
 */
bool isKartuValid(string c) {
    for(auto x : kartuValid) {
        if(c == x) return true;
    }
    return false;
}

/**
 * @brief mengembalikan true jika selisih a dan b kurang dari epsilon (EPS)
 * 
 * @param a 
 * @param b 
 * @return true 
 * @return false 
 */
bool isSame (double a, double b) {
    return (a < b + EPS) && (b < a + EPS);
}

/**
 * @brief Mengembalikan hasil a op b
 * 
 * @param a 
 * @param b 
 * @param op anggota {+, -, *, /}
 * @return (double) a op b
 */
double operate(double a, double b, char op) {
    if(op == '+') return a + b;
    if(op == '-') return a - b;
    if(op == '*') return a * b;
    if(op == '/') return a / b;
    assert(0);
    return -1;
}

/**
 * @brief Menggunakan urutan kartu dan operasi untuk mengisi ans
 * 
 * @param op urutan operasi
 * @param nilaiKartu urutan kartu
 * @param ans menyimpan jawaban
 */
void hitungJawaban(vector<char> &op, vector<int> &nilaiKartu, vector<string> &ans) {
    double a = nilaiKartu[0], b = nilaiKartu[1], c = nilaiKartu[2], d = nilaiKartu[3];
    // Lakukan seluruh kemungkinan urutan
    // ((a op b) op c) op d
    if (isSame(operate(operate(operate(a, b, op[0]), c, op[1]), d, op[2]), 24)) {
        stringstream ss;
        ss << "((" << a << " " << op[0] << " " << b << ") " << op[1] << " " << c << ") " << op[2] << " " << d << "";
        ans.push_back(ss.str());
    }
    // (a op (b op c)) op d
    if (isSame(operate(operate(a, operate(b, c, op[1]), op[0]), d, op[2]), 24)) {
        stringstream ss;
        ss << "(" << a << " " << op[0] << " (" << b << " " << op[1] << " " << c << ")) " << op[2] << " " << d << "";
        ans.push_back(ss.str());
    }
    // a op (b op (c op d))
    if (isSame(operate(a, operate(b, operate(c, d, op[2]), op[1]), op[0]), 24)) {
        stringstream ss;
        ss << "" << a << " " << op[0] << " (" << b << " " << op[1] << " (" << c << " " << op[2] << " " << d << "))";
        ans.push_back(ss.str());
    }
    // a op ((b op c) op d)
    if (isSame(operate(a, operate(operate(b, c, op[1]), d, op[2]), op[0]), 24)) {
        stringstream ss;
        ss << "" << a << " " << op[0] << " ((" << b << " " << op[1] << " " << c << ") " << op[2] << " " << d << ")";
        ans.push_back(ss.str());
    }
    // (a op b) op (c op d)
    if (isSame(operate(operate(a, b, op[0]), operate(c, d, op[2]), op[1]), 24)) {
        stringstream ss;
        ss << "(" << a << " " << op[0] << " " << b << ") " << op[1] << " (" << c << " " << op[2] << " " << d << ")";
        ans.push_back(ss.str());
    }
}

/**
 * @brief membangkitkan kemungkinan operasi untuk mengisi ans
 * 
 * @param opNum index, bernilai 0 pada pemanggilan
 * @param op operasi yang digunakan, kosong pada pemanggilan
 * @param nilaiKartu permutasi kartu
 * @param ans menyimpan jawaban
 */
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

/**
 * @brief membangkitkan permutasi nilai kartu untuk mengisi ans
 * 
 * @param idx harus bernilai 0 pada pemanggilan
 * @param nilaiKartu menyimpan hasil permutasi, harus kosong pada pemanggilan
 * @param jumlahKartu adalah frequency array dari kartu pada input, berukuran JENIS_KARTU + 1
 * @param ans menyimpan jawaban
 */
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

/**
 * @brief output jawaban dan durasi
 * 
 * @param output_stream cout atau ostream lain
 * @param ans vector<string> berisi jawaban
 * @param duration durasi dalam milisekon
 */
void output(ostream& output_stream, const vector<string>& ans, chrono::milliseconds duration) {
    if (ans.size() == 0) {
        output_stream << "no solution found\n";
    }
    else if (ans.size() == 1) {
        output_stream << ans.size() << " solution found\n";
    }
    else {
        output_stream << ans.size() << " solutions found\n";
    }
    
    for(string s: ans) {
        output_stream << s << '\n';
    }
    output_stream<< "Execution time = " << duration.count() << " milliseconds" << endl;
}

int32_t main(int argc, char *argv[]) {
    init();
    string path_prefix = "test/";
    bool strictCommandOutput = false;

    // Arguments, for testing purpose
    if(argc == 2 || argc > 3) {
        cout << "Invalid Argument count!" << endl;
        return 0;
    }
    else if(argc == 3) {
        string path_input = path_prefix, path_output = path_prefix;
        path_input.append(argv[1]);
        path_output.append(argv[2]);
        if (strcmp(argv[1], "cin")) {
            freopen(path_input.c_str(), "r", stdin);
        }
        if (strcmp(argv[2], "cout")) {
            freopen(path_output.c_str(), "w", stdout);
        }
        strictCommandOutput = true;
    }
    else if(argc == 1) {
        cout << "Masukkan 4 kartu (contoh: A 8 9 Q):\n";
    }

    // Input
    vector<string> kartu(4);
    vector<int> jumlahKartu(JENIS_KARTU + 1, 0);
    bool isRandom = false;
    while (true) {
        jumlahKartu = vector<int>(JENIS_KARTU + 1, 0);
        string input_string;
        getline(cin, input_string);
        stringstream input_stream(input_string);
        
        bool invalid_input = false;
        for(int i = 0; i < 4; i++) {
            if (!(input_stream >> kartu[i])) {
                // validasi input < 4
                invalid_input = true;
                break;
            }
            if (kartu[i] == "*") {
                // random kartu
                kartu[i] = randomCard();
                isRandom = true;
            }
            if (!isKartuValid(kartu[i])) {
                // validasi input bukan jenis kartu
                invalid_input = true;
                break;
            }
            jumlahKartu[daftarNilaiKartu[kartu[i]]]++;
        }

        string tmp;
        if (invalid_input || input_stream >> tmp) {
            cout << "Masukan tidak sesuai\n";
            continue;
        }

        // lolos seluruh validasi, keluar dari loop
        break;
    }

    if (isRandom) {
        cout << "Kartu : " << kartu[0] << ' ' << kartu[1] << ' ' << kartu[2] << ' ' << kartu[3] << '\n';
    }

    // Selesai input, mulai menghitung waktu eksekusi program
    auto start = chrono::high_resolution_clock::now();

    vector<string> ans;
    permutasiNilaiKartu(0, vector<int>(), jumlahKartu, ans);

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);

    output(cout, ans, duration);

    if (!strictCommandOutput) {
        while(true) {
            cout << "Apakah ingin menyimpan solusi?(Y/N)\n";
            string response;
            cin >> response;
            if (response == "Y" || response == "y") {
                cout << "Nama file (contoh: testcase3.out) : ";
                string nama_file;
                cin >> nama_file;
                string path_output = path_prefix + nama_file;
                ofstream output_stream(path_output);

                output_stream << "Kartu : " << kartu[0] << ' ' << kartu[1] << ' ' << kartu[2] << ' ' << kartu[3] << '\n';
                output(output_stream, ans, duration);

                cout << "Solusi sudah dimasukkan ke " << path_output << '\n';
                break;
            }
            else if (response == "N" || response == "n") {
                break;
            }
            
        }
        
    }
}