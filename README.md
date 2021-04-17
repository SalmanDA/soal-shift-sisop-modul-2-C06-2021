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

Langkah selanjutnya untuk mengerjakan soal 2B sampai 2E dibutuhkan beberapa variable untuk memanipulasi penamaan file untuk data yang diminta oleh soal, maka dari itu kami membuat beberapa variable untuk menyelesaikan soal (NOTE : variable ini berlaku sampai 2E karena 2B - 2E dikerjakan dalam 1 looping), keterangan penggunaan variable sudah kami tuliskan di dalam code.

```
                /**
                 * @Variable Info : 
                 * folderCategory : String --> this variable is used to store directory folder per pets category
                 * temp : String --> this variable is used to temporary store dir->d_name and strtok by ";" to get pet's category name
                 * fileDir : String --> this variable is used to store files jpg directory after unzip
                 * fileDirDoublePets : String --> this variable is used to store files jpg directory when in picture there are 2 pets 
                 * doublePets : String --> this variable is used to store temporary file name for double pets in the picture
                 * fileDirTxt : String --> this variable is used to store directory file to create keterangan.txt on folder modul2/petshop
                 * petIdentity : String (doubleArray) --> this variable used to store petCategory;petName;petAge from file name
                 * newFileName : String --> this variable used to store newFileName to rename file with pet's name
                 * tempFileName : String --> this variable used to store temporary file name, used later to get petIdentity like category;name;age
                **/
                char folderCategory[256];
                char temp[256];
                char fileDir[256];
                char fileDirDoublePets[256];
                char doublePets[256];
                char fileDirTxt[256];
                char petIdentity[3][256];
                char newFileName[256];
                char tempFileName[256];
```     

Langkah berikutnya adalah karena looping ini dapat mendeteksi bukan hanya file melainkan juga directory seperti "." dan ".." maka untuk hanya looping file .jpg yang diperlukan pada soal, kami mengakalinya dengan cara berikut.

```
                // Condition to skip name listing while dir gets folder not files
                if ( !strcmp( dirFile->d_name, "."  )) continue;
                if ( !strcmp( dirFile->d_name, ".." )) continue;
```

Setelah lewat dari kondisi diatas, maka dirFile sudah pasti hanya berisi file .jpg. Berikutnya, Copy dan Tambahkan string untuk membuat directory file path ke lokasi jpg saat file pertama kali di extract yaitu di /modul2/petshop/

```
                // Copy and Append string fileDir to create path to jpeg after unzip
                strcpy(fileDir, "modul2/petshop/");
                strcat(fileDir, dirFile->d_name);
```

Selanjutnya gunakan variable folderCategory untuk pemindahan file jpg berdasarkan jenis peliharaan yang ada di foto tersebut. Kami menggunakan strtok untuk break string pada saat bertemu ";" karena kategori jenis peliharaan berada pada nama file pertama sebelum char ';'.

```
                // Copy and Append string name to create directory Folder per Pet's Category
                strcpy(folderCategory,"modul2/petshop/");
                strcpy(temp, dirFile->d_name);
		        strcat(folderCategory, strtok(temp, ";"));
```

Setelah kondisi diatas semua terpenuhi dan berhasil, maka kami menggunakan childProcess baru untuk exec command pembuatan folder jenis peliharaan.

```
                /** --Number 2B Answer-- **/
                // This condition to create folder per Pet Category
                if (childProcess = fork() == 0)
                {
                    printf("Creating folder on %s\n", folderCategory);
                    char *args[] = {"mkdir", "-p", folderCategory, NULL};
                    execv("/bin/mkdir", args);
                }
                /** --End of Number 2B Answer-- **/
```

### 2C
Untuk memudahkan pengerjaan kami sengaja mengerjakan 2C terakhir, jadi dalam program kami setelah 2D dan 2E selesai dikerjakan barulah kami mengerjakan soal 2C, karena pada soal 2C kami disuruh untuk memindahkan foto ke folder pada saat, Pada kasus kami untuk menjelaskan soal 2C karena pengerjaan terakhir asumsikan 2D dan 2E sudah selesai dikerjakan.

Langkah pertama untuk pengerjaan soal 2C disuruh untuk memindahkan foto dari folder setelah extract ke dalam folder jenis peliharaan yang telah dibuat pada soal 2B sesuai jenis peliharaan yang ada pada foto. Karena pada kasus kami sudah mengerjakan soal 2D dan 2E terlebih dahulu maka, kami sudah membagi antara pets.
