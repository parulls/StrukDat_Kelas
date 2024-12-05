#include <iostream>
#include <iomanip>
#include <conio.h>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class bank {
private:
    struct pengguna {
        string pin, norek, nama, alamat, notel;
        double saldo;
    };
    struct hal_pembayaran {
        string norek, keterangan;
        double jumlah, saldo;
    };

    pengguna penggunaList[100];
    vector<hal_pembayaran> pembayaranList;
    stack<string> transaksi;
    queue<pengguna> penggunaQueue;
    int penggunaCount;
    int pembayaranCount;

public:
    bank() {
        penggunaCount = 0;
        pembayaranCount = 0;
    }
    void menu();
    void pengaturan_atm();
    void pengguna_baru();
    void pengguna_lama();
    void deposit();
    void penarikan();
    void transfer();
    void pembayaran();
    void edit_informasi_pengguna();
    void hapus_pengguna();
    void tampilkan_informasi_pengguna();
    void tampilkan_pembayaran();
    void cek_kode_pin();
    void back();
};

void bank::menu() {
    opsi:
    int pilihan;
    system("cls");
    cout << "\t\t\tMobile Banking Bersama USU";
    cout << "\n\n1. Gunakan Mobile Banking";
    cout << "\n2. Keluar";
    cout << "\n\nMasukkan pilihan : ";
    cin >> pilihan;

    switch (pilihan) {
    case 1:
        pengaturan_atm();
        break;
    case 2:
        exit(0);
    default:
        cout << "\n\n\t\t\tTidak Ada Pilihan Yang Sesuai. Silahkan Coba Lagi.";
        goto opsi;
        break;
    }
}

void bank::pengaturan_atm() {
    opsi:
    int pilihan;
    system("cls");
    cout << "\t\t\t\t\tSelamat Datang!!";
    cout << "\n\n1. Daftar Akun Baru";
    cout << "\n2. Sudah Punya Akun? Masuk Disini!";
    cout << "\n3. Kembali";
    cout << "\n\nMasukkan Pilihan : ";
    cin >> pilihan;
    switch (pilihan) {
    case 1:
        pengguna_baru();
        break;
    case 2:
        cek_kode_pin();
        break;
    case 3:
        menu();
        break;
    default:
        cout << "\n\n\t\t\tTidak Ada Pilihan Yang Sesuai. Silahkan Coba Lagi.";
        goto opsi;
        break;
    }
}

void bank::pengguna_baru() {
    system("cls");
    cout << "\t\t\t\tMenu Pengguna Baru";
    opsi:
    pengguna p;
    cout << "\n\nDaftarkan Nomor Rekening Pengguna\t : ";
    cin >> p.norek;
    if (p.norek.length() != 15) {
        cout << "\n\t\t\tNomor Rekening Harus 15 Digit\n";
        goto opsi;
    }
    for (int i = 0; i < penggunaCount; i++) {
        if (penggunaList[i].norek == p.norek) {
            cout << "\n\t\t\t\tNomor Rekening Pengguna Sudah Pernah Digunakan\n.";
            goto opsi;
        }
    }
    cout << "Nama Pengguna\t\t\t\t : ";
    cin.ignore();
    getline(cin, p.nama);
    cout << "Alamat\t\t\t\t\t : ";
    getline(cin, p.alamat);
    cout << "Kode Pin (6 Digit)\t\t\t : ";
    cin >> p.pin;
    if (p.pin.length() != 6) {
        cout << "\n\t\t\tPin Harus 6 Digit";
        goto opsi;
    }
    cout << "Nomor Telepon\t\t\t\t : ";
    cin >> p.notel;
    cout << "Saldo Terkini\t\t\t\t : Rp.";
    cin >> p.saldo;

    if (p.saldo >= 50000) {
        penggunaList[penggunaCount++] = p;
        penggunaQueue.push(p);
        cout << "\n\n\t\t\tPendaftaran Akun Pengguna Baru Berhasil.";
        cout << "\n\n\t\t\tSilahkan Masuk Kembali Untuk Menggunakan Mobile Banking.";
    } else {
        cout << "\t\t\tMinimal Saldo Pengguna Baru adalah Rp50000\n";
        goto opsi;
    }

    cout << "\n\nTekan tombol apapun untuk kembali...";
    getch();
    pengaturan_atm();
}

