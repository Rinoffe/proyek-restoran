#include <iostream>
#include <cstring>
using namespace std;

struct {
    string nama, usn, pass;
} pelanggan[100];

struct {
    string nama, jenis;
    int porsi, harga;
} menuRestoran[] = {
    {"Nasi Goreng Kampung", "Main Course", 50, 28000},
    {"Ayam Penyet Sambal Terasi", "Main Course", 50, 35000},
    {"Sate Ayam Madura", "Appetizer", 50, 30000},
    {"Salad Buah Yogurt", "Appetizer", 50, 18000},
    {"Mie Ayam Jamur", "Main Course", 50, 22000},
    {"Es Teler", "Dessert", 50, 15000},
    {"Pancake Nutella", "Dessert", 50, 28000},
    {"Teh", "Beverage", 100, 10000},
    {"Jus Jeruk", "Beverage", 100, 12000}
};
int jmlMenu = sizeof(menuRestoran) / sizeof(menuRestoran[0]);

void tampilkanMenu(){
    int counter = 1;

    cout << "\nAppetizer\n";
    for (int i = 0; i < jmlMenu; i++){
        if (menuRestoran[i].jenis == "Appetizer"){
            cout << counter << ". " << menuRestoran[i].nama << " @ Rp. " << menuRestoran[i].harga << endl;
            counter++;
        }
    }
    cout << "\nBeverage\n";
    for (int i = 0; i < jmlMenu; i++){
        if (menuRestoran[i].jenis == "Beverage"){
            cout << counter << ". " << menuRestoran[i].nama << " @ Rp. " << menuRestoran[i].harga << endl;
            counter++;
        }
    }
    cout << "\nDessert\n";
    for (int i = 0; i < jmlMenu; i++){
        if (menuRestoran[i].jenis == "Dessert"){
            cout << counter << ". " << menuRestoran[i].nama << " @ Rp. " << menuRestoran[i].harga << endl;
            counter++;
        }
    }
    cout << "\nMain Course\n";
    for (int i = 0; i < jmlMenu; i++){
        if (menuRestoran[i].jenis == "Main Course"){
            cout << counter << ". " << menuRestoran[i].nama << " @ Rp. " << menuRestoran[i].harga << endl;
            counter++;
        }
    }
    cout << endl;
}

void reservasi(int &jmlReservasi){

}

void hargaSort(int kodeCari){
    system("cls");
    for (int i = 0; i < jmlMenu - 1; i++){
        for (int j = 0; j < jmlMenu - 1 - i; j++){
            if (menuRestoran[j].jenis == menuRestoran[j + 1].jenis){
                if (kodeCari == 4){
                    if (menuRestoran[j].harga < menuRestoran[j + 1].harga){
                        swap(menuRestoran[j], menuRestoran[j + 1]);
                    }
                }else if (menuRestoran[j].harga > menuRestoran[j + 1].harga){
                    swap(menuRestoran[j], menuRestoran[j + 1]);
                }
            }
        }
    }

    if (kodeCari == 4){
        cout << "Sort Harga Tertinggi\n";
    }else{
        cout << "Sort Harga Terendah\n";
    }
    tampilkanMenu();
    system("pause");
}

void byJenis(){
    bool found = false;
    int counter = 1;
    string keyword;
    
    system("cls");
    cout << "Cari Jenis Menu\n\n";
    cout << "Cari : "; cin.ignore(); getline(cin, keyword);
    cout << endl;

    for (int i = 0; i < jmlMenu; i++){
        if (menuRestoran[i].jenis.find(keyword) != string::npos){
            cout << counter << ". " << menuRestoran[i].nama
                 << " @ Rp. " << menuRestoran[i].harga << endl;
            counter++;
            found = true;
        }
    }

    if (!found) {
        cout << "\nMenu tidak ditemukan\n";
    }
    cout << endl;
    system("pause");
}

