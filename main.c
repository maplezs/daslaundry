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

// Prototype prosedur untuk user admin	
void loginadmin(); 		// untuk masuk ke user admin
void menuadmin(); 		// menu pilihan admin
void hapuspesanan();	// hapus pesanan yang sudah di-update
void daftarpesanan();	// melihat semua daftar pesanan yang sudah dibuat user
void statusdanharga();	// memberi harga pada pesanan user tertentu serta memperbarui status pesanan
void daftaruser();		// melihat semua daftar user yang sudah registrasi
void loginuser(); 		// untuk login akun yang sudah teregistrasi
void userbaru(); 		// membuat user baru
void menuuser();		// menu user
void pesananbaru();		// membuat pesanan baru
void cekkonfir(); 		// cek konfirmasi pesanan dari admin

// Deklarasi struct
struct tgl{
        char berat[10];
        int tanggal;
        char namauser[30];
        int harga;
        char status[40];
} datapesanan;
struct tglx{
        char berat[10];
        int tanggal;
        char namauser[30];
        int harga;
        char status[40];
} temp[100];
struct tglxx{
        char berat[10];
        int tanggal;
        char namauser[30];
        int harga;
        char status[40];
} tempx[100];
struct user{
	char namauser[30];
	char sandiuser[40];
}  listuser;

// Variabel
char admuser[20], nameuser[30];
char admpasswd[40], passuser[40];
char status[30], buatbaru[2], userlog[30], pilihuser[30];
int temp2;
FILE *fadmin;
FILE *flistuser;
FILE *fdatapesanan;
FILE *fbackdatapesanan;
FILE *fdatapesanan2;
FILE *fdatapesanan3;

