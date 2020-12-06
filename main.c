/*
 *===========DASLAUNDRY============ 
 * 
 * Program Laundry Berbasis Terminal
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Prototype fungsi untuk bersihkan layar tiap masuk ke sebuah menu dapat berfungsi di Linux, Mac OS dan Windows
void clearscrn();

// Prototype prosedur untuk admin	
void loginadmin(); 		// Untuk masuk ke user admin
void menuadmin(); 		// Menu pilihan admin
void hapuspesanan();	// Hapus pesanan yang sudah di-update
void daftarpesanan();	// Melihat semua daftar pesanan yang sudah dibuat user
void statusdanharga();	// Memberi harga pada pesanan user tertentu serta memperbarui status pesanan
void daftaruser();		// Melihat seluruh daftar user
void searching();		// Melihat semua daftar user yang sudah registrasi

// Prototype prosedur untuk user
void loginuser(); 		// Untuk login akun yang sudah teregistrasi
void userbaru(); 		// Membuat user baru
void menuuser();		// Menu user
void pesananbaru();		// Membuat pesanan baru
void cekkonfir(); 		// Cek konfirmasi pesanan dari admin

// Deklarasi struct
struct tgl{
        char berat[10];
        int tanggal;
        char namauser[30];
        int harga;
        char status[40];
} datapesanan, temp[100], tempx[100];
struct user{
	char namauser[30];
	char sandiuser[40];
}  listuser;

// Variabel
char admuser[20], nameuser[30];
char admpasswd[40], passuser[40];
char status[30], buatbaru[2], userlog[30], pilihuser[30];
int temp2;
int i, n, j, a;
FILE *fadmin;
FILE *flistuser;
FILE *fdatapesanan;
FILE *fbackdatapesanan;
FILE *fdatapesanan2;
FILE *fdatapesanan3;

// FUNGSI UTAMA
int main(){
	int log;
	puts("==================================");
    puts("            DASLAUNDRY            ");
    puts("==================================");
    // Pembuat file kosong jika belum ada saat program mulai untuk mencegah error
    flistuser = fopen("daftaruser.dat", "ab");
    fdatapesanan = fopen("datapesanan.dat", "ab");
    fdatapesanan2 = fopen("datapesanan2.dat", "ab");
    fclose(flistuser);
    fclose(fdatapesanan);
    fclose(fdatapesanan2);
    // Menu utama terdapat pilihan login sebagai user atau admin serta pilihan untuk keluar dari program
    puts("Selamat datang di Daslaundry");
    puts("Menu Login");
    puts("Login sebagai :");
    puts("1. Admin");
    puts("2. User");
    puts("3. Registrasi User");
    puts("4. Keluar dari program");
    printf("Masukkan pilihan : ");scanf("%d", &log);
    getchar();
    switch (log)
    {
    case 1:
        clearscrn();loginadmin();
        break;
    case 2:
        clearscrn();loginuser();
        break;
    case 3:
        clearscrn();userbaru();
        break;
	  case 4:
		exit(0);
		break;
    default:
        puts("Pilihan salah!");
        getchar();
        clearscrn();
        main();
    }
}
// Fungsi penghapus layar terminal yang dapat dijalankan di Windows, Linux, dan MacOS
void clearscrn(){
	if(system("cls") != 0){
		system("clear");
	}
	else{
		system("cls");
	}
}
// FITUR ADMIN

// Kolom Login Admin
void loginadmin(){
    char useradmin[30];
    char adminpass[40];
    printf("Username : ");gets(useradmin); 
    printf("Password : ");gets(adminpass); 
	if(strcmp(useradmin, "admin") == 0 && strcmp(adminpass, "123") == 0){
		menuadmin();
	}
	puts("Username dan Password salah!");
	getchar();
	loginadmin();
}

// Menu kontrol admin
void menuadmin(){
    int admpilih; 
    clearscrn();
    puts("==================================");
    puts("           MENU ADMIN             ");
    puts("==================================");
    puts("1. Beri harga pada pesanan dan update status pada pesanan");
    puts("2. Daftar user");
    puts("3. Daftar pesanan");
    puts("4. Hapus pesanan yang sudah selesai");
    puts("5. Cari banyak pesanan berdasarkan tanggal");
    puts("6. Logout");
    printf("Masukkan pilihan : ");scanf("%d", &admpilih);
    switch (admpilih){
    case 1:
       clearscrn();statusdanharga();
        break;
    case 2:
        clearscrn();daftaruser();
        break;
    case 3:
        clearscrn();daftarpesanan();
        break;
    case 4:
        clearscrn();hapuspesanan();
        break;
    case 5:
		clearscrn();searching();
        break;
    case 6:
    	clearscrn();main();
    	break;
    default:
        puts("Pilihan salah!");
        menuadmin();
    }
}

// Melihat daftar user yang terdaftar
void daftaruser(){
    n = 0;
    flistuser = fopen("daftaruser.dat", "rb");
	while(fread(&listuser,sizeof(listuser),1,flistuser) == 1){
            n += 1;
			printf("%d. Nama Pengguna : %s\n", n, listuser.namauser);
		}
    if(n > 0){
        printf("Total User yang terdaftar : %d", n);
    }
    else{
        puts("Belum ada user yang terdaftar!");
    }
    fclose(flistuser);getchar();getchar();
    menuadmin();
}

// Melihat daftar pesanan user yang telah disorting 
void daftarpesanan(){
    char temp2nama[30], temp2berat[10], temp2status[40], temp2xnama[30];
    i = 0;
    puts("=========DAFTAR PESANAN USER=========");
    puts("DAFTAR PESANAN YANG BELUM SELESAI");
    fdatapesanan = fopen("datapesanan.dat", "rb");
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan) == 1){
       strcpy(temp[i].namauser, datapesanan.namauser);
       strcpy(temp[i].berat, datapesanan.berat);
       strcpy(temp[i].status, datapesanan.status);
       temp[i].tanggal = datapesanan.tanggal;
        i++;
        n = i;
    }
    fclose(fdatapesanan);
    if(n>0){
		for(i=0; i<n; i++){
			for(j=0;j<n-i-1;j++){
				if(temp[j].tanggal>temp[j+1].tanggal){
					temp2 = temp[j].tanggal;
					strcpy(temp2xnama, temp[j].namauser);
					strcpy(temp2berat, temp[j].berat);
					strcpy(temp2status, temp[j].status);
					temp[j].tanggal = temp[j+1].tanggal;
					strcpy(temp[j].namauser, temp[j+1].namauser);
					strcpy(temp[j].berat, temp[j+1].berat);
					strcpy(temp[j].status, temp[j+1].status);
					temp[j+1].tanggal = temp2;
					strcpy(temp[j+1].namauser, temp2xnama);
					strcpy(temp[j+1].berat, temp2berat);
					strcpy(temp[j+1].status, temp2status);
				}
			}
		}
		for(i=0 ;i<n ;i++){
			printf("%d. Nama : %s Berat (Kg): %s Tanggal : %d\n Status : %s\n", i+1, temp[i].namauser, temp[i].berat, temp[i].tanggal, temp[i].status);
		}
    }
     else{
        puts("Belum ada pesanan!");
    }
    puts("=====================================");
    puts("DAFTAR PESANAN YANG SUDAH SELESAI");
    fdatapesanan2 = fopen("datapesanan2.dat", "rb");
    i=0;
    n=0;
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan2)==1){
        strcpy(tempx[i].namauser, datapesanan.namauser);
        strcpy(tempx[i].berat, datapesanan.berat);
        strcpy(tempx[i].status, datapesanan.status);
        tempx[i].harga = datapesanan.harga;
        tempx[i].tanggal = datapesanan.tanggal;
        i++;
        n=i;
    }
    fclose(fdatapesanan2);
    if (n>0){
        for(i=0 ;i<n ;i++){
			for(j=0 ;j<n-i-1 ;j++){
				if(tempx[j].tanggal>tempx[j+1].tanggal){
					temp2 = tempx[j].tanggal;
					strcpy(temp2nama, tempx[j].namauser);
					strcpy(temp2berat, tempx[j].berat);
					strcpy(temp2status, tempx[j].status);
					tempx[j].tanggal = tempx[j+1].tanggal;
					strcpy(tempx[j].namauser, tempx[j+1].namauser);
					strcpy(tempx[j].berat, tempx[j+1].berat);
					strcpy(tempx[j].status, tempx[j+1].status);
					tempx[j+1].tanggal = temp2;
					strcpy(tempx[j+1].namauser, temp2nama);
					strcpy(tempx[j+1].berat, temp2berat);
					strcpy(tempx[j+1].status, temp2status);
				}
            }
        }
		for(i=0 ;i<n ;i++){
			printf("%d. Nama : %s Berat (Kg): %s Tanggal : %d\n Status : %s\n", i+1, tempx[i].namauser, tempx[i].berat, tempx[i].tanggal, tempx[i].status);
		}
    }
    else{
        puts("Belum ada pesanan yang selesai!");
    }

    getchar();getchar();
    menuadmin();
}

// Memberikan harga secara manual kepada user yang melakukan pesanan 
void statusdanharga(){
    int harga;
    char konfirm[40] = "Menunggu Konfirmasi";
    i = 0;
    fdatapesanan = fopen("datapesanan.dat", "rb");
    puts("Daftar pesanan yang belum dikonfirmasi dan diberi harga");
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1){
       if(strcmp(datapesanan.status, konfirm) == 0){
       i += 1;
       printf("%d. Nama : %s Berat %s Tanggal %d\n Status : %s\n", i,datapesanan.namauser, datapesanan.berat, datapesanan.tanggal, datapesanan.status);
       }
    }
    fclose(fdatapesanan);
    puts("1. Pilih pesanan untuk diberi harga dan update");
    puts("2. Kembali");
    printf("Masukkan pilihan : ");scanf("%d", &a);
    getchar();
    switch (a)
    {
    case 1:
        break;
    case 2 :
        menuadmin();
        break;
    default:
        statusdanharga();
    }
    if(i>0){
        printf("Pilih pesanan yang akan diupdate dan diberi harga berdasarkan nama user : ");fgets(pilihuser, sizeof(pilihuser), stdin);
        printf("Masukkan harga : ");scanf("%d", &harga);
        fdatapesanan2 = fopen("datapesanan2.dat", "ab");
        fdatapesanan = fopen("datapesanan.dat", "rb");
        fdatapesanan3 = fopen("datapesanan3.dat", "ab");
        while(fread(&datapesanan, sizeof(datapesanan), 1, fdatapesanan) == 1){
			if(strcmp(datapesanan.namauser, pilihuser) == 0){
				datapesanan.harga = harga;
				strcpy(datapesanan.status, "Pesanan selesai");
				fwrite(&datapesanan, sizeof(datapesanan), 1, fdatapesanan2);
			}
        }
        fclose(fdatapesanan);
        fdatapesanan = fopen("datapesanan.dat", "rb");
        while(fread(&datapesanan ,sizeof(datapesanan), 1, fdatapesanan) == 1){
			if(strcmp(datapesanan.namauser,pilihuser)!=0){
				fwrite(&datapesanan, sizeof(datapesanan), 1,fdatapesanan3);
			}
		}
    fclose(fdatapesanan2);
    fclose(fdatapesanan);
    fclose(fdatapesanan3);
    remove("datapesanan.dat");
    rename("datapesanan3.dat","datapesanan.dat");
    puts("Pesanan berhasil diupdate dan diberi harga");getchar();
    menuadmin();
    }
    else{
        puts("Belum ada pesanan!");getchar();
        menuadmin();
    }
}

// Menghapus pesanan yang telah selesai
void hapuspesanan(){
    char username[30];
    fdatapesanan = fopen("datapesanan2.dat", "rb");
    j = 0;
	puts("DAFTAR PESANAN YANG SUDAH SELESAI");
    while(fread(&datapesanan,sizeof(datapesanan), 1, fdatapesanan) == 1){
        j += 1;
        printf(" Nama user : %s Harga : %d\n Status : %s\n", datapesanan.namauser, datapesanan.harga, datapesanan.status);
    }
    fclose(fdatapesanan);
    getchar();
    puts("1. Pilih dan hapus pesanan");
    puts("2. Kembali");
    printf("Masukkan pilihan : ");scanf("%d", &a);
    getchar();
    switch (a)
    {
    case 1:
        break;
    
    case 2 :
        menuadmin();
        break;
    default:
        hapuspesanan();
    }
    if(j>0){
        printf("Pilih pesanan yang akan diupdate dan diberi harga berdasarkan nama user : ");fgets(username, sizeof(username), stdin);
    fdatapesanan = fopen("datapesanan2.dat", "rb");
    fdatapesanan2 = fopen("datapesanantmp.dat", "ab");
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1){
    	if(strcmp(datapesanan.namauser,username)!=0){
            fwrite(&datapesanan,sizeof(datapesanan),1,fdatapesanan2);
        }
    }
    fclose(fdatapesanan);
    fclose(fdatapesanan2);
    remove("datapesanan2.dat");
	rename("datapesanantmp.dat","datapesanan2.dat");
    puts("Pesanan berhasil dihapus!");getchar();getchar();
    menuadmin();
    }
    else
    {
        puts("Belum ada pesanan yang selesai!");getchar();getchar();
        menuadmin();
    }
}

// Mencari jumlah user yang sesuai berdasarkan tanggal pemesanan
void searching(){
	int temptanggal[100];
    int jumlah=0;
    int cari;
    i=0;
    fdatapesanan = fopen("datapesanan.dat", "rb");
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1){
        temptanggal[i] = datapesanan.tanggal;
        i++;
    }
    fclose(fdatapesanan);
    fdatapesanan2 = fopen("datapesanan2.dat", "rb");
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan2)==1){
        temptanggal[i] = datapesanan.tanggal;
        i++;
    }
    // searching
    n=i;
    fclose(fdatapesanan2);
    printf("Masukan tanggal yang akan dicari jumlah pesanannya : ");scanf("%d", &cari);
    getchar;
    for (i = 0; i < n; i++){
    if (temptanggal[i] == cari)
		jumlah++;
	}
    printf("Ada %d pesanan pada tanggal %d", jumlah, cari);getchar();getchar();
    menuadmin();
}
//

//FITUR USER

// Pembuatan user baru
void userbaru(){
    flistuser = fopen("daftaruser.dat", "ab");
	printf("Masukkan nama pengguna  : ");fgets(listuser.namauser, sizeof(listuser.namauser), stdin);
    fflush(stdin);
	printf("Masukkan kata sandi : ");fgets(listuser.sandiuser, sizeof(listuser.sandiuser), stdin);
	fwrite(&listuser, sizeof(listuser), 1, flistuser);
	fclose(flistuser);
	puts("Pembuatan user baru telah selesai!");
	getchar();
    clearscrn();
    loginuser();
}

// Kolom login user
void loginuser(){
    flistuser = fopen("daftaruser.dat", "rb");
    puts("Login");
    printf("Nama user : ");fgets(nameuser, sizeof(nameuser), stdin);
    fflush(stdin);
    printf("Kata sandi : ");fgets(passuser, sizeof(passuser), stdin);
    while(fread(&listuser, sizeof(listuser), 1, flistuser) == 1){
    	if(strcmp(nameuser, listuser.namauser)==0 && strcmp(passuser, listuser.sandiuser)==0){
        strcpy(userlog, nameuser);
        fclose(flistuser);
        menuuser();
    	}
	}
	puts("Nama user atau sandi salah!");getchar();
    loginuser();
}

// Menu user untuk melakukan pemesanan
void menuuser(){
    int pilihanuser;
    clearscrn();
    puts("====DASLAUNDRY===");
    printf("Selamat datang %s", userlog);
    puts("====MENU USER====");
    puts("1. Buat pesanan baru");
    puts("2. Cek konfirmasi pesanan");
    puts("3. Keluar");
    printf("Masukkan pilihan : ");scanf("%d", &pilihanuser);
    getchar();
    switch (pilihanuser)
    {
    case 1 :
        clearscrn();pesananbaru();
        break;
    case 2 :
        clearscrn();cekkonfir();
        break;
    case 3 : 
		clearscrn();main();
        break;
    default:
        puts("Pilihan salah!");
        menuuser();
    }
}

// Fungsi pemesanan laundry
void pesananbaru(){
    int b=0;
    a=0;
    fdatapesanan = fopen("datapesanan.dat", "rb");
    while(fread(&datapesanan, sizeof(datapesanan), 1, fdatapesanan) == 1){
		if(strcmp(datapesanan.namauser, userlog) == 0){
			a += 1;
		}
	}
	fclose(fdatapesanan);
	fdatapesanan2 = fopen("datapesanan2.dat", "rb");
	while(fread(&datapesanan, sizeof(datapesanan), 1, fdatapesanan2) == 1){
		if(strcmp(datapesanan.namauser, userlog)==0){
			b+=1;
		}
	}
	fclose(fdatapesanan2);			    
	if(a == 0 && b == 0){
    fdatapesanan = fopen("datapesanan.dat", "ab");
    puts("Anda akan membuat pesanan baru");
    puts("Silahkan mengisi data-data pesanan :");
    printf("Berapa berat cucian anda (Kg) : ");fgets(datapesanan.berat, sizeof(datapesanan.berat), stdin);
    printf("Masukkan tanggal hari ini : ");scanf("%d", &datapesanan.tanggal);
    strcpy(datapesanan.namauser, userlog);
    strcpy(datapesanan.status, "Menunggu Konfirmasi");
    datapesanan.harga = 0;
    fwrite(&datapesanan,sizeof(datapesanan),1,fdatapesanan);
    puts("Pesanan berhasil dibuat");getchar();
    fclose(fdatapesanan);
    menuuser();
    }
    else{
		puts("Pesanan sudah ada!");
		getchar();
		menuuser();
	}
}

// Pengecekkan harga dan konfirmasi dari admin 
void cekkonfir(){
    fdatapesanan = fopen("datapesanan.dat", "rb");
    fdatapesanan2 = fopen("datapesanan2.dat", "rb");
    puts("Cek Konfirmasi Pesanan");
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1){
        if(strcmp(datapesanan.namauser, userlog)==0){
			printf("Status Pesanan anda saat ini adalah : %s\nHarga : %d", datapesanan.status, datapesanan.harga);getchar();
        }
    }
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan2)==1){
        if(strcmp(datapesanan.namauser, userlog)==0){
			printf("Status Pesanan anda saat ini adalah : %s\nHarga : %d", datapesanan.status, datapesanan.harga);getchar();
       }
    }
    fclose(fdatapesanan);
    fclose(fdatapesanan2);
    menuuser();
}
//
