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
    switch (log)
    {
    case 1:
        loginadmin();
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
    clearscrn();
    getchar();
    printf("Username : ");fgets(admuser, sizeof(admuser), stdin);
    fflush(stdin);
    printf("Password : ");fgets(admpasswd, sizeof(admpasswd), stdin);
    while(fread(&ademin,sizeof(ademin),1,fadmin)==1){
    if(strcmp(admuser, ademin.username)==0 && strcmp(admpasswd, ademin.pass)==0){
        fclose(fadmin);
        menuadmin();
    }
	}
	puts("Username atau Password salah");
	loginadmin();
}
void loginuser(){
    struct user{
	char namauser[30];
	char sandiuser[40];
    } listuser;
    flistuser = fopen("daftaruser.dat", "rb");
    clearscrn();
    getchar();
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
    puts("Nama user atau sandi salah!");
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
        //daftarpesanan();
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
    printf("Selamat datang %s di Daslaundry!\n", userlog);
    puts("====MENU USER====");
    puts("1. Buat pesanan baru");
    puts("2. Cek konfirmasi pesanan");
    printf("Masukkan pilihan : ");scanf("%d", &pilihanuser);
    switch (pilihanuser)
    {
    case 1 :
        //pesananbaru();
        break;
    case 2 :
       // cekkonfir();
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
    fflush(stdin);
    fclose(flistuser);getchar();getchar();
    menuadmin();
}
/*
void beriharga(){
    FILE *flistharga;
    struct harga
    {
        char harga[20];
    } listharga;
    flistharga = fopen("daftarharga", "rb");
    if()

}
*/
