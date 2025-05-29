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

int jmlStaff = 0, jmlMenu = 0, jmlSeat = 0;
string seats[rows][cols],
       jenis[] = {"Appetizer", "Main Course", "Dessert", "Beverage"};
int jmlJenis = sizeof(jenis) / sizeof(jenis[0]);

struct staff{
    string nama, usn, pass;
} dataStaff;

struct temp{
    int baris, kolom;
} tempSeats;

struct menu{
    string nama, jenis;
    int harga;
} dataMenu;

void splitFileDataStaff(string line){
    stringstream ss(line);

    getline(ss, dataStaff.nama, ',');
    getline(ss, dataStaff.usn, ',');
    getline(ss, dataStaff.pass);
}

void splitFileDataSeats(string line){
    string baris, kolom;
    stringstream ss(line);

    getline(ss, baris, ',');
    getline(ss, kolom);

    tempSeats.baris = stoi(baris);
    tempSeats.kolom = stoi(kolom);
}

void splitFileDataMenu(string line){
    string harga;
    stringstream ss(line);
    
    getline(ss, dataMenu.nama, ',');
    getline(ss, dataMenu.jenis, ',');
    getline(ss, harga);

    dataMenu.harga = stoi(harga);
}

void taruhTemp(menu temp[]){
    string line, harga;
    int count = 0;

    ifstream fileRead(fileMenu);
    if (fileRead.is_open()){
        while (getline(fileRead, line)){
            stringstream ss(line);
            getline(ss, temp[count].nama, ',');
            getline(ss, temp[count].jenis, ',');
            getline((ss), harga);
            temp[count].harga = stoi(harga);
            count++;
        }
    }
    fileRead.close();
}

void tampilkanMenu(){

    system("cls");
    int counter = 1;

    menu temp[jmlMenu];
    taruhTemp(temp); 

    menu* ptr = temp; 

    cout << "MENU RESTORAN\n";

    for (int j = 0; j < jmlJenis; j++) {
        cout << endl << jenis[j] << ":\n";

        for (int i = 0; i < jmlMenu; i++) {
            if ((ptr + i)->jenis == jenis[j]) {
                cout << counter << ". " 
                     << (ptr + i)->nama 
                     << " - Rp. " << (ptr + i)->harga << endl;
                counter++;
            }
        }
    }

    cout << endl;
}


void editMenu(){
    int kodeEdit;
    string line, lineKeep;
    bool ulangEdit = 1;

    while (ulangEdit){
        int i = 1;
        system("cls");
        cout << "EDIT MENU\n\n";

        ifstream file(fileMenu);
        if (file.is_open()){
            while(getline(file, line)){
                splitFileDataMenu(line);
                cout << i << ". " << dataMenu.nama << endl; i++;
            }
        }        
        file.close();
        cout << jmlMenu + 1 << ". Keluar\n";
        cout << "\nPilih menu : "; cin >> kodeEdit;

        if (kodeEdit < 0 || kodeEdit > jmlMenu + 1){
            cout << "\nKode tidak valid" << endl;
            system("pause"); system("cls");
        }else if (kodeEdit == jmlMenu + 1){
            ulangEdit = 0;
        }else{
            string nama, temp[jmlMenu];
            int kodeJenis, harga, pilihEdit, count = 0;
            bool ulangPilih = 1;

            ifstream file(fileMenu);
            if (file.is_open()){
                for (int i = 0; i < kodeEdit; i++){
                    getline(file, line);
                    splitFileDataMenu(line);
                }
            }
            file.close();

            while (ulangPilih){
                system("cls");
                cout << "[1] Nama menu : " << dataMenu.nama << endl
                     << "[2] Jenis     : " << dataMenu.jenis << endl
                     << "[3] Harga     : Rp. " << dataMenu.harga << endl
                     << "[4] Keluar\n\n";
                cout << "Pilih edit : "; cin >> pilihEdit; cin.ignore();

                switch (pilihEdit){
                    case 1: cout << "\nNama baru : "; getline(cin, nama); dataMenu.nama = nama; break;
                    case 2:
                        cout << endl;
                        for (int i = 0; i < jmlJenis; i++){
                            cout << i + 1 << ". " << jenis[i] << endl;
                        }
                        cout << "\nJenis baru : "; cin >> kodeJenis;
                        if (kodeJenis < 1 || kodeJenis > jmlJenis){
                            cout << "\nKode tidak valid\n"; system("pause");
                            break;
                        }
                        dataMenu.jenis = jenis[kodeJenis - 1];
                    break;
                    case 3: cout << "\nHarga baru : Rp. "; cin >> harga; dataMenu.harga = harga; break;
                    case 4: ulangPilih = 0; break;
                    default:
                        cout << "Kode tidak valid" << endl;
                        system("pause");
                }
            }

            ifstream fileUpdate(fileMenu);
            if (fileUpdate.is_open()){
                while (getline(fileUpdate, lineKeep)){
                    if (lineKeep != line){
                        temp[count] = lineKeep; count++;
                    }else{
                        temp[count] = dataMenu.nama + "," + dataMenu.jenis + "," + to_string(dataMenu.harga);
                        count++;
                    }
                }
            }
            fileUpdate.close();

            ofstream fileWrite(fileMenu);
            if (fileWrite.is_open()){
                for (int i = 0; i < count; i++){
                    fileWrite << temp[i] << endl;
                }
            }
            fileWrite.close();
        }
    }
}

