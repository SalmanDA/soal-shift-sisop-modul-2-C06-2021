# soal-shift-sisop-modul-2-C06-2021

## Laporan Soal Nomor 2 :

### Program Process
Untuk menyelesaikan soal nomor 2, kami menggunakan struktur process fork sebagai berikut : 

```
int main()
{
    /**
     * @Variable Info : 
     * pid_t --> this variable is used to create process and it's children
    **/
    pid_t firstChildProcessId, secondChildProcessId, childProcess;
    firstChildProcessId = fork();
    secondChildProcessId = fork();

    if (firstChildProcessId < 0 || secondChildProcessId < 0)
    {
        // This condition to handle process if can't start
    }

    if (firstChildProcessId > 0 && secondChildProcessId > 0)
    {
        // This condition is the parent process to create folder modul2/petshop
    }
    else if (firstChildProcessId == 0 && secondChildProcessId > 0)
    {
        // This condition is the first child process to unzip pets.zip to modul2/petshop
    }
    else if (firstChildProcessId > 0 && secondChildProcessId == 0)
    {
        // This condition is the second child process to execute another command based on question 2B 2C 2D 2E
    }
    return 0;
}
```

Dari struktur code kami diatas: 
- Pertama untuk childProcess < 0 untuk handle apakah terjadi error apa tidak. 
- Untuk childProcess 1 & 2 > 0 dijadikan condition parent process untuk exec membuat folder modul2/petshop .
- Untuk childProcess 1 == 0 & childProcess 2 > 0 dijadikan condition kedua untuk anak process pertama untuk unzip pets.zip ke dalam folder modul2/petshop .
- Untuk childProcess 1 > 0 & childProcess 2 == 0 dijadikan condition untuk exec perintah untuk menyelesaikan soal 2B, 2C, 2D, dan 2E.

### 2A
Dalam soal 2A diminta agar program dapat mengextract zip ke folder /modul2/petshop, kemudian untuk folder dan file yang tidak perlu dihapus. Menurut analisa kami pada saat mengerjakan soal, file yang penting hanyalah file yang berbentuk .jpg sehingga nantinya program kami hanya akan memindahkan file yang memiliki format .jpg.

Langkah awal untuk menyelesaikan soal 2A, memakai condition parent process untuk execute command mkdir dari /bin/mkdir untuk membuat folder baru yaitu modul2/petshop/.

```
/** --Number 2A Answer-- **/
    // This condition is the first child process to create folder modul2/petshop
    if (firstChildProcessId > 0 && secondChildProcessId > 0)
    {
        printf("\n--Start soal2.c C06 Program--\n");
        printf("Creating modul2/petshop folder\n");
        char *arg[] = {"mkdir", "-p", "modul2/petshop", NULL};
        execv("/bin/mkdir", arg);
    }
```

Kemudian, setelah berhasil membuat folder baru, gunakan childProcess pertama untuk melakukan exec command unzip file dan ditaruh kedalam folder /modul2/petshop yang sudah dibuat pada tahap sebelumnya.

```
// This condition is the second child process to unzip pets.zip to modul2/petshop
    else if (firstChildProcessId == 0 && secondChildProcessId > 0)
    {
        printf("Unzipping jpg files on pets.zip\n");
        char *argv[] = {"unzip", "pets.zip", "*.jpg", "-d", "modul2/petshop", NULL};
        execv("/bin/unzip", argv);
    }
```

### 2B
Dalam soal 2B diminta agar program dapat membuat folder untuk setiap jenis peliharaan yang ada. Untuk menyelesaikan soal ini kami menggunakan konsep bruteforce pada mkdir nantinya, karena tidak akan terjadi error jika sudah ada folder yang terbuat ,walaupun menurut kami kurang efisien tetapi sudah dapat menyelesaikan kondisi yang diminta di soal.

Langkah awal untuk mengerjakan soal 2B, 2C, 2D, dan 2E menggunakan child process yang sama yaitu childProcess 2 (Sleep digunakan untuk delay program agar tidak terjadi bentrok saat exec command berikutnya).

```
// This condition is the third child process to execute another command based on question 2B 2C 2D 2E
    else if (firstChildProcessId > 0 && secondChildProcessId == 0)
    {
        sleep(1);
```

Langkah berikutnya adalah menggunakan bantuan library dirent.h dari c yaitu DIR untuk mengakses sebuah directory dan mengecek ada file apa saja didalamnya.
Dengan bantuan looping nantinya kita dapat mengecek file apa saja yang berada didalam pointer Dir yaitu typeDir tersebut, dalam kasus kami membuka folder modul2/petshop (tempat file pertamakali diextract).

```
        /**
         * @Variable Info : 
         * DIR --> this data type to represent a directory stream
         * struct dirent * dir --> this struct to keep files when looping from DIR *d
        **/
        DIR *typeDir;
        struct dirent *dirFile;
        typeDir = opendir("modul2/petshop");

        if (typeDir)
        {
            while ((dirFile = readdir(typeDir)) != NULL)
            {
```