// FUNGSI UTAMA
int main(){
    // buat file kosong jika belum ada saat program mulai untuk mencegah error
    flistuser = fopen("daftaruser.dat", "ab");
    fdatapesanan = fopen("datapesanan.dat", "ab");
    fdatapesanan2 = fopen("datapesanan2.dat", "ab");
    fclose(flistuser);
    fclose(fdatapesanan);
    fclose(fdatapesanan2);
    int log;
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
    char useradmin[30];
    char adminpass[40];
    printf("Username : ");gets(useradmin); 
    printf("Password : ");gets(adminpass); 
	if(strcmp(useradmin, "admin")==0 && strcmp(adminpass, "123")==0){
		menuadmin();
	}
	puts("Username dan Password salah!");
	getchar();
	loginadmin();
}
void menuadmin(){
    int admpilih;
    clearscrn();
    puts("1. Beri harga pada pesanan dan update status pada pesanan");
    puts("2. Daftar user");
    puts("3. Daftar pesanan");
    puts("4. Hapus pesanan yang sudah selesai");
    puts("5. Logout");
    printf("Masukkan pilihan : ");scanf("%d", &admpilih);
    switch (admpilih)
    {
    case 1:
        statusdanharga();
        break;
    case 2:
        daftaruser();
        break;
    case 3:
        daftarpesanan();
        break;
    case 4:
       hapuspesanan();
        break;
    case 5:
        main();
        break;
    default:
        puts("Pilihan salah!");
        menuadmin();
    }
}
void loginuser(){
    flistuser = fopen("daftaruser.dat", "rb");
    puts("Login");
    printf("Nama user : ");fgets(nameuser, sizeof(nameuser), stdin);
    fflush(stdin);
    printf("Kata sandi : ");fgets(passuser, sizeof(passuser), stdin);
    while(fread(&listuser,sizeof(listuser),1,flistuser)==1){
    	if(strcmp(nameuser, listuser.namauser)==0 && strcmp(passuser, listuser.sandiuser)==0){
        strcpy(userlog, nameuser);
        fclose(flistuser);
        menuuser();
    	}
	}
	puts("Nama user atau sandi salah!");getchar();
    loginuser();
}
void userbaru(){
    flistuser = fopen("daftaruser.dat", "ab");
	printf("Masukkan nama pengguna  : ");fgets(listuser.namauser, sizeof(listuser.namauser), stdin);
    fflush(stdin);
	printf("Masukkan kata sandi : ");fgets(listuser.sandiuser, sizeof(listuser.sandiuser), stdin);
	fwrite(&listuser,sizeof(listuser),1,flistuser);
	fclose(flistuser);
	puts("Pembuatan user baru telah selesai!");
	getchar();
    clearscrn();
    loginuser();
}
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
        pesananbaru();
        break;
    case 2 :
        cekkonfir();
        break;
    case 3 : 
		clearscrn();
        main();
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
    int z = 0;
    flistuser = fopen("daftaruser.dat", "rb");
	while(fread(&listuser,sizeof(listuser),1,flistuser)==1){
            z+=1;
			printf("%d. Nama Pengguna : %s\n", z, listuser.namauser);
		}
    if(z > 0){
        printf("Total User yang terdaftar : %d", z);
    }
    else
    {
        puts("Belum ada user yang terdaftar!");
    }
    
    fclose(flistuser);getchar();getchar();
    menuadmin();
}
void daftarpesanan(){
    int i=0;
    int n;
    clearscrn();
    puts("DAFTAR PESANAN USER");
    puts("DAFTAR PESANAN YANG BELUM SELESAI");
    fdatapesanan = fopen("datapesanan.dat", "rb+");
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1){
        strcpy(temp[i].namauser, datapesanan.namauser);
        strcpy(temp[i].berat, datapesanan.berat);
        strcpy(temp[i].status, datapesanan.status);
        temp[i].harga = datapesanan.harga;
        temp[i].tanggal = datapesanan.tanggal;
        i++;
        n=i;
    }
    fclose(fdatapesanan);
    i = 0;
    int j;
    if(n>0){
    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++){
            if(temp[j].tanggal>temp[j+1].tanggal){
                temp2 = temp[j].tanggal;
                temp[j].tanggal = temp[j+1].tanggal;
                temp[j+1].tanggal = temp2;
            }
        }
    }
    for(i=0;i<n;i++){
        printf("%d. Nama : %s Berat : %s Tanggal : %d\n Status : %s\n", i+1, temp[i].namauser, temp[i].berat, temp[i].tanggal, temp[i].status);
		}
    }
    else
    {
        puts("Belum ada pesanan!");
    }
    
    puts("DAFTAR PESANAN YANG SUDAH SELESAI");
    fdatapesanan2 = fopen("datapesanan2.dat", "rb+");
    i=0;
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
    if (n==0){
		puts("Tidak ada pesanan yang selesai");
	}
    else if(n>0){
    for(i=0;i<n;i++){
        for(j=0;j<n-i-1;j++){
            if(tempx[j].tanggal>tempx[j+1].tanggal){
                temp2 = tempx[j].tanggal;
                tempx[j].tanggal = tempx[j+1].tanggal;
                tempx[j+1].tanggal = temp2;
            }
            }
        }
    for(i=0;i<n;i++){
        printf("%d. Nama : %s Berat : %s Tanggal : %d\n Status : %s\n", i+1, tempx[i].namauser, tempx[i].berat, tempx[i].tanggal, tempx[i].status);
    }
    }
    else{
        puts("Belum ada pesanan yang selesai!");
    }

    getchar();getchar();
    menuadmin();
}
void pesananbaru(){
    int pil;
    int a=0, b=0;
    fdatapesanan = fopen("datapesanan.dat", "rb");
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1){
		if(strcmp(datapesanan.namauser, userlog)==0){
			a+=1;
		}
	}
	fclose(fdatapesanan);
	fdatapesanan2 = fopen("datapesanan2.dat", "rb");
	while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan2)==1){
		if(strcmp(datapesanan.namauser, userlog)==0){
			b+=1;
		}
	}
	fclose(fdatapesanan2);			    
	if(a>0 && b>0){
    fdatapesanan = fopen("datapesanan.dat", "ab");
    puts("Anda akan membuat pesanan baru");
    puts("Silahkan mengisi data-data pesanan :");
    printf("Berapa berat cucian anda : ");fgets(datapesanan.berat, sizeof(datapesanan.berat), stdin);
    printf("Masukkan tanggal hari ini : ");scanf("%d", &datapesanan.tanggal);
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
    else{
		puts("Pesanan sudah ada!");
		getchar();
		menuuser();
	}
}
void statusdanharga(){
    int i=0;
    int i2;
    int harga;
    char konfirm[40]="Menunggu Konfirmasi";
    fdatapesanan = fopen("datapesanan.dat", "rb");
    clearscrn();
    puts("Daftar pesanan yang belum dikonfirmasi dan diberi harga");
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1){
        if(strcmp(datapesanan.status, konfirm)==0){
        i+=1;
        printf("%d. Nama : %s Berat %s Tanggal %d\n Status : %s\n", i,datapesanan.namauser, datapesanan.berat, datapesanan.tanggal, datapesanan.status);
       }
    }
    fclose(fdatapesanan);
    puts("1. Pilih pesanan untuk diberi harga dan update");
    puts("2. Kembali");
    printf("Masukkan pilihan : ");scanf("%d", &i2);
    switch (i2)
    {
    case 1:
        break;
    
    case 2 :
        menuadmin();
        break;
    default:
        statusdanharga();
    }
    getchar();
    if(i>0){
        printf("Pilih pesanan yang akan diupdate dan diberi harga berdasarkan nama user : ");fgets(pilihuser, sizeof(pilihuser), stdin);
        printf("Masukkan harga : ");scanf("%d", &harga);
        fdatapesanan2 = fopen("datapesanan2.dat", "ab");
        fdatapesanan = fopen("datapesanan.dat", "rb");
        fdatapesanan3 = fopen("datapesanan3.dat", "ab");
        while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1){
    	if(strcmp(datapesanan.namauser,pilihuser)==0){
            datapesanan.harga = harga;
    	    strcpy(datapesanan.status, "Pesanan selesai");
            fwrite(&datapesanan,sizeof(datapesanan),1,fdatapesanan2);
        }
        }
        fclose(fdatapesanan);
        fdatapesanan = fopen("datapesanan.dat", "rb");
        while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1){
        if(strcmp(datapesanan.namauser,pilihuser)!=0){
            fwrite(&datapesanan,sizeof(datapesanan),1,fdatapesanan3);
        }
    }
    fclose(fdatapesanan2);
    fclose(fdatapesanan);
    fclose(fdatapesanan3);
        remove("datapesanan.dat");
	    rename("datapesanan3.dat","datapesanan.dat");
        puts("Pesanan berhasil diupdate dan diberi harga");getchar();getchar();
        menuadmin();
    }
    else{
        puts("Belum ada pesanan!");getchar();getchar();
        menuadmin();
    }
}
void hapuspesanan(){
    char username[30];
    int j;
    int x1;
    fdatapesanan = fopen("datapesanan2.dat", "rb");
    clearscrn();
    j=0;
	puts("DAFTAR PESANAN YANG SUDAH SELESAI");
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1){
        j+=1;
        printf(" Nama user : %s Harga : %d\n Status : %s\n", datapesanan.namauser, datapesanan.harga, datapesanan.status);
    }
    fclose(fdatapesanan);
    getchar();
    puts("1. Pilih dan hapus pesanan");
    puts("2. Kembali");
    printf("Masukkan pilihan : ");scanf("%d", &x1);
    switch (x1)
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
void cekkonfir(){
    fdatapesanan = fopen("datapesanan.dat", "rb");
    fdatapesanan2 = fopen("datapesanan2.dat", "rb");
    puts("Cek Konfirmasi Pesanan");
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1){
        if(strcmp(datapesanan.namauser, userlog)==0){
        printf("Status Pesanan anda saat ini adalah : %s\nHarga : %d", datapesanan.status, datapesanan.harga);getchar();getchar();
        }
    }
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan2)==1){
        if(strcmp(datapesanan.namauser, userlog)==0){
        printf("Status Pesanan anda saat ini adalah : %s\nHarga : %d", datapesanan.status, datapesanan.harga);getchar();getchar();
        }
    }
    fclose(fdatapesanan);
    fclose(fdatapesanan2);
    menuuser();
}
