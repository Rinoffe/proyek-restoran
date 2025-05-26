#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;

const int rows = 6, cols = 8;
const string fileStaff = "data_staff.csv",
             fileSeats = "data_seats.csv",
             fileMenu = "data_menu.csv";

int jmlStaff = 0, jmlMenu = 0;

string seats[rows][cols];

struct staff{
    string nama, usn, pass;
} dataStaff;

struct temp{
    int baris, kolom;
} tempSeats;

struct menu{
    string nama, jenis;
    int harga;
} menuRestoran;

void splitFileDataStaff(string line){
    string nama, usn, pass;
    stringstream ss(line);

    getline(ss, nama, ',');
    getline(ss, usn, ',');
    getline(ss, pass);

    dataStaff.nama = nama;
    dataStaff.usn = usn;
    dataStaff.pass = pass;
}

void splitDataSeats(string line){
    string baris, kolom;
    stringstream ss(line);

    getline(ss, baris, ',');
    getline(ss, kolom, ',');

    tempSeats.baris = stoi(baris);
    tempSeats.kolom = stoi(kolom);
}

void tampilkanMenu(){
    system("cls");
    int counter = 1;
    cout << "Menu Restoran\n";

    cout << "\nAppetizer\n";
    for (int i = 0; i < jmlMenu; i++){
        if (menuRestoran.jenis == "Appetizer"){
            cout << counter << ". " << menuRestoran.nama << " @ Rp. " << menuRestoran.harga << endl;
            counter++;
        }
    }
    cout << "\nBeverage\n";
    for (int i = 0; i < jmlMenu; i++){
        if (menuRestoran.jenis == "Beverage"){
            cout << counter << ". " << menuRestoran.nama << " @ Rp. " << menuRestoran.harga << endl;
            counter++;
        }
    }
    cout << "\nDessert\n";
    for (int i = 0; i < jmlMenu; i++){
        if (menuRestoran.jenis == "Dessert"){
            cout << counter << ". " << menuRestoran.nama << " @ Rp. " << menuRestoran.harga << endl;
            counter++;
        }
    }
    cout << "\nMain Course\n";
    for (int i = 0; i < jmlMenu; i++){
        if (menuRestoran.jenis == "Main Course"){
            cout << counter << ". " << menuRestoran.nama << " @ Rp. " << menuRestoran.harga << endl;
            counter++;
        }
    }
    cout << endl;
}

void hapusMenu(){
    
}

void tambahMenu(){
    system("cls");
    string nama, jenis, harga;
    int kodeJenis;
    
    cout << "TAMBAH MENU\n\n";
    cout << "Nama Menu : "; cin.ignore(); getline(cin, nama);
    cout << "\n[1] Main Course"
         << "\n[2] Appetizer"
         << "\n[3] Dessert"
         << "\n[4] Beverage";
    cout << "Jenis     : "; cin >> kodeJenis;
    switch (kodeJenis) {
            case 1: jenis = "Main Course"; break;
            case 2: jenis = "Appetizer"; break;
            case 3: jenis = "Dessert"; break;
            case 4: jenis = "Beverage"; break;
            default:
                cout << "\nKode tidak valid\n";
                system("pause");
                return;
        }
    cout << "Harga     : Rp.  "; cin >> harga;

    ofstream file(fileMenu, ios::app);
    if (file.is_open()){
        cout << setfill(' ');
        file << nama << ","
             << jenis << ","
             << harga << endl;

        cout << "\nMenu berhasil ditambahkan\n";
        jmlMenu++;
        system("pause");
    }
    file.close();
}

void menuManage(){
    int kodeManage;
    bool ulangManage = 1;

    while (ulangManage){
        system("cls");

        updateMenu();
        cout << "MANAGE MENU\n";
        cout << "[1] Tambah Menu\n"
             << "[2] Hapus Menu\n"
             << "[3] Edit Menu\n"
             << "[4] Keluar\n\n";
        cout << "Pilih kode : "; cin >> kodeManage;

        switch (kodeManage){
            case 1: tambahMenu(); break;
            case 2: hapusMenu(); break;
            case 3: editMenu(); break;
            case 4: ulangManage = 0; break;
            default:
                cout << "Kode menu tidak valid" << endl;
                system("pause");
        }
    }
}

