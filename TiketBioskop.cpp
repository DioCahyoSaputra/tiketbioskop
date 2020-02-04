#include <iostream>
#include <bits/stdc++.h>
#include <string.h>
#define max 25
using namespace std;
typedef struct typequeue *typeptr;
struct FILM{
	bool KondisiKursi[max];
	int JumlahTiketTerjual = 0;
	char JudulFilm[30];
}film[3];

typedef struct{
    char Nama[20], NIK[20];
    int PosisiAntrian;
}daftar;
struct typequeue{
    daftar info;
    typeptr kanan;
};
typeptr awal, akhir, Cek;
daftar antrian;
int JumlahData = 0, JumlahAntri = 0, HargaTiket = 35000;
bool cekBeliTiket;
double total, TotalPemasukkan = 0;

void buatqueue();
int queuekosong();
void enqueue(daftar IB);
void dequeue();
void hapusbelakang();
void menu();
void jadwalTayang();
void kursiVenom();
void kursiOverload();
void kursiBOHEMIAN();

int main()
{
	menu();	
	return 0;
}

void menu(){
	int pilih,pilih3;
	char kembali;
	buatqueue();
	do{
		system("cls");//clear screen	
		cout << "--------MENU--------\n\n";
		cout<<"1. Cek Kursi\n2. Daftar Antrian\n3. Panggil Antrian\n4. Batal Antrian\n5. Laporan Penjualan Tiket\n6. Keluar\nPilihan Anda :";cin>>pilih;
		switch(pilih){
			case 1:
				//pengecekkan kursi masih ada slot atau penuh
				jadwalTayang();
				cout << "Cek Film apa? ";cin >> pilih;
				cout << "\n\n";
				switch(pilih){
					case 1:
						kursiVenom();
						break;
					case 2:
						kursiOverload();	
						break;
					case 3:
						kursiBOHEMIAN();
						break;
					default:
						cout << "\nTidak ada dalam pilihan!";
				}
			break;
			case 2:
				//pendaftaran antrian sebelum membeli tiket 
                JumlahAntri+=1;
                JumlahData+=1;
                cout << "\nAntrian ke-"<<JumlahAntri;
                antrian.PosisiAntrian = JumlahAntri;
                cin.ignore();
                cout << "\nNama \t: ";cin.getline(antrian.Nama,20);
                cout << "NIK \t: ";cin >>antrian.NIK;
                enqueue(antrian);
				break;
			case 3:
				//panggilan antrian atau proses pembelian tiket
			cekBeliTiket = false;
			if(queuekosong())
				cout << "Belum Masuk Antrian";
			else{
			Cek = awal;
			cout << "\nAntrian ke-" << Cek -> info.PosisiAntrian;
			cout << "\nAtas Nama :\n";
			cout << "   " << Cek -> info.Nama<<endl;
			cout << "   " << Cek -> info.NIK;
			do{
			jadwalTayang();
			cout<< "4. Batal Pembelian\n";
			cout<<"Film Pilihan Anda : ";cin>>pilih3;
			system("cls");
			int JumlahTiket,NomorKursi;
			bool cek;
			switch(pilih3){
				case 1:
				if(film[pilih3 - 1].JumlahTiketTerjual == max){
					cout << "\nMaaf Kursi Penuh!\n";
				}
				else{
				cout<<"\nJudul Film\t: "<<film[pilih3-1].JudulFilm;
				cout<< "\n\n";
					kursiVenom();
					cout<<"\nJumlah Tiket\t: ";cin>>JumlahTiket;
					for(int i = 0; i<JumlahTiket; i++){
					cout << "Kursi Nomor : ";cin >> NomorKursi;
						if(film[pilih3 - 1].KondisiKursi[NomorKursi] == true){
							cout << "\nMaaf Kursi sudah dipesan!\n\n";
							i--;
						}
						else{
						film[pilih3 - 1].KondisiKursi[NomorKursi] = true;
						}
					}
					total= HargaTiket * JumlahTiket;
					TotalPemasukkan+=total;
					cout<<"\nTotal Harga\t: Rp. "<<total;
					film[pilih3 - 1].JumlahTiketTerjual+=JumlahTiket;
					dequeue();
					JumlahData--;
                	cekBeliTiket = true;
                }
					break;
				case 2:
					if(film[pilih3 - 1].JumlahTiketTerjual == max){
					cout << "\nMaaf Kursi Penuh!\n";
					}
					else{
					cout<<"\nJudul Film\t: "<<film[pilih3-1].JudulFilm;
					cout<< "\n\n";
					kursiOverload();
					cout<<"\nJumlah Tiket\t: ";cin>>JumlahTiket;
					for(int i = 0; i<JumlahTiket; i++){
						cout << "Kursi Nomor : ";cin >> NomorKursi;
						if(film[pilih3 - 1].KondisiKursi[NomorKursi] == true){
							cout << "\nMaaf Kursi sudah dipesan!\n\n";
							i--;
						}
						else{
						film[pilih3 - 1].KondisiKursi[NomorKursi] = true;
						}
					}
					total= HargaTiket * JumlahTiket;
					TotalPemasukkan+=total;
					film[pilih3 - 1].JumlahTiketTerjual+=JumlahTiket;
					cout<<"\nTotal Harga\t: Rp. "<<total;
					dequeue();
					JumlahData--;
                	cekBeliTiket = true;
                }
					break;
				case 3:
					if(film[pilih3 - 1].JumlahTiketTerjual == max){
					cout << "\nMaaf Kursi Penuh!\n";
				}
				else{
					cout<<"\nJudul Film\t: "<<film[pilih3-1].JudulFilm;
					cout<< "\n\n";
					kursiBOHEMIAN();
					cout<<"\nJumlah Tiket\t: ";cin>>JumlahTiket;
					for(int i = 0; i<JumlahTiket; i++){
						cout << "Kursi Nomor : ";cin >> NomorKursi;
						if(film[pilih3 - 1].KondisiKursi[NomorKursi] == true){
							cout << "\nMaaf Kursi sudah dipesan!\n\n";
							i--;
						}
						else{
						film[pilih3 - 1].KondisiKursi[NomorKursi] = true;
						}
					}
					total= HargaTiket * JumlahTiket;
					TotalPemasukkan+=total;
					film[pilih3 - 1].JumlahTiketTerjual+=JumlahTiket;
					cout<<"\nTotal Harga\t: Rp. "<<total;
					dequeue();
					JumlahData--;
                	cekBeliTiket = true;
                }
					break;
				case 4:
					//pembatalan pembelian tiket
					dequeue();
					JumlahData--;
					break;
				default:
					cout << "\nMaaf Tidak ada Dalam Pilihan!";
				}
			}while(pilih3 != 4 && cekBeliTiket == false);
			}
			break;
			case 4:
				//pembatalan antrian atau keluar dari antrian
				if(JumlahData == 0){
					cout<<"\nAntrian Masih Kosong!\n\n";
				}
				else if(JumlahData == 1){
					Cek = awal;
					cout << "\nAntrian ke-" << Cek -> info.PosisiAntrian;
					cout << "\nKeluar Dari Antrian!\n";
					dequeue();
					JumlahData--;
					}
					else {
						Cek = akhir;
						cout << "\nAntrian ke-" << Cek -> info.PosisiAntrian;
						cout << "\nKeluar Dari Antrian!\n";
						hapusbelakang();
						JumlahData--;
					}
				break;
			case 5:
				//laporan penjualan tiket sementara/akhir
				cout << "\nLaporan Penjualan Hari Ini :\n";
				cout << "\n------VENOM------\n\n";
				cout << "Jumlah Tiket Terjual : " << film[0].JumlahTiketTerjual;
				cout << "\n\n------OVERLOAD------\n\n";
				cout << "Jumlah Tiket Terjual : " << film[1].JumlahTiketTerjual;
				cout << "\n\n------BOHEMIAN RAPHSODY------\n\n";
				cout << "Jumlah Tiket Terjual : " << film[2].JumlahTiketTerjual;
				cout << "\n\nTotal Pemasukkan : Rp. " << TotalPemasukkan;
			break;
			case 6:
				break;
			default :
			cout<<"Pilihan anda salah, mohon ulangi";
			cout<<endl;
		}
		cout<<endl<<endl;
		cout<<"Kembali ke menu ? (y/n)";cin>>kembali;
	}while(kembali=='Y'||kembali=='y'); 
}	

