#include <iostream>
using namespace std;

struct {
    string nama, usn, pass;
} pelanggan[100];

void home(){
    int kodeHome;
    
        system("cls");
        cout << "SELAMAT DATANG DI RESTORAN X\n\n";
        cout << "[1] Pesan Menu\n";
        cout << "[2] Reservasi Kursi\n";
        cout << "[3] Feedback\n";
        cout << "[4] Kembali\n";
        cout << "Pilih: "; cin >> kodeHome;
        switch (kodeHome){
            case 1:
                home();
            break;
            case 2:
                home();
            break;
            case 3:
                home();
            break;
            case 4:
                system("cls");
            break;
            default:
                cout << "\nKode tidak valid\n";
                system("pause"); system("cls");
                home();
        }
}

void login(int &daftar){
    string nama, usn, pass;
    bool ulangMasuk = 1;
    
        system("cls");
        cout << "MASUK\n\n";
        cout << "Username : "; cin >> usn;
        cout << "Password : "; cin >> pass;

        for (int i = 0; i < daftar; i++){
            if ((usn == pelanggan[i].usn) && (pass == pelanggan[i].pass)){
                cout << "\nBerhasil masuk\n"; system("pause");
                ulangMasuk = 0;
                home();
            }
        }

        if (ulangMasuk){
            cout << "\nGagal masuk\n";
            system("pause"); system("cls");
            login(daftar);
        }
}

void signup(int &daftar){
        system("cls");
        cout << "DAFTAR\n\n";
        cout << "Nama     : "; cin.ignore(); getline(cin, pelanggan[daftar].nama);
        cout << "Username : "; cin >> pelanggan[daftar].usn;
        cout << "Password : "; cin >> pelanggan[daftar].pass;

        for (int i = 0; i < daftar; i++){
            if (pelanggan[daftar].usn == pelanggan[i].usn){
                cout << "\nUsername tidak tersedia\n";
                system("pause"); system("cls");
                signup(daftar);
            }
        }
    
    cout << "\nBerhasil daftar\n";
    daftar++;
    system("pause"); system("cls");
}

void masuk(int daftar){
    int kodeMasuk;

    cout << "SELAMAT DATANG DI RESTORAN X\n\n";
    cout << "[1] Masuk\n";
    cout << "[2] Daftar\n";
    cout << "Pilih : "; cin >> kodeMasuk;

    switch (kodeMasuk){
        case 1:
            if (daftar == 0){
                cout << "\nBelum ada pengguna yang terdaftar, mohon daftar terlebih dahulu\n";
                system("pause"); system("cls");
            }else{
                login(daftar);
            }
        break;
        case 2:
            signup(daftar);
        break;
        default:
            cout << "\nKode tidak valid\n";
            system("pause"); system("cls");
    }
    masuk(daftar);
}

main(){
    int daftar = 0;
    masuk(daftar);
}