void dislplaySeats(){
    system ("cls");

    cout << "RESERVASI MEJA\n\n";
    cout << "    ";
    for (int i = 0; i < cols; i++){
        cout << "  " << i + 1 << " ";
    }
    cout << "\n\n    " << setfill('-') << setw(cols * 4 + 1) << "" << endl;
    for (int i = rows; i > 0; i--){
        cout << i << (i > 9 ? "  " : "   ");
        for (int j = 0; j < cols; j++){
            cout << seats[i - 1][j];
        }
        cout << "|" << endl;
        cout << "    " << setfill('-') << setw(cols * 4 + 1) << "" << endl;
    }
}

void deleteAllSeat(int &seatSold){
    seatSold = 0;

    ofstream fileReset(fileSeats);
    fileReset.close();
}

void deleteSeat(int &seatSold){
    int baris, kolom, count = 0;
    string temp[rows * cols], line;

    dislplaySeats();
    cout << "\nInput baris & kolom (contoh: 5 7)\n";
    cout << "Pilih kursi : "; cin >> baris >> kolom;

    if (seats[baris - 1][kolom - 1] == "|   "){
        cout << "\nKursi sudah kosong\n";
        system("pause");
        return;
    }

    seats[baris - 1][kolom - 1] == "|   ";
    seatSold--;

    ifstream fileDelete(fileSeats);
    if (fileDelete.is_open()){
        while(getline(fileDelete, line)){
            splitDataSeats(line);
            if (!(tempSeats.baris == baris - 1 && tempSeats.kolom == kolom - 1)){
                temp[count] = line; count++;
            }
        } 
    }
    fileDelete.close();

    ofstream fileUpdate(fileSeats);
    if (fileUpdate.is_open()){
        for (int i = 0; i < count; i++){
            fileUpdate << temp[i] << endl;
        }
    }
    fileUpdate.close();
}

void addSeat(int &seatSold){
    int baris, kolom;

    dislplaySeats();
    cout << "\nInput baris & kolom (contoh: 5 7)\n";
    cout << "Pilih kursi : "; cin >> baris >> kolom;

    if (seats[baris - 1][kolom - 1] == "| X "){
        cout << "\nKursi sudah terpakai\n\n";
        system("pause");
        return;
    }

    seats[baris - 1][kolom - 1] == "| X ";
    seatSold++;

    ofstream file(fileSeats, ios::app);
    if (file.is_open()){
        file << to_string(baris - 1) << ","
             << to_string(kolom - 1) << endl;
    }
    file.close();
}

void updateSeats(){
    string line;

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            seats[i][j] = "|   ";
        }
    }

    ifstream file(fileSeats);
    if (file.is_open()){
        while (getline(file, line)){
            splitDataSeats(line);
            seats[tempSeats.baris][tempSeats.kolom] = "| X ";
        }
    }
    file.close();
}

void menuReservasi(){
    int kodeSeats, seatSold = 0, temp = seatSold;
    bool ulangSeats = 1;

    while (ulangSeats){
        updateSeats();
        dislplaySeats();
        cout << "\n[1] Tambah meja"
             << "\n[2] Hapus meja"
             << "\n[3] Hapus semua"
             << "\n[4] Keluar\n";
        cout << "\nPilih menu: "; cin >> kodeSeats;

        switch (kodeSeats){
            case 1: addSeat(seatSold); break;
            case 2: deleteSeat(seatSold); break;
            case 3: deleteAllSeat(seatSold); break;
            case 4: ulangSeats = 0; break;
            default:
                cout << "Kode menu tidak valid" << endl;
                system("pause");
        }
    }
    if (seatSold > temp){
        
    }
}

void sortHarga(bool sort){
    system("cls");
    bool tukar;
    
    for (int i = 0; i < jmlMenu - 1; i++){
        for (int j = 0; j < jmlMenu - 1 - i; j++){
            if (menuRestoran[j].jenis == menuRestoran[j + 1].jenis){
                tukar = sort ?
                        (menuRestoran[j].harga > menuRestoran[j + 1].harga) :
                        (menuRestoran[j].harga < menuRestoran[j + 1].harga);
            }
        }
    }

    if (sort) cout << "Sort Harga Tertinggi\n";
    else cout << "Sort Harga Terendah\n";
    tampilkanMenu();
    system("pause");
}