void bank::pengguna_lama() {
    opsi:
    system("cls");
    int pilihan;
    cout << "\t\t\t\tMenu Penggunaan Mobile Banking";
    cout << "\n1. Deposit";
    cout << "\n2. Penarikan";
    cout << "\n3. Transfer";
    cout << "\n4. Pembayaran";
    cout << "\n5. Struk Pembayaran";
    cout << "\n6. Edit Informasi Pengguna";
    cout << "\n7. Tampilkan Informasi Pengguna";
    cout << "\n8. Hapus Akun Pengguna";
    cout << "\n9. Kembali";
    cout << "\n\nMasukkan Pilihan : ";
    cin >> pilihan;
    switch (pilihan) {
    case 1:
        deposit();
        break;
    case 2:
        penarikan();
        break;
    case 3:
        transfer();
        break;
    case 4:
        pembayaran();
        break;
    case 5:
        tampilkan_pembayaran();
        break;
    case 6:
        edit_informasi_pengguna();
        break;
    case 7:
        tampilkan_informasi_pengguna();
        break;
    case 8:
        hapus_pengguna();
        break;
    case 9:
        pengaturan_atm();
        break;
    default:
        cout << "\n\nTidak Ada Pilihan Yang Sesuai. Silahkan Coba Lagi.";
        goto opsi;
        break;
    }
}

void bank::deposit() {
    system("cls");
    double dep;
    cout << "\t\t\t\tMenu Deposit";
    cout << "\n\nJumlah Deposit\t\t\t\t : Rp.";
    cin >> dep;

    for (int i = 0; i < penggunaCount; i++) {
        if (dep >= 100000) {
            penggunaList[i].saldo += dep;
            transaksi.push("Deposit: Rp." + to_string(dep));
            cout << "\n\n\t\t\tSaldo Sebesar Rp." << fixed << setprecision(0) << dep << " Berhasil Ditambahkan!";
            cout << "\n\n\t\t\tSaldo Terkini : Rp." << fixed << setprecision(0) << penggunaList[i].saldo;
            back();
        } else {
            cout << "Minimal Deposit adalah Rp.100000\n";
            back();
        }
    }
}

void bank::penarikan() {
    system("cls");
    double tarik;
    cout << "\t\t\tMenu Penarikan";
    cout << "\n\nJumlah Penarikan\t\t\t : Rp.";
    cin >> tarik;

    for (int i = 0; i < penggunaCount; i++) {
        if (tarik <= (penggunaList[i].saldo - 50000)) {
            penggunaList[i].saldo -= tarik;
            transaksi.push("Penarikan: Rp." + to_string(tarik));
            cout << "\n\n\t\t\tSaldo Sebesar Rp." << fixed << setprecision(0) << tarik << " Berhasil Ditarik!";
            cout << "\n\n\t\t\tSaldo Terkini : Rp." << fixed << setprecision(0) << penggunaList[i].saldo;
            back();
        } else {
            cout << "\n\n\t\t\tSaldo Anda Tidak Mencukupi.";
            cout << "\n\n\t\t\tSaldo Terkini : Rp." << fixed << setprecision(0) << penggunaList[i].saldo;
            back();
        }
    }
}

void bank::transfer() {
    system("cls");
    string kirimnorek, terimanorek;
    double transfer;
    cout << "\t\t\tMenu Transfer";
    cout << "\n\nNomor Rekening Anda\t\t\t : ";
    cin >> kirimnorek;
    cout << "Nomor Rekening Penerima\t\t\t : ";
    cin >> terimanorek;
    cout << "Jumlah Transfer\t\t\t\t : ";
    cin >> transfer;

    bool kirimnorekFound = false;
    bool terimanorekFound = false;

    for (int i = 0; i < penggunaCount; i++) {
        if (transfer <= (penggunaList[i].saldo - 50000)) {
            if (penggunaList[i].norek == kirimnorek) {
                penggunaList[i].saldo -= transfer;
                kirimnorekFound = true;
            }
            if (penggunaList[i].norek == terimanorek) {
                penggunaList[i].saldo += transfer;
                terimanorekFound = true;
            }
        } else cout << "\nSaldo Anda Tidak Mencukupi.";
    }

    if (kirimnorekFound && terimanorekFound) {
        transaksi.push("Transfer: Rp." + to_string(transfer) + " to " + terimanorek);
        cout << "\n\n\t\t\tTransfer berhasil!";
    } else {
        cout << "\n\nNomor Rekening Anda/Penerima Tidak Ditemukan.";
    }
    back();
}

void bank::pembayaran() {
    system("cls");
    hal_pembayaran q;
    cout << "\t\t\tMenu Pembayaran";
    cout << "\n\nKeterangan\t\t\t\t : ";
    cin.ignore();
    getline(cin, q.keterangan);
    cout << "Jumlah Pembayaran\t\t\t : Rp.";
    cin >> q.jumlah;

    for (int i = 0; i < penggunaCount; i++) {
        if (q.jumlah <= (penggunaList[i].saldo - 50000)) {
            penggunaList[i].saldo -= q.jumlah;
            transaksi.push("Pembayaran: Rp." + to_string(q.jumlah) + " for " + q.keterangan);
            cout << "\n\n\t\t\tPembayaran Berhasil!";
            cout << "\n\n\t\t\tSaldo Terkini : Rp." << fixed << setprecision(0) << penggunaList[i].saldo;
            pembayaranList.push_back(q);
            back();
        } else {
            cout << "\n\n\t\t\tSaldo Anda Tidak Mencukupi.";
            cout << "\n\n\t\t\tSaldo Terkini : Rp." << fixed << setprecision(0) << penggunaList[i].saldo;
            back();
        }
    }
}

