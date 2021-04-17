# soal-shift-sisop-modul-2-C06-2021

## Laporan Soal Nomor 1 :

### Penjelasan soal
Pada soal ini kami diminta untuk membuat tiga folder dengan nama "Musyik", "Fylm", dan "Pyoto". Kemudian mendownload tiga file .zip dari tiga link dan di ekstrak. File-file hasil ekstrak dipindahkan ke dalam folder yang telah dibuat. Semua kegiatan ini dilakukan secara otomatis pada tanggal 9 April 2021 pukul 16:22:00, yaitu 6 jam sebelum ulang tahun Stevany. Tepat pada saat ulang tahun Stevany, semua folder yang dibuat zip dengan nama Lopyu_Stevany.zip dan folder folder kosong lainnya akan dihapus.

### Program Process
Untuk menyelesaikan soal nomor 1, kami membuat fungsi-fungsi untuk melakukan kegiatan yang telah disebutkan.

### 2a, 2b dan 2c
Fungsi yang pertama adalah fungsi yang digunakan untuk pembuatan folder, mendownload file, dan mengekstrak file. Untuk menyelesaikannya, kami menggunakan struktur process fork sebagai berikut:

```
void prepare(){
	pid_t child = fork();
	int status;

	if(child<0) exit(EXIT_FAILURE);

	if(child==0){
		pid_t child1 = fork();
		int status1;

		if(child1<0) exit(EXIT_FAILURE);

		if(child1==0){ // membuat folder
			char *argv[]={"mkdir","-p",dir[0], dir[1], dir[2], NULL};
	            	execv("/bin/mkdir",argv);
		} else { 
			while((wait(&status1)) > 0);
			pid_t child2 = fork();
			int status2;
			
			if(child2<0) exit(EXIT_FAILURE);
			
			if(child2==0){// download dan unzip musik
				pid_t child3 = fork();
				int status3;
			
				if(child3<0) exit(EXIT_FAILURE);
			
				if(child3==0){
					char *argv[] = {"wget", gdrive[0], "-O", nama_zip[0], NULL};
		        		execv("/usr/bin/wget",argv);
				} else {
					while((wait(&status3)) > 0);
					sleep(5);
					char *argv[] = {"unzip", nama_zip[0], NULL};
					execv("/usr/bin/unzip", argv);
//					sleep(5);
				}
                ...
}
```
Pada fungsi ini, fork yang pertama akan membuat folder-folder yang diminta. Fork kedua akan mendownload dan mengekstrak file, demikian juga fork ketiga dan keempat.

### 2d
Untuk memindah file, juga menggunakan struktur process fork yang ahmpir sama seperti di atas. Kami menggunakan fung find dan mv untuk memindahkan fill-file yang telah diekstrak. Berikut implementasinya:

```
void move_files(){
	pid_t moves = fork();
	int move_status;

	if(moves<0) exit(EXIT_FAILURE);
	
	if(moves==0){
		pid_t moves1 = fork();
		int move_status1;

		if(moves1<0) exit(EXIT_FAILURE);
		
		if(moves1==0){
			char *argv[] = {"find", fold[0], "-type","f","-exec","mv","{}",dir[0],";", NULL};
	                execv("/usr/bin/find", argv);
		} else {
        ...
}
```

Jadi, fork pertama digunakan untuk memindah file dari folder "MUSIK" ke folder "Musyik". Fork kedua digunakan untuk memindah file dari "FILM" ke "Fylm". Dan yang terakhir digunakan untuk memindahkan file dari "FOTO" ke "Pyoto".

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

Langkah pertama untuk pengerjaan soal 2C disuruh untuk memindahkan foto dari folder setelah extract ke dalam folder jenis peliharaan yang telah dibuat pada soal 2B sesuai jenis peliharaan yang ada pada foto. Karena pada kasus kami sudah mengerjakan soal 2D dan 2E terlebih dahulu maka, kami sudah membagi antara foto yang memiliki peliharaan hanya 1 atau lebih dengan mengecek apakah string memiliki char "_" atau tidak.

Untuk yang 2C DoublePets (foto memiliki lebih dari satu peliharaan) :

Pakailah variable folderCategory untuk membuat path folder per jenis peliharaan dalam foto dan fileDirDoublePets.

```
 			// Copy and Append fileDirDoublePets to locate filePath after unzip
                        strcpy(fileDirDoublePets, "modul2/petshop/");
                        strcat(fileDirDoublePets, temp2);
```

Kemudian Cek apakah temp2 mempunyai .jpg atau tidak (ini terjadi karena jika 1 file memiliki 2 peliharaan setelah dipisah oleh "_" maka ada nama yang tidak memiliki .jpg. Jika tidak punya maka tambahkan ".jpg" dibelakang untuk penamaan file.

```
			// condition to check string contain jpg or not
                        if(!strstr(temp2, ".jpg"))
                        {
                            strcat(fileDirDoublePets, ".jpg"); 
                        }
```

Kemudian pindahkan file dengan "mv" dari directory setelah unzip ke dalam folder kategori per jenis peliharaan yang ada di dalam foto.

```
			/** --Number 2C Answer (move) [type: doublePet]-- **/
                        // Condition to move picture to pet's category
                        if (childProcess = fork() == 0)
                        {
                            strcpy(folderCategory,"modul2/petshop/");
                            strcpy(temp, temp2);
                            strcat(folderCategory, strtok(temp, ";"));

                            char *args[] = {"mv", fileDirDoublePets, folderCategory, NULL};
                            execv("/bin/mv", args);
                        }
                        /** --End of Number 2C Answer (move) [type: doublePet]-- **/
```

Langkah selanjutnya adalah menyiapkan variable newFileName untuk penamaan file baru berdasarkan nama dari peliharaan tersebut.

```
			// Copy and Append newFileName to create new picture name based on pet's name
                        strcpy(newFileName, folderCategory);
                        strcat(newFileName, "/");
                        strcat(newFileName, petIdentity[1]);
                        strcat(newFileName, ".jpg");
```

Langkah berikutnya memanipulasi string supaya folderCategory menjadi directory dari file yang sudah dipindah kedalam folder jenis peliharaan.

```
			// Condition to check if temp2 contain jpg or not
                        strcat(folderCategory, "/");
                        strcat(folderCategory, temp2);
                        if(!strstr(temp2, ".jpg"))
                        {
                            strcat(folderCategory, ".jpg"); 
                        }
                        
```

Langkah terakhir adalah rename file dengan bantuan command mv.

```
			/** --Number 2C Answer (rename) [type: doublePet]-- **/
                        // Condition to rename file with pet's name
                        if (childProcess = fork() == 0)
                        {
                            printf("Renaming %s to %s\n\n", folderCategory, newFileName);
                            char *args[] = {"mv", folderCategory, newFileName, NULL};
                            execv("/bin/mv", args);
                        }
                        /** --End of Number 2C Answer (rename) [type: doublePet]-- **/
```

Untuk file yang hanya berisi 