void searchMenu(bool byJenis) {
    system("cls");
    bool found = false;
    string keyword;
    int counter = 1;

    if (byJenis){
        int kodeJenis;
        cout << "Cari Jenis Menu\n";
        cout << "\n[1] Main Course"
             << "\n[2] Appetizer"
             << "\n[3] Dessert"
             << "\n[4] Beverage";
        cout << "\nCari : "; cin >> kodeJenis;
        cout << endl;

        switch (kodeJenis) {
            case 1: keyword = "Main Course"; break;
            case 2: keyword = "Appetizer"; break;
            case 3: keyword = "Dessert"; break;
            case 4: keyword = "Beverage"; break;
            default:
                cout << "\nKode tidak valid\n";
                system("pause");
                return;
        }
    }else{
        cout << "Cari Nama Menu\n\n";
        cout << "Cari : "; cin.ignore(); getline(cin, keyword);
        cout << endl;
    }

    for (int i = 0; i < jmlMenu; i++) {
        bool match = byJenis ?
            menuRestoran.jenis.find(keyword) != string::npos :
            menuRestoran.nama.find(keyword) != string::npos;

        if (match){
            cout << counter << ". " << menuRestoran.nama
                 << " @ Rp. " << menuRestoran.harga << endl;
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

void menuCari(){
    system("cls");
    int kodeCari;
    bool ulangCari = 1;

    while (ulangCari){
        system("cls");
        cout << "Cari Menu\n\n";
        cout << "[1] Berdasarkan Nama\n"
             << "[2] Berdasarkan Jenis\n"
             << "[3] Filter Harga Terendah\n"
             << "[4] Filter Harga Tertinggi\n"
             << "[5] Kembali\n";
        cout << "Pilih menu : "; cin >> kodeCari;
        switch (kodeCari){
            case 1: searchMenu(0); break;
            case 2: searchMenu(1); break;
            case 3: sortHarga(1); break;
            case 4: sortHarga(0); break;
            case 5: ulangCari = 0; break;
            default:
                cout << "\nKode tidak valid\n";
                system("pause");
        }
    }
}
    
void tambahPesan(){
    system("cls");
    int psn = 1, kodePesan[psn], jmlPesan[psn], total_seluruh = 0; 
    char jawab;
   
    for (int i = 0; i < psn; i++){
        cout << "Menu Restoran\n";
        tampilkanMenu();
        cout << "Pilih menu   : "; cin >> kodePesan[i];
        cout << "Jumlah porsi : "; cin >> jmlPesan[i];

        if (kodePesan[i] > 0 && kodePesan[i] <= jmlMenu){
            cout << "\nPesanan berhasil ditambahkan!\n";
            cout << "Tambah pesanan lain? (y/n) : "; cin >> jawab;

            if (jawab == 'y' || jawab == 'Y') psn++;
            system("cls");

        }else{
            cout << "\nKode tidak valid\n";
            system("pause"); system("cls");
        }
    }
 
    // cetak receipt
    cout << "\nFOOD RECEIPT\n";
    for (int i = 0; i < psn; i++) {
        int total_satuan = jmlPesan[i] * menuRestoran[kodePesan[i] - 1].harga;
       
        cout << "\nMenu           : " << menuRestoran[kodePesan[i] - 1].nama;
        cout << "\njumlah pesanan : " << jmlPesan[i];
        cout << "\nHarga satuan   : Rp. " << menuRestoran[kodePesan[i] - 1].harga;
        cout << "\nTotal          : Rp. " << total_satuan << endl;
        total_seluruh += total_satuan;
    
    }
    if (psn > 1) cout << "\nTotal seluruh  : Rp. " << total_seluruh << endl;
    cout << endl;
    system("pause");
}

void updateMenu(){
    for (int i = 0; i < jmlMenu - 1; i++){
        for (int j = 0; j < jmlMenu - 1 - i; j++){
            if (menuRestoran[j].jenis[0] > menuRestoran[j + 1].jenis[0]){
                swap(menuRestoran[j], menuRestoran[j + 1]);
            }
        }
    }
}

void menuPesan(){
    system("cls");
    int kodeMenu;
    bool ulangMenu = 1;

    while (ulangMenu){
        system("cls");
        updateMenu();
        cout << "\n[1] Lihat Menu"
             << "\n[2] Pesan"
             << "\n[3] Cari Menu"
             << "\n[4] Keluar\n";
        cout << "Pilih menu : "; cin >> kodeMenu;

        switch (kodeMenu){
            case 1: tampilkanMenu(); system("pause"); break;
            case 2: tambahPesan(); break;
            case 3: menuCari(); break;
            case 4: ulangMenu = 0; break;
            default:
                cout << "\nKode tidak valid\n";
                system("pause");
        }
    }    
}

void menuUtama(){
    int kodeHome;
    bool ulangHome = 1;
    
    while (ulangHome){
        system("cls");
        cout << "SELAMAT DATANG DI RESTORAN X\n";
        cout << "\n[1] Pesan Menu"
             << "\n[2] Reservasi Meja"
             << "\n[3] Manage Menu"
             << "\n[4] Kembali\n";
        cout << "\nPilih menu : "; cin >> kodeHome;

        switch (kodeHome){
            case 1: menuPesan(); break;
            case 2: menuReservasi(); break;
            case 3: menuManage(); break;
            case 4: ulangHome = 0; break;
            default:
                cout << "\nKode tidak valid\n";
                system("pause");
        }
    }
}

void login(bool &ulangMasuk, int limitLogin){
    string usn, pass, line;
    bool ulangLogin = 1, terdaftar = 0;

    if (jmlStaff == 0) {
        cout << "\nBelum ada pengguna yang terdaftar, mohon daftar terlebih dahulu\n";
        system("pause");
        return;
    }

    if (limitLogin == 0){
        ulangMasuk = 0;
        return;
    }

    system("cls");
    cout << "MASUK\n\n";
    cout << "Username : "; cin >> usn;
    cout << "Password : "; cin >> pass;

    ifstream file(fileStaff);
    if (file.is_open()){
        for (int i = 0; i <= jmlStaff; i++){
            getline(file, line);
            splitFileDataStaff(line);
            if (usn == dataStaff.usn && pass == dataStaff.pass){
                cout << "\nBerhasil masuk\n";
                ulangLogin = 0;
                system("pause");
                menuUtama();
            }        
            if (usn == dataStaff.usn) terdaftar = 1;
        }    

        if (ulangLogin){
            if (!terdaftar){
                cout << "\nUsername Anda belum terdaftar, mohon daftar terlebih dahulu\n";
                system("pause");
                return;
            }
            cout << "\nLogin gagal, kesempatan Anda tersisa " << limitLogin - 1 << endl;
            system("pause");
            login(ulangMasuk, limitLogin - 1);
        }
    }
}

void signup(){
    string line;
    string nama, usn, pass;

    system("cls");
    cout << "DAFTAR\n\n";
    cout << "Nama     : "; cin.ignore(); getline(cin, nama);
    cout << "Username : "; cin >> usn;
    cout << "Password : "; cin >> pass;

    ifstream fileRead(fileStaff);
    if (fileRead.is_open()){
        for (int i = 0; i < jmlStaff; i++){
            getline(fileRead, line);
            splitFileDataStaff(line);
            if (usn == dataStaff.usn) {
                cout << "\nUsername tidak tersedia. Silakan coba username lain.\n";
                system("pause");
                return;
            }
        }
    }
    fileRead.close();

    ofstream fileWrite(fileStaff, ios::app);
    if (fileWrite.is_open()){
        fileWrite << nama << "," << usn << "," << pass << endl;
        cout << "\nBerhasil daftar\n";
        jmlStaff++;
        system("pause");
    }
    fileWrite.close();
}

void menuMasuk(){
    int kodeMasuk, limitLogin = 5;
    bool ulangMasuk = 1;

    while (ulangMasuk){
        cout << "SELAMAT DATANG DI RESTORAN X\n";
        cout << "\n[1] Masuk"
             << "\n[2] Daftar\n"
             << "\n[3] Keluar\n";
        cout << "\nPilih menu : "; cin >> kodeMasuk;

        switch (kodeMasuk){
            case 1:
                login(ulangMasuk, limitLogin);
            break;
            case 2:
                signup();
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
    string line;

    ifstream fileS(fileStaff);
    if (fileS.is_open()){
        while (getline(fileS, line)){
            jmlStaff++;
        }
    }
    fileS.close();

    ifstream fileF(fileMenu);
    if (fileF.is_open()){
        while (getline(fileF, line)){
            jmlMenu++;
        }
    }
    fileF.close();

    // menuMasuk();
    // menuPesan();
    menuUtama();
}