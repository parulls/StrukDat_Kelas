#include <iostream>
#include <iomanip>
#include <conio.h>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class Bank {
private:
    struct Pengguna {
        string pin, norek, nama, alamat, notel;
        double saldo;
        Pengguna* next;
    };

    struct Pembayaran {
        string keterangan;
        double jumlah;
    };

    Pengguna* head;
    vector<Pembayaran> pembayaranList;

    stack<string> transaksiHistory; 
    queue<string> antrianTransaksi; 

public:
    Bank() : head(nullptr) {}

    void menu();
    void pengaturanATM();
    void penggunaBaru();
    void deposit(Pengguna* user);
    void penarikan(Pengguna* user);
    void transfer(Pengguna* user);
    void pembayaran(Pengguna* user);
    void tampilkanInformasi(Pengguna* user);
    void tampilkanPembayaran();
    void hapusPengguna();
    Pengguna* cariPenggunaByNorek(const string& norek);
    Pengguna* autentikasi();
    void penggunaLama(Pengguna* user);
    void back();
    void back2(Pengguna *user);
    void undoTransaksi();
    void antriTransaksi(const string& transaksi);
};

// --- Fungsi Cari Pengguna Berdasarkan Nomor Rekening ---
Bank::Pengguna* Bank::cariPenggunaByNorek(const string& norek) {
    Pengguna* current = head;
    while (current) {
        if (current->norek == norek) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

// --- Fungsi Menu Utama ---
void Bank::menu() {
    int pilihan;
    system("cls");
    cout << "\t\t\t\t\t\tSelamat Datang di Mobile Banking Bersama USU";
    cout << "\n\n1. Gunakan Mobile Banking";
    cout << "\n2. Keluar";
    cout << "\n\nMasukkan pilihan : ";
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            pengaturanATM();
            break;
        case 2:
            exit(0);
        default:
            cout << "\nPilihan tidak valid. Silakan coba lagi.\n";
            menu();
    }
}

// --- Fungsi Pengaturan ATM ---
void Bank::pengaturanATM() {
    int pilihan;
    system("cls");
    cout << "\t\t\t\t\t\tSelamat Datang!";
    cout << "\n\n1. Daftar Akun Baru";
    cout << "\n2. Masuk sebagai Pengguna Lama";
    cout << "\n3. Kembali";
    cout << "\n\nMasukkan pilihan : ";
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            penggunaBaru();
            break;
        case 2: {
            Pengguna* user = autentikasi();
            if (user) {
                penggunaLama(user);
            }
            break;
        }
        case 3:
            menu();
            break;
        default:
            cout << "\nPilihan tidak valid. Silakan coba lagi.\n";
            pengaturanATM();
    }
}

// --- Fungsi Daftar Pengguna Baru ---
void Bank::penggunaBaru() {
    system("cls");
    cout << "\t\t\t\t\t\tPendaftaran Akun Baru\n";

    Pengguna* newPengguna = new Pengguna();
    newPengguna->next = nullptr;

    cout << "Masukkan Nomor Rekening (15 digit)    : ";
    cin >> newPengguna->norek;

    if (newPengguna->norek.length() != 15) {
        cout << "Nomor Rekening harus 15 digit.\n";
        delete newPengguna;
        back();
    }
    else if (cariPenggunaByNorek(newPengguna->norek)) {
        cout << "Nomor Rekening sudah terdaftar.\n";
        delete newPengguna;
        back();
    }

    cin.ignore();
    cout << "Masukkan Nama                         : ";
    getline(cin, newPengguna->nama);

    cout << "Masukkan Alamat                       : ";
    getline(cin, newPengguna->alamat);

    cout << "Masukkan PIN (6 digit)                : ";
    cin >> newPengguna->pin;

    if (newPengguna->pin.length() != 6) {
        cout << "PIN harus 6 digit.\n";
        delete newPengguna;
        back();
        return;
    }

    cout << "Masukkan Nomor Telepon                : ";
    cin >> newPengguna->notel;

    cout << "Masukkan Saldo Awal (minimal Rp50000) : ";
    cin >> newPengguna->saldo;

    if (newPengguna->saldo < 50000) {
        cout << "Saldo minimal adalah Rp50000.\n";
        delete newPengguna;
        back();
        return;
    }

    if (!head) {
        head = newPengguna;
    } else {
        Pengguna* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newPengguna;
    }

    cout << "Pendaftaran berhasil.\n";
    back();
}