void bank::tampilkan_informasi_pengguna() {
    system("cls");
    cout << "\t\t\tMenu Tampilkan Informasi Pengguna";
    for (int i = 0; i < penggunaCount; i++) {
        cout << "\n\n\n***********************************************************************";
        cout << "\n\nNomor Rekening\t\t\t\t : " << penggunaList[i].norek;
        cout << "\nNama Pengguna\t\t\t\t : " << penggunaList[i].nama;
        cout << "\nAlamat\t\t\t\t\t : " << penggunaList[i].alamat;
        cout << "\nKode Pin\t\t\t\t : " << penggunaList[i].pin;
        cout << "\nNomor Telepon\t\t\t\t : " << penggunaList[i].notel;
        cout << "\nSaldo Terkini\t\t\t\t : " << fixed << setprecision(0) << penggunaList[i].saldo;
        cout << "\n\n\n***********************************************************************";
    }
    if (penggunaCount == 0) {
        cout << "\n\nData Pengguna Tidak Ditemukan.";
        back();
    }
    back();
}

void bank::edit_informasi_pengguna() {
    system("cls");
    string n, a, nt, pn;
    cout << "\t\t\tMenu Edit Informasi Pengguna";

    for (int i = 0; i < penggunaCount; i++) {
        cout << "\n\nNama Pengguna\t\t\t\t : ";
        cin.ignore();
        getline(cin, n);
        cout << "Alamat\t\t\t\t\t : ";
        getline(cin, a);
        cout << "Kode Pin (6 Digit)\t\t\t : ";
        cin >> pn;
        cout << "Nomor Telepon\t\t\t\t : ";
        cin >> nt;

        penggunaList[i].nama = n;
        penggunaList[i].alamat = a;
        penggunaList[i].pin = pn;
        penggunaList[i].notel = nt;

        cout << "\n\n\t\t\tData Berhasil Diubah!";
        back();
    }
}

void bank::hapus_pengguna() {
    system("cls");
    string pin;
    char ch;
    cout << "\t\t\tMenu Hapus Pengguna";
    cout << "\n\nKode PIN\t\t\t\t\t\t : ";
    cin >> pin;
    cout << "Apakah Anda Yakin Ingin Menghapus Akun Anda? (Y/N)\t : ";
    cin >> ch;

    for (int i = 0; i < penggunaCount; i++) {
        if (penggunaList[i].pin == pin && (ch == 'Y' || ch == 'y')) {
            for (int j = i; j < penggunaCount - 1; j++) {
                penggunaList[j] = penggunaList[j + 1];
            }
            penggunaCount--;
            pengaturan_atm();
            break;
        } else if (ch == 'N' || ch == 'n') {
            back();
            break;
        }
    }
}

void bank::tampilkan_pembayaran() {
    system("cls");
    cout << "\t\t\tMenu Tampilkan Pembayaran";
    for (int i = 0; i < pembayaranList.size(); i++) {
        cout << "\n\n\n***********************************************************************";
        cout << "\n\nKeterangan\t\t\t\t : " << pembayaranList[i].keterangan;
        cout << "\nJumlah Pembayaran\t\t\t : Rp." << fixed << setprecision(0) << pembayaranList[i].jumlah;
        cout << "\n\n\n***********************************************************************";
    }
    if (pembayaranList.size() == 0) {
        cout << "\n\nData Pembayaran Tidak Ditemukan.";
        back();
    }
    back();
}

void bank::cek_kode_pin() {
    system("cls");
    string norek, pin;
    hal_pembayaran q;
    cout << "\t\t\t\tMasukkan Nomor Rekening dan Kode PIN";
    cout << "\n\nNomor Rekening\t\t\t\t : ";
    cin >> norek;
    cout << "Kode PIN\t\t\t\t : ";
    cin >> pin;

    bool found = false;

    for (int i = 0; i < penggunaCount; i++) {
        if ((penggunaList[i].norek == norek || pembayaranList[i].norek == q.norek) && penggunaList[i].pin == pin) {
            found = true;
            break;
        }
    }

    if (found) {
        pengguna_lama();
    } else {
        cout << "\n\nNomor Rekening Tidak Ditemukan atau Kode PIN Salah.";
        back();
    }
}


void bank::back() {
    cout << "\n\nTekan tombol apapun untuk kembali...";
    getch();
    pengguna_lama();
}

int main() {
    bank b;
    bank* bPtr = &b;
    bPtr->menu();
}
