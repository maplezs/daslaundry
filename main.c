#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// Prototype fungsi untuk bersihkan layar tiap masuk ke sebuah menu dapat berfungsi di Linux, Mac OS dan Windows
void clearscrn();
// Prototype prosedur untuk user admin
	// untuk masuk ke user admin
void loginadmin();
	// menu pilihan admin
void menuadmin();
	// hapus pesanan yang sudah di-update
void hapuspesanan();
	// memperbarui status pesanan jika sudah selesai
void updatestatus();
	// melihat semua daftar pesanan yang sudah dibuat user
void daftarpesanan();
	// memberi harga pada pesanan user tertentu
void beriharga();
	// melihat semua daftar user yang sudah registrasi
void daftaruser();

// Prototype prosedur untuk user
	// untuk login akun yang sudah teregistrasi
void loginuser();
	// membuat user baru
void userbaru();
	// menu user
void menuuser();
	// membuat pesanan baru
void pesananbaru();
	// cek konfirmasi pesanan dari admin
void cekkonfir();
// Variabel
char admuser[20], namauser[30];
char admpasswd[40], sandiuser[40];
char status[30], buatbaru[2], userlog[30];
FILE *fadmin;
FILE *flistuser;
FILE *fdatapesanan;
// FUNGSI UTAMA
int main(){
    int log;
    // Menu utama terdapat pilihan login sebagai user atau admin serta pilihan untuk keluar dari program
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
        loginuser();
        break;
    case 3:
        userbaru();
        break;
	  case 4:
		exit(0);
		break;
    default:
        puts("Pilihan salah!");
        getchar();getchar();
        clearscrn();
        main();
    }
}
void clearscrn(){
	if(system("cls")!=0){
		system("clear");
	}
	else{
		system("cls");
	}
}
// Prosedur login admin dengan database yang sudah ada
void loginadmin(){
    struct data {
	char username[20];
	char pass[40];
    } ademin;
    fadmin = fopen("dataadmin.dat", "rb");
    printf("Username : ");fgets(admuser, sizeof(admuser), stdin);
    fflush(stdin);
    printf("Password : ");fgets(admpasswd, sizeof(admpasswd), stdin);
    while(fread(&ademin,sizeof(ademin),1,fadmin)==1){
		if(strcmp(admuser, ademin.username)==0 && strcmp(admpasswd, ademin.pass)==0){
			fclose(fadmin);
			menuadmin();
		}
		else{
			clearscrn();
			puts("Username atau Password salah");
			loginadmin();
		}
	}
}
void loginuser(){
    struct user{
	char namauser[30];
	char sandiuser[40];
    } listuser;
    flistuser = fopen("daftaruser.dat", "rb");
    clearscrn();
    printf("Nama user : ");fgets(namauser, sizeof(namauser), stdin);
    fflush(stdin);
    printf("Kata sandi : ");fgets(sandiuser, sizeof(sandiuser), stdin);
    fread(&listuser,sizeof(listuser),1,flistuser);
    while(fread(&listuser,sizeof(listuser),1,flistuser)==1){
    	if(strcmp(namauser, listuser.namauser)==0 && strcmp(sandiuser, listuser.sandiuser)==0){
        strcpy(userlog, namauser);
        fclose(flistuser);
        menuuser();
    	}
    }
    puts("Nama user atau sandi salah!");getchar();getchar();
    loginuser();
}
void userbaru(){
    struct user{
	char namauser[30];
	char sandiuser[40];
    }  listuser;
	flistuser = fopen("daftaruser.dat", "ab");
    clearscrn();
    getchar();
	printf("Masukkan nama pengguna  : ");fgets(listuser.namauser, sizeof(listuser.namauser), stdin);
	fflush(stdin);
	printf("Masukkan kata sandi : ");fgets(listuser.sandiuser, sizeof(listuser.sandiuser), stdin);
	fwrite(&listuser,sizeof(listuser),1,flistuser);
	fclose(flistuser);
	puts("Pembuatan user baru telah selesai!");
    loginuser();
}
void menuadmin(){
    int admpilih;
    clearscrn();
    puts("1. Beri harga pada pesanan");
    puts("2. Daftar user");
    puts("3. Daftar pesanan");
    puts("4. Update status pesanan");
    puts("5. Hapus pesanan yang sudah selesai");
    puts("6. Logout");
    printf("Masukkan pilihan : ");scanf("%d", &admpilih);
    switch (admpilih)
    {
    case 1:
        //beriharga();
        break;
    case 2:
        daftaruser();
        break;
    case 3:
        daftarpesanan();
        break;
    case 4:
        //updatestatus();
        break;
    case 5:
       //hapuspesanan();
        break;
    case 6:
        main();
        break;
    default:
        puts("Pilihan salah!");
        menuadmin();
    }
}
void menuuser(){
    int pilihanuser;
    clearscrn();
    printf("Selamat datang %s", userlog);
    printf("di Daslaundry!\n");
    puts("====MENU USER====");
    puts("1. Buat pesanan baru");
    puts("2. Cek konfirmasi pesanan");
    printf("Masukkan pilihan : ");scanf("%d", &pilihanuser);
    switch (pilihanuser)
    {
    case 1 :
        pesananbaru();
        break;
    case 2 :
        cekkonfir();
        break;
    case 3 : 
        loginuser();
        break;
    default:
        puts("Pilihan salah!");
        menuuser();
    }
}
void daftaruser(){
    struct data {
        char namauser[30];
        char sandiuser[40];
    } listuser;
    flistuser = fopen("daftaruser.dat", "rb");
	while(fread(&listuser,sizeof(listuser),1,flistuser)==1){
			printf("Nama Pengguna : %s\n", listuser.namauser);
		}
    fclose(flistuser);getchar();getchar();
    menuadmin();
}
void daftarpesanan(){
    struct tgl{
        char berat[10];
        int tanggal;
        int bulan;
        char namauser[30];
        double harga;
        char status[40];
    } datapesanan;
    fdatapesanan = fopen("datapesanan.dat", "rb");
    puts("DAFTAR PESANAN USER");
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1){
    printf("Nama : %s Berat %s Tanggal %d\n Bulan :%d\n Status : %s", datapesanan.namauser, datapesanan.berat, datapesanan.tanggal, datapesanan.bulan, datapesanan.status);
    }
    fclose(fdatapesanan);getchar();getchar();
    menuadmin();
}
void pesananbaru(){
    struct tgl{
        char berat[10];
        int tanggal;
        int bulan;
        char namauser[30];
        double harga;
        char status[40];
    } datapesanan;
    int pil;
    fdatapesanan = fopen("datapesanan.dat", "ab");
    puts("Anda akan membuat pesanan baru");
    puts("Silahkan mengisi data-data pesanan :");
    getchar();
    printf("Berapa berat cucian anda : ");fgets(datapesanan.berat, sizeof(datapesanan.berat), stdin);
    printf("Masukkan tanggal hari ini : ");scanf("%d", &datapesanan.tanggal);
    printf("Masukkan bulan : ");scanf("%d", &datapesanan.bulan);
    strcpy(datapesanan.namauser, userlog);
    strcpy(datapesanan.status, "Menunggu Konfirmasi");
    datapesanan.harga = 0;
    fwrite(&datapesanan,sizeof(datapesanan),1,fdatapesanan);
    puts("Pesanan berhasil dibuat");
    fclose(fdatapesanan);
    puts("Ingin membuat pesanan lagi atau kembali ke menu? : ");
    puts("1. Buat pesanan baru");
    puts("2. Kembali ke menu");
    printf("Masukkan pilihan : ");scanf("%d", &pil);
    switch (pil)
    {
    case 1 :
        pesananbaru();
        break;
    case 2 :
        menuuser();
        break;
    default:
        puts("Pilihan salah!");getchar();getchar();
    }
    
}
/*
void updatestatus(){

}
*/
void cekkonfir(){
    struct tgl{
        char berat[10];
        int tanggal;
        int bulan;
        char namauser[30];
        double harga;
        char status[40];
    } datapesanan;
    fdatapesanan = fopen("datapesanan.dat", "rb");
    puts("Cek Konfirmasi Pesanan");
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1 && strcmp(datapesanan.namauser, userlog)==0){
		printf("Status Pesanan anda saat ini adalah : %s", datapesanan.status);getchar();getchar();
    }
    menuuser();
}
/*
void beriharga(){
    struct tgl{
        char berat[10];
        int tanggal;
        int bulan;
        char namauser[30];
        double harga;
    } datapesanan;
    fdatapesanan = fopen("datapesanan.dat", "ab");
    

}
*/
