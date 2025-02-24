#include <iostream>
using namespace std;

struct {
    string nama, usn, pass;
} pelanggan[100];

void home(){
    system("cls");
    cout << "SELAMAT DATANG DI RESTORAN X\n\n";
    // lanjut
    system("pause"); system("cls");
}

void login(int &daftar){
    string nama, usn, pass;
    bool ulangMasuk = 1;
    
    do{
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
        }       
    } while (ulangMasuk);
}

void signup(int &daftar){
    bool ulangDaftar;
    do{
        ulangDaftar = 0;
        system("cls");
        cout << "DAFTAR\n\n";
        cout << "Nama     : "; cin.ignore(); getline(cin, pelanggan[daftar].nama);
        cout << "Username : "; cin >> pelanggan[daftar].usn;
        cout << "Password : "; cin >> pelanggan[daftar].pass;

        for (int i = 0; i < daftar; i++){
            if (pelanggan[daftar].usn == pelanggan[i].usn){
                cout << "\nUsername tidak tersedia\n";
                ulangDaftar = 1;
                system("pause"); system("cls");
            }
        }
    } while (ulangDaftar);
    cout << "\nBerhasil daftar\n";
    daftar++;
    system("pause"); system("cls");
}

main (){
    int kodeMasuk, daftar = 0;

    while (true){
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
                cout << "Kode tidak valid\n";
                system("pause"); system("cls");
        }
    }
}