void hapusMenu(){
    int kodeHapus, count = 0;
    string line, lineDelete, temp[jmlMenu];
    bool ulangHapus = 1;

    while (ulangHapus){
        system("cls");
        int i = 1;
        cout << "HAPUS MENU\n\n";

        ifstream file(fileMenu);
        if (file.is_open()){
            while(getline(file, line)){
                splitFileDataMenu(line);
                cout << i << ". " << dataMenu.nama << endl; i++;
            }
        }        
        file.close();
        cout << jmlMenu + 1 << ". Keluar\n";
        cout << "\nPilih menu : "; cin >> kodeHapus;

        if (kodeHapus < 0 || kodeHapus > jmlMenu + 1){
            cout << "\nKode tidak valid" << endl;
            system("pause"); system("cls");
        }else if (kodeHapus == jmlMenu + 1){
            ulangHapus = 0;
        }else{
            ifstream fileDelete(fileMenu);
                if (fileDelete.is_open()){
                    for (int i = 0; i < kodeHapus; i++){
                        getline(fileDelete, lineDelete);
                    }
                    fileDelete.seekg(0, ios::beg);
                    while(getline(fileDelete, line)){
                        if (line != lineDelete){
                            temp[count] = line; count++;
                        }
                    } 
                }
            fileDelete.close();

            ofstream fileUpdate(fileMenu);
            if (fileUpdate.is_open()){
                for (int i = 0; i < count; i++){
                    fileUpdate << temp[i] << endl;
                }
                cout << "\nMenu telah dihapus\n"; system("pause");
                jmlMenu--;
            }
            fileUpdate.close();            
        }
    }
}

