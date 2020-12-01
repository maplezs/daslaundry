#include <stdio.h>
#include <string.h>
int log;
char admuser[20];
char admpasswd[40];
FILE *fadmin;
struct {
	char username[20];
	char pass[40];
} ademin;
void loginadmin();
void menuadmin();
int main(){
    puts("Menu Login");
    puts("Login sebagai :");
    puts("1. Admin");
    puts("2. User");
    printf("Masukkan pilihan : ");scanf("%d", &log);
}
void loginadmin(){
    printf("Username : ");fgets(admuser, sizeof(admuser), stdin);
    fflush(stdin);
    printf("Password : ");fgets(admpasswd, sizeof(admpasswd), stdin);
    fadmin = fopen("dataadmin.dat", "rb");
    fread(&ademin,sizeof(ademin),1,fadmin);
    if(strcmp(admuser, ademin.username)==1 && strcmp(admuser, ademin.pass)==1){
        fclose(fadmin);
        menuadmin();
    }
    else if(strcmp(admuser, ademin.username)!=1 || strcmp(admuser, ademin.pass)!=1){
        puts("Username atau kata sandi salah!");
        loginadmin();
    }
}
void menuadmin(){
    int admpilih;
    puts("1. Beri harga pada pesanan");
    puts("2. Daftar user");
    puts("3. Daftar pesanan");
    puts("4. Update status pesanan");
    puts("5. Hapus pesanan yang sudah selesai");
    printf("Masukkan pilihan : ");scanf("%d", &admpilih);
    switch (admpilih)
    {
    case 1:
        beriharga();
        break;
    case 2:
        daftaruser();
        break;
    case 3:
        daftarpesanan();
        break;
    case 4:
        updatestatus();
        break;
    case 5:
        hapuspesanan();
        break;
    default:
        puts("Pilihan salah!");
        menuadmin();
    }
}
void daftaruser(){
    FILE *fuser;
    struct data {
        char name[40];
    } user;
    
    fuser = fopen("datauser.dat", "rb");
    while(fread(&user,sizeof(user),1,fuser)==1){
		printf("%s\n", user.name);
		puts("");
	} fclose(fuser);
}