void byNama(){
    bool found = false;
    string keyword;
    int counter = 1;
    
    system("cls");
    cout << "Cari Nama Menu\n\n";
    cout << "Cari : "; cin.ignore(); getline(cin, keyword);
    cout << endl;

    for (int i = 0; i < jmlMenu; i++){
        if (menuRestoran[i].nama.find(keyword) != string::npos){
            cout << counter << ". " << menuRestoran[i].nama
                 << " @ Rp. " << menuRestoran[i].harga << endl;
            counter++;
            found = true;
        }
    }

    if (!found) {
        cout << "\nMenu tidak ditemukan\n";
    }
    cout << endl;
    system("pause");
}

void cariMenu(){
    int kodeCari;
    bool ulangCari = 1;

    while (ulangCari){
        cout << "Cari Menu\n\n";
        cout << "[1] Berdasarkan Nama\n"
             << "[2] Berdasarkan Jenis\n"
             << "[3] Filter Harga Terendah\n"
             << "[4] Filter Harga Tertinggi\n"
             << "[5] Kembali\n";
        cout << "Pilih menu : "; cin >> kodeCari;
        switch (kodeCari){
            case 1:
                byNama();
            break;
            case 2:
                byJenis();
            break;
            case 3:
                hargaSort(kodeCari);
            break;
            case 4:
                hargaSort(kodeCari);
            break;
            case 5:
                ulangCari = 0;
            break;
            default:
                cout << "\nKode tidak valid\n";
                system("pause");
        }
        system("cls");
    }
}
int kodePesan, jmlPesan;


    
void tambahPesan(){
    int kodePesan[100];
    int jmlPesan[100];
    bool ulangPesan = 1;
    int psn = 1;
   
        for(int i = 0; i < psn;i++){
        tampilkanMenu();
        cout << "Pesan Menu\n\n";
        cout << "Pilih menu : "; cin >> kodePesan[i];
        cout << "Jumlah porsi : "; cin >> jmlPesan[i];
        if (kodePesan[i] > 0 && kodePesan[i] <= jmlMenu){
            cout << "\nBerhasil pesan " << menuRestoran[kodePesan[i] - 1].nama
                 << " sebanyak " << jmlPesan[i] << endl;
                
            system("pause");
            system("cls");
        }else{
            cout << "\nKode tidak valid\n";
            system("pause");
            system("cls");
        }
    cout << "\nPesanan anda berhasil ditambahkan\n";
    cout << "tambahkan pesanan lain? (y/n) : ";
    char jawab;
    cin >> jawab;
    if (jawab == 'y' || jawab == 'Y'){
        psn++;
        
    }else{
        cout << "\nPesanan anda berhasil ditambahkan\n";
    
    }
    system("cls");
    }
 
    // Tampilkan rekap seluruh pesanan
    int total;
    cout << "\nRekap Pesanan Anda:\n";
    cout << "==========================\n";
    for (int i = 0; i < psn; i++) {
        int total_harga = jmlPesan[i] * menuRestoran[kodePesan[i] - 1].harga;
       
        cout << "nama : " <<  menuRestoran[kodePesan[i] - 1].nama<<endl;
        cout << "harga pesanan : " << menuRestoran[kodePesan[i] - 1].harga<<endl;
        cout << "jumlah pesanan : " << jmlPesan[i]<<endl;
        cout << "total harga pesanan : "<<total_harga<<endl;
        total += total_harga;
        cout << " "<< endl;
    
    }
    cout << "total harga pesanan : "<< total <<endl;
    cout << " "<< endl;
    cout << "==========================\n";
    system("pause");

}

void sortByJenis(){
    for (int i = 0; i < jmlMenu - 1; i++){
        for (int j = 0; j < jmlMenu - 1 - i; j++){
            if (menuRestoran[j].jenis[0] > menuRestoran[j + 1].jenis[0]){
                swap(menuRestoran[j], menuRestoran[j + 1]);
            }
        }
    }
}