//list jadwal film
void jadwalTayang(){
	cout<<"\n------ Jadwal Tayang Hari Ini -----\n";
	strcpy(film[0].JudulFilm,"VENOM (15.30)");
	strcpy(film[1].JudulFilm,"OVERLORD (18.00)");
	strcpy(film[2].JudulFilm,"BOHEMIAN RAPHSODY (20.00)");
	for(int a=0;a<3;a++){
		cout<<endl<<a+1<<". "<<film[a].JudulFilm;
	}
		cout<<endl;
}

//output kursi yg tersedia pada film VENOM
void kursiVenom(){
	int Jumlah = 1, Kursi = 1;
	cout << setw(18) << "[LAYAR]\n\n";
	for(int i=0;i<5;i++){
		for(int j = 0; j < 5; j++){				
				cout<<setw(5) << Jumlah;		
				Jumlah++;
			}
		cout << endl;
		for(int k = 0; k < 5; k++){
			if(!film[0].KondisiKursi[Kursi])
				cout << setw(5) << "[0]";
			else
				 cout << setw(5) << "[1]";
			Kursi++;
		}
		cout << endl;
	}
	cout<<"\n\t0 = kosong\n\t1 = terisi";
	cout<<endl<<endl;
}

//output kursi yg tersedia pada film OVERLOAD
void kursiOverload(){
	int Jumlah = 1, Kursi = 1;
	cout << setw(18) << "[LAYAR]\n\n";
	for(int i=0;i<5;i++){
		for(int j = 0; j < 5; j++){				
				cout<<setw(5) << Jumlah;		
				Jumlah++;
			}
		cout << endl;
		for(int k = 0; k < 5; k++){
			if(!film[1].KondisiKursi[Kursi])
				cout << setw(5) << "[0]";
			else
				 cout << setw(5) << "[1]";
			Kursi++;
		}
		cout << endl;
	}
	cout<<"\n\t0 = kosong\n\t1 = terisi";
	cout<<endl<<endl;
}