void tambahMenu(){
    system("cls");
    string nama, harga;
    int kodeJenis;
    
    cout << "TAMBAH MENU\n\n";
    cout << "Nama Menu : "; cin.ignore(); getline(cin, nama);

    cout << endl;
    for (int i = 0; i < jmlJenis; i++){
        cout << i + 1 << ". " << jenis[i] << endl;
    }
    cout << "\nJenis     : "; cin >> kodeJenis;
    if (kodeJenis < 1 || kodeJenis > jmlJenis){
        cout << "\nKode tidak valid\n";
        system("pause"); return;
    }

    cout << "Harga     : Rp.  "; cin >> harga;

    ofstream file(fileMenu, ios::app);
    if (file.is_open()){
        cout << setfill(' ');
        file << nama << "," << jenis[kodeJenis - 1] << "," << harga << endl;
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
    ofstream file(fileSeats);
    file.close();
}

void deleteSeat(int &seatSold){
    int baris, kolom, count = 0;
    string temp[rows * cols], line;

    dislplaySeats();
    cout << "\nInput baris & kolom (contoh: 5 7)\n";
    cout << "Pilih kursi : "; cin >> baris >> kolom;

    if ((baris < 1 || baris > rows) && (kolom < 1 || kolom > cols)){
        cout << "\nInput tidak valid\n";
        system("pause");
        return;
    }

    if (seats[baris - 1][kolom - 1] == "|   "){
        cout << "\nKursi sudah kosong\n";
        system("pause");
        return;
    }

    seats[baris - 1][kolom - 1] = "|   ";
    seatSold--;

    ifstream fileDelete(fileSeats);
    if (fileDelete.is_open()){
        while(getline(fileDelete, line)){
            splitFileDataSeats(line);
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

    if ((baris < 1 || baris > rows) && (kolom < 1 || kolom > cols)){
        cout << "\nInput tidak valid\n";
        system("pause");
        return;
    }

    if (seats[baris - 1][kolom - 1] == "| X "){
        cout << "\nKursi sudah terpakai\n\n";
        system("pause");
        return;
    }

    seats[baris - 1][kolom - 1] = "| X ";
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
            splitFileDataSeats(line);
            seats[tempSeats.baris][tempSeats.kolom] = "| X ";
        }
    }
    file.close();
}

void menuReservasi(){
    int kodeSeats, seatSold = 0, temp = seatSold;
    string line;
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
    jmlSeat += seatSold;
    if (seatSold > temp){
        cout << "\nMeja ";
        ifstream file(fileSeats);
        if (file.is_open()){
            for (int i = seatSold; i > 0; i--){
                file.seekg(0, ios::beg);
                for (int j = 0; j <= jmlSeat - i; j++){
                    getline(file, line);
                }
                splitFileDataSeats(line);
                cout << tempSeats.baris + 1 << tempSeats.kolom + 1 << " ";
            }
        }
        file.close();
        cout << "claimed!\n\n";
        system("pause");
    }
}

void sortHarga(bool sort){
    system("cls");
    menu temp[jmlMenu];

    taruhTemp(temp);
    
    for (int i = 0; i < jmlMenu - 1; i++){
        for (int j = 0; j < jmlMenu - 1 - i; j++){
            if (temp[j].jenis == temp[j + 1].jenis){
                bool tukar = sort ?
                        (temp[j].harga > temp[j + 1].harga) :
                        (temp[j].harga < temp[j + 1].harga);
                if (tukar) swap(temp[j].harga, temp[j + 1].harga);
            }
        }
    }

    ofstream fileWrite(fileMenu);
    if (fileWrite.is_open()){
        for (int i = 0; i < jmlMenu; i++){
            fileWrite << temp[i].nama << "," << temp[i].jenis << "," << to_string(temp[i].harga) << endl;
        }
    }
    fileWrite.close();

    if (sort) cout << "Sort Harga Tertinggi\n";
    else cout << "Sort Harga Terendah\n";
    tampilkanMenu();
    system("pause");
}

void searchMenu(bool byJenis) {
    system("cls");
    int kodeJenis;
    bool found = false;
    string keyword;
    menu temp[jmlMenu];

    taruhTemp(temp);

    if (byJenis){
        cout << "Cari Jenis Menu\n\n";
        for (int i = 0; i < jmlJenis; i++){
            cout << i + 1 << ". " << jenis[i] << endl;
        }
        cout << "\nCari : "; cin >> kodeJenis;
        if (kodeJenis < 1 || kodeJenis > jmlJenis){
            cout << "\nKode tidak valid\n";
            system("pause"); return;
        }
        keyword = jenis[kodeJenis - 1];
    }else{
        cout << "Cari Nama Menu\n\n";
        cout << "Cari : "; cin.ignore(); getline(cin, keyword);
    }

    if (byJenis){
        system("cls");
        cout << "Menu " << jenis[kodeJenis - 1] << endl;
    }
    cout << endl;
    for (int i = 0; i < jmlMenu; i++) {
        bool match = byJenis ?
            temp[i].jenis.find(keyword) != string::npos :
            temp[i].nama.find(keyword) != string::npos;
        if (match){
            cout << temp[i].nama << " - Rp. " << temp[i].harga << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "Menu tidak ditemukan";
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
        cout << "CARI MENU\n\n";
        cout << "[1] Berdasarkan Nama\n"
             << "[2] Berdasarkan Jenis\n"
             << "[3] Filter Harga Terendah\n"
             << "[4] Filter Harga Tertinggi\n"
             << "[5] Kembali\n";
        cout << "\nPilih menu : "; cin >> kodeCari;
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
    int total_seluruh = 0;
    string jawab, submit;
    menu temp[jmlMenu];
   
    taruhTemp(temp);

    do{
        int psn = 1, kodePesan[psn][2];

        for (int i = 0; i < psn; i++){
            cout << "Menu Restoran\n";
            tampilkanMenu();
            cout << "Pilih menu   : "; cin >> kodePesan[i][0];
            cout << "Jumlah porsi : "; cin >> kodePesan[i][1];

            if (kodePesan[i][0] > 0 && kodePesan[i][0] <= jmlMenu){
                cout << "\nPesanan berhasil ditambahkan!\n";
                cout << "Tambah pesanan lain? (y/n) : "; cin >> jawab;
                if (jawab == "y" || jawab == "Y") psn++;                
            }else{
                cout << "\nKode tidak valid\n";
                system("pause"); system("cls");
            }
        }
    
        system("cls");
        cout << "FOOD RECEIPT\n";
        for (int i = 0; i < psn; i++) {
            int total_satuan = kodePesan[i][1] * temp[kodePesan[i][0] - 1].harga;
        
            cout << "\nMenu           : " << temp[kodePesan[i][0] - 1].nama;
            cout << "\njumlah pesanan : " << kodePesan[i][1];
            cout << "\nHarga satuan   : Rp. " << temp[kodePesan[i][0] - 1].harga;
            cout << "\nTotal          : Rp. " << total_satuan << endl;
            total_seluruh += total_satuan;
        
        }
        if (psn > 1) cout << "\nTotal seluruh  : Rp. " << total_seluruh << endl;
        cout << endl;

        cout << "Pesanan sudah benar? (y/n) : "; cin >> submit;
    }while (!(submit == "y" || submit == "Y"));
}

void menuPesan(){
    system("cls");
    int kodeMenu;
    bool ulangMenu = 1;

    while (ulangMenu){
        system("cls");
        cout << "MENU PEMESANAN\n";
        cout << "\n[1] Lihat Menu"
             << "\n[2] Pesan Menu"
             << "\n[3] Cari Menu"
             << "\n[4] Keluar\n";
        cout << "\nPilih menu : "; cin >> kodeMenu;

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
        cout << "SISTEM RESTORAN SAMBODEX DINER\n";
        cout << "\n[1] Pesan Menu"
             << "\n[2] Reservasi Meja"
             << "\n[3] Manage Menu"
             << "\n[4] Keluar\n";
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
        for (int i = 0; i < jmlStaff; i++){
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
        system("cls");
        cout << "SISTEM RESTORAN SAMBODEX DINER\n";
        cout << "\n[1] Masuk"
             << "\n[2] Daftar"
             << "\n[3] Keluar\n";
        cout << "\nPilih menu : "; cin >> kodeMasuk;

        switch (kodeMasuk){
            case 1: login(ulangMasuk, limitLogin); break;
            case 2: signup(); break;
            case 3: ulangMasuk = 0; break;
            default:
                cout << "\nKode tidak valid\n";
                system("pause");
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

    ifstream fileM(fileMenu);
    if (fileM.is_open()){
        while (getline(fileM, line)){
            jmlMenu++;
        }
    }
    fileM.close();

    ifstream seat(fileSeats);
    if (seat.is_open()){
        while (getline(seat, line)){
            jmlSeat++;
        }
    }
    seat.close();
    
    menuMasuk();
}