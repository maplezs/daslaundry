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
void statusdanharga();		// memberi harga pada pesanan user tertentu serta memperbarui status pesanan
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
        int bulan;
        char namauser[30];
        int harga;
        char status[40];
} datapesanan;
struct user{
	char namauser[30];
	char sandiuser[40];
}  listuser;
// Variabel
char admuser[20], nameuser[30];
char admpasswd[40], passuser[40];
char status[30], buatbaru[2], userlog[30], pilihuser[30];
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
    	// kode yang di komen dibawah ini hapus saja bikin gaisa login jangan pake else intinya 
    /*	else {
			clearscrn();
			puts("Username atau Password salah");
			loginuser();
		}*/
	}
	puts("Nama user atau sandi salah!");getchar();getchar();
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
    printf("Selamat datang %s", userlog);
    puts("di Daslaundry!");
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
    int y=0;
    fdatapesanan = fopen("datapesanan.dat", "rb+");
    fdatapesanan2 = fopen("datapesanan2.dat", "rb+");
    clearscrn();
    puts("DAFTAR PESANAN USER");
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1){
            y+=1;
            printf("%d. Nama : %s Berat %s Tanggal %d\n Bulan :%d\n Status : %s\n", y, datapesanan.namauser, datapesanan.berat, datapesanan.tanggal, datapesanan.bulan, datapesanan.status);
    }
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan2)==1){
            y+=1;
            printf("%d. Nama : %s Berat %s Tanggal %d\n Bulan :%d\n Status : %s\n", y,datapesanan.namauser, datapesanan.berat, datapesanan.tanggal, datapesanan.bulan, datapesanan.status);
    }
    fclose(fdatapesanan);fclose(fdatapesanan2);
    getchar();getchar();
    menuadmin();
}
void pesananbaru(){
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
void statusdanharga(){
    int i=0;
    int harga;
    char konfirm[40]="Menunggu Konfirmasi";
    fdatapesanan = fopen("datapesanan.dat", "rb");
    clearscrn();
    puts("Daftar pesanan yang belum dikonfirmasi dan diberi harga");
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1){
        if(strcmp(datapesanan.status, konfirm)==0){
        i+=1;
        printf("%d. Nama : %s Berat %s Tanggal %d\n Bulan :%d\n Status : %s\n", i,datapesanan.namauser, datapesanan.berat, datapesanan.tanggal, datapesanan.bulan, datapesanan.status);
       }
    }
    fclose(fdatapesanan);
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
// Semua Kode yang dikomen dibawah ini jangan dihapus dulu tunggu semua selesai, bisa saja nanti masih bisa kepakai 
   // fdatapesanan = fopen("datapesanan.dat", "rb");
    //fbackdatapesanan = fopen("backdatapesanan.dat", "ab");
    //fflush(stdout);
   // while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1){
//			fwrite(&datapesanan,sizeof(datapesanan),1,fbackdatapesanan);
   // }
    //fclose(fdatapesanan);
  //  fclose(fbackdatapesanan);
    /*printf("Pilih pesanan yang akan diupdate dan diberi harga berdasarkan nama user : ");fgets(pilihuser, sizeof(pilihuser), stdin);
    printf("Masukkan harga : ");scanf("%d", &harga);
    fdatapesanan2 = fopen("datapesanan2.dat", "ab");
   // fdatapesanan3 = fopen("datapesanan3.dat", "a+b");
    fdatapesanan = fopen("datapesanan.dat", "rb");
    //fbackdatapesanan = fopen("backdatapesanan.dat", "rb");
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
   // fdatapesanan = fopen("datapesanan.dat", "rb");
    fclose(fdatapesanan);
    fclose(fdatapesanan3);
    //fflush(fdatapesanan);
   /* fflush(fdatapesanan2);
    while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1 && strcmp(datapesanan.namauser, pilihuser)==0){
    	datapesanan.harga = harga;
    	strcpy(&datapesanan.status, "Pesanan selesai");
        rewind(fdatapesanan2);
        fwrite(&datapesanan,sizeof(datapesanan),1,fdatapesanan2);
        //fseek(fdatapesanan2,sizeof(datapesanan), SEEK_CUR);
    }//fclose(fdatapesanan2);fclose(fdatapesanan);
    //pesananbelum();
    fflush(stdout);
   while(fread(&datapesanan,sizeof(datapesanan),1,fdatapesanan)==1){
    	if(strcmp(datapesanan.namauser,pilihuser)!=0){
			fwrite(&datapesanan,sizeof(datapesanan),1,fdatapesanan2);
		}
	}
    fclose(fdatapesanan);
    fclose(fdatapesanan2);*/
   /* remove("datapesanan.dat");
    //remove("backdatapesanan.dat");
	rename("datapesanan3.dat","datapesanan.dat");
    puts("Pesanan berhasil diupdate dan diberi harga");getchar();getchar();
    menuadmin();*/
   // statusdanharga();
}
void hapuspesanan(){
    char username[30];
    int j;
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
    /*
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
    */

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