void menu(int jmlReservasi){
    if (jmlReservasi == 0){
        cout << "Anda belum reservasi kursi\n";
        system("pause");
    }else{
        int kodeMenu;
        bool ulangMenu = 1;

        while (ulangMenu){
            sortByJenis();
            cout << "Menu Restoran\n\n";
            cout << "[1] Lihat Menu\n"
                 << "[2] Pesan\n"
                 << "[3] Cari Menu\n"
                 << "[4] Keluar\n";
            cout << "Pilih menu : "; cin >> kodeMenu;

            switch (kodeMenu){
                case 1:
                    system("cls");
                    cout << "Menu Restoran\n";
                    tampilkanMenu();
                    system("pause");
                break;
                case 2:
                    system("cls");
                    cout << "Menu Restoran\n";
                    tambahPesan();
                break;
                case 3:
                    system("cls");
                    cariMenu();
                break;
                case 4:
                    ulangMenu = 0;
                break;
                default:
                    cout << "\nKode tidak valid\n";
                    system("pause");
            }
            system("cls");
        }
    }
}

void home(){
    int kodeHome, jmlReservasi = 1;
    bool ulangHome = 1;
    
    while (ulangHome){
        system("cls");
        cout << "SELAMAT DATANG DI RESTORAN X\n\n";
        cout << "[1] Pesan Menu\n";
        cout << "[2] Reservasi Kursi\n";
        cout << "[3] Feedback\n";
        cout << "[4] Kembali\n";
        cout << "Pilih: "; cin >> kodeHome;

        switch (kodeHome){
            case 1:
                system("cls");
                menu(jmlReservasi);
            break;
            case 2:
                reservasi(jmlReservasi);
            break;
            case 3:
                
            break;
            case 4:
                ulangHome = 0;
            break;
            default:
                cout << "\nKode tidak valid\n";
                system("pause");
        }
        system("cls");
    }
}

void login(int daftar, bool &ulangMasuk, int limitLogin){
    string nama, usn, pass;
    bool ulangLogin = 1, admin = 0;

    if (limitLogin == 0){
        ulangMasuk = 0;
        cout << "\nLimit login anda habis\n";
        system("pause");
    }else{
        system("cls");
        cout << "MASUK\n\n";
        cout << "Username : "; cin >> usn;
        cout << "Password : "; cin >> pass;

        if (usn == "admin" && pass == "admin123"){
            ulangLogin = 0; admin = 1;
            cout << "lanjut";
        }else{
            for (int i = 0; i < daftar; i++){
                if ((usn == pelanggan[i].usn) && (pass == pelanggan[i].pass)){
                    cout << "\nBerhasil masuk\n";
                    system("pause");
                    ulangLogin = 0;
                    home();
                }
            }
        }
    
        if ((ulangLogin) && (daftar != 0)){
            cout << "\nLogin gagal, kesempatan anda tersisa " << limitLogin - 1 << endl;
            system("pause");
            login(daftar, ulangMasuk, limitLogin - 1);
        }else if ((daftar == 0) && (!admin)){
            cout << "\nBelum ada pengguna yang terdaftar, mohon daftar terlebih dahulu\n";
            system("pause"); system("cls");
        }      
    }  
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
    }while (ulangDaftar);

    if (!ulangDaftar){
        cout << "\nBerhasil daftar\n";
        daftar++;
        system("pause"); system("cls");
    }    
}

void masuk(int daftar){
    int kodeMasuk, limitLogin = 5;
    bool ulangMasuk = 1;

    while (ulangMasuk){
        cout << "SELAMAT DATANG DI RESTORAN X\n\n";
        cout << "[1] Masuk\n";
        cout << "[2] Daftar\n";
        cout << "[3] Keluar\n";
        cout << "Pilih : "; cin >> kodeMasuk;

        switch (kodeMasuk){
            case 1:
                login(daftar, ulangMasuk, limitLogin);
            break;
            case 2:
                signup(daftar);
            break;
            case 3:
                ulangMasuk = 0;
            break;
            default:
                cout << "\nKode tidak valid\n";
                system("pause"); system("cls");
        }
    }
}

main(){
    int daftar = 0;
    masuk(daftar);
    home();
}