//output kursi yg tersedia pada film BOHEMIAN
void kursiBOHEMIAN(){
	int Jumlah = 1, Kursi = 1;
	cout << setw(18) << "[LAYAR]\n\n";
	for(int i=0;i<5;i++){
		for(int j = 0; j < 5; j++){				
				cout<<setw(5) << Jumlah;		
				Jumlah++;
			}
		cout << endl;
		for(int k = 0; k < 5; k++){
			if(!film[2].KondisiKursi[Kursi])
				cout << setw(5) << "[0]";
			else
				 cout << setw(5) << "[1]";
			Kursi++;
		}
		cout << endl;
	}
	cout<<"\n\t0 = kosong\n\t1 = terisi";
	cout<<endl<<endl;
}

//pembuatan antrian baru
void buatqueue(){
    awal = (typequeue*)malloc(sizeof(typequeue));
    awal = NULL;
    akhir = awal;
}

//pengecekkan jika antrian kosong
int queuekosong()
{
    if(awal == NULL)
        return (true);
    else
        return(false);
}

//pemasukkan data antrian
void enqueue(daftar IB)
{

    typeptr NS, bantu;
    NS = (typequeue*)malloc(sizeof(typequeue));
    NS -> info = IB;
    NS -> kanan = NULL;
    if(awal == NULL){
        awal = NS;
    }
    else
    	awal -> kanan = NS;
    akhir = NS;
    akhir -> kanan = NULL;
}

//penghapusan data antrian dari depan
void dequeue()
{
    typeptr hapus;
    if(queuekosong())
        cout << "\n\nAntrian Kosong\n";
    else
    {
        hapus = awal;
        awal = hapus -> kanan;
        free(hapus);
        }
}

//penghapusan data antrian dari belakang
void hapusbelakang()
{
    typeptr hapus, bantu;
    if(queuekosong())
        cout << "\n\nAntrian Kosong\n";
    else
    {
        bantu = awal;
        hapus = akhir;
        while(bantu -> kanan != akhir)
        	bantu = bantu -> kanan;
        bantu = akhir;
        akhir -> kanan = NULL;
        free(hapus);
        }
}