// --- Fungsi Autentikasi Pengguna ---
Bank::Pengguna* Bank::autentikasi() {
    system("cls");
    string norek, pin;
    cout << "\t\t\t\t\t\tAutentikasi Pengguna\n";
    cout << "Masukkan Nomor Rekening        : ";
    cin >> norek;
    cout << "Masukkan PIN                   : ";
    cin >> pin;

    Pengguna* user = cariPenggunaByNorek(norek);
    if (user && user->pin == pin) {
        return user;
    } else {
        cout << "Nomor Rekening atau PIN salah.\n";
        back();
        return nullptr;
    }
}

// --- Fungsi Menu Pengguna Lama ---
void Bank::penggunaLama(Pengguna* user) {
    int pilihan;
    system("cls");
    cout << "\t\t\t\t\t\tSelamat Datang, " << user->nama;
    cout << "\n\n1. Deposit";
    cout << "\n2. Penarikan";
    cout << "\n3. Transfer";
    cout << "\n4. Pembayaran";
    cout << "\n5. Tampilkan Informasi Pengguna";
    cout << "\n6. Hapus Akun";
    cout << "\n7. Kembali";
    cout << "\n\nMasukkan pilihan: ";
    cin >> pilihan;

    switch (pilihan) {
        case 1:
            deposit(user);
            break;
        case 2:
            penarikan(user);
            break;
        case 3:
            transfer(user);
            break;
        case 4:
            pembayaran(user);
            break;
        case 5:
            tampilkanInformasi(user);
            break;
        case 6:
            hapusPengguna();
            break;
        case 7:
            pengaturanATM();
            break;
        default:
            cout << "Pilihan tidak valid.\n";
            penggunaLama(user);
    }
}

// --- Fungsi Deposit ---
void Bank::deposit(Pengguna* user) {
    system("cls");
    double jumlah;
    cout << "\t\t\t\t\t\tDeposit\nMasukkan jumlah               : Rp.";
    cin >> jumlah;

    if (jumlah >= 100000) {
        user->saldo += jumlah;
        transaksiHistory.push("Deposit: Rp." + to_string(jumlah));
        cout << "Deposit berhasil. Saldo saat ini: Rp." << fixed << setprecision(0) << user->saldo << "\n";
    } else {
        cout << "Jumlah minimal deposit adalah Rp100000.\n";
    }
    back2(user);
}

// --- Fungsi Penarikan ---
void Bank::penarikan(Pengguna* user) {
    system("cls");
    double jumlah;
    cout << "\t\t\t\t\t\tPenarikan\nMasukkan jumlah               : Rp.";
    cin >> jumlah;

    if (jumlah <= user->saldo - 50000) {
        user->saldo -= jumlah;
        transaksiHistory.push("Penarikan: Rp." + to_string(jumlah));
        cout << "Penarikan berhasil. Saldo saat ini: Rp." << fixed << setprecision(0) << user->saldo << "\n";
    } else {
        cout << "Saldo tidak mencukupi. Minimal saldo tersisa Rp50000.\n";
    }
    back2(user);
}

// --- Fungsi Transfer ---
void Bank::transfer(Pengguna* user) {
    system("cls");
    string norekTujuan;
    double jumlah;
    cout << "\t\t\t\t\tTransfer\n";
    cout << "Masukkan Nomor Rekening Tujuan  : ";
    cin >> norekTujuan;
    cout << "Masukkan Jumlah                : Rp.";
    cin >> jumlah;

    Pengguna* tujuan = cariPenggunaByNorek(norekTujuan);
    if (tujuan && jumlah <= user->saldo - 50000) {
        user->saldo -= jumlah;
        tujuan->saldo += jumlah;
        transaksiHistory.push("Transfer ke " + norekTujuan + ": Rp." + to_string(jumlah));
        cout << "Transfer berhasil. Saldo Anda: Rp." << fixed << setprecision(0) << user->saldo << "\n";
    } else {
        cout << "Transfer gagal. Pastikan saldo mencukupi dan rekening tujuan valid.\n";
    }
    back2(user);
}

// --- Fungsi Pembayaran ---
void Bank::pembayaran(Pengguna* user) {
    system("cls");
    Pembayaran bayar;
    cout << "\t\t\t\t\tPembayaran\n";
    cout << "Masukkan Keterangan            : ";
    cin.ignore();
    getline(cin, bayar.keterangan);
    cout << "Masukkan Jumlah                : Rp.";
    cin >> bayar.jumlah;

    if (bayar.jumlah <= user->saldo - 50000) {
        user->saldo -= bayar.jumlah;
        pembayaranList.push_back(bayar);
        transaksiHistory.push("Pembayaran: " + bayar.keterangan + " Rp." + to_string(bayar.jumlah));
        cout << "Pembayaran berhasil. Saldo Anda: Rp." << fixed << setprecision(0) << user->saldo << "\n";
    } else {
        cout << "Saldo tidak mencukupi.\n";
    }
    back2(user);
}

// --- Fungsi Menampilkan Informasi Pengguna ---
void Bank::tampilkanInformasi(Pengguna* user) {
    system("cls");
    cout << "\t\t\t\t\tInformasi Pengguna\n";
    cout << "Nama                          : " << user->nama << "\n";
    cout << "Nomor Rekening                : " << user->norek << "\n";
    cout << "Alamat                        : " << user->alamat << "\n";
    cout << "Nomor Telepon                 : " << user->notel << "\n";
    cout << "Saldo                         : Rp." << fixed << setprecision(0) << user->saldo << "\n";
    back2(user);
}

// --- Fungsi Hapus Pengguna ---
void Bank::hapusPengguna() {
    system("cls");
    string norek;
    cout << "\t\t\t\t\t\tHapus Akun\nMasukkan Nomor Rekening       : ";
    cin >> norek;

    Pengguna* current = head;
    Pengguna* prev = nullptr;
    while (current) {
        if (current->norek == norek) {
            if (prev) {
                prev->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
            cout << "Akun berhasil dihapus.\n";
            back();
            return;
        }
        prev = current;
        current = current->next;
    }
    cout << "Nomor Rekening tidak ditemukan.\n";
    back();
}

// --- Fungsi Back ---
void Bank::back() {
    cout << "\nTekan tombol apapun untuk kembali...";
    _getch();
    system("cls");
    pengaturanATM();
}

void Bank::back2(Pengguna* user) {
    cout << "\nTekan tombol apapun untuk kembali...";
    _getch();
    system("cls");
    penggunaLama(user);
}

// --- Fungsi Undo Transaksi ---
void Bank::undoTransaksi() {
    if (!transaksiHistory.empty()) {
        cout << "Transaksi terakhir: " << transaksiHistory.top() << " dibatalkan.\n";
        transaksiHistory.pop();
    } else {
        cout << "Tidak ada transaksi yang bisa dibatalkan.\n";
    }
    back();
}

// --- Fungsi Antri Transaksi ---
void Bank::antriTransaksi(const string& transaksi) {
    antrianTransaksi.push(transaksi);
    cout << "Transaksi '" << transaksi << "' telah masuk antrian.\n";
    back();
}

int main() {
    Bank bank;
    bank.menu();
    return 0;
}
