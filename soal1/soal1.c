#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <string.h>
#include <wait.h>

char *dir[] = {"Musyik","Fylm","Pyoto"};
char *gdrive[] = {"https://drive.google.com/uc?id=1ZG8nRBRPquhYXq_sISdsVcXx5VdEgi-J&export=download","https://drive.google.com/uc?id=1ktjGgDkL0nNpY-vT7rT7O6ZI47Ke9xcp&export=download","https://drive.google.com/uc?id=1FsrAzb9B5ixooGUs0dGiBr-rC7TS9wTD&export=download"};
char *nama_zip[] = {"Musik_for_Stevany.zip","Film_for_Stevany.zip","Foto_for_Stefany.zip"};
char *fold[] = {"MUSIK","FILM","FOTO"};

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
			} else {
				while((wait(&status2)) > 0);
				pid_t child4 = fork();
				int status4;
			
				if(child4<0) exit(EXIT_FAILURE);
					
				if(child4==0){ //download dan unzip film
					pid_t child5 = fork();
					int status5;
			
					if(child5<0) exit(EXIT_FAILURE);
						
					if(child5==0){
						char *argv[] = {"wget","--no-check-certificate",gdrive[1],"-O", nama_zip[1], NULL};
		                		execv("/usr/bin/wget", argv);
					} else {
						while((wait(&status5)) > 0);
						sleep(5);
						char *argv[] = {"unzip", nama_zip[1], NULL};
						execv("/usr/bin/unzip", argv);
//						sleep(5);
					}
				} else { //download dan unzip foto
					while((wait(&status4)) > 0);
					pid_t child6 = fork();
					int status6;

					if(child6<0) exit(EXIT_FAILURE);

					if(child6==0){
						char *argv[] = {"wget","--no-check-certificate",gdrive[2], "-O", nama_zip[2], NULL};
		               			execv("/usr/bin/wget", argv);
					} else {
						while((wait(&status6)) > 0);
						sleep(5);
						char *argv[] = {"unzip", nama_zip[2], NULL};
						execv("/usr/bin/unzip", argv);
					}
				}
			}
		}
	} else { //return
        	while((wait(&status)) > 0);
        	return;
    	}
}

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
			while((wait(&move_status1)) > 0);
			pid_t moves2 = fork();
			int move_status2;

			if(moves2<0) exit(EXIT_FAILURE);

			if(moves2==0){
				char *argv[] = {"find", fold[1], "-type","f","-exec","mv","{}",dir[1],";", NULL};
	                	execv("/usr/bin/find", argv);
			} else {
				while((wait(&move_status2)) > 0);
				char *argv[] = {"find", fold[2], "-type","f","-exec","mv","{}",dir[2],";", NULL};
	                	execv("/usr/bin/find", argv);
			}
		}
	} else {
		while((wait(&move_status)) > 0);
		return;
	}
}

void day_D(){
	pid_t day_id = fork();
	int day_status;

	if(day_id<0) exit(EXIT_FAILURE);
		
	if(day_id==0){
		pid_t day1 = fork();
        	int dstatus1;
       	 
        	if(day1<0) exit(EXIT_FAILURE);

        	if(day1==0){
            		char *argv[]={"zip","-mr","Lopyu_Stevany",dir[0], dir[1], dir[2], NULL};
              	 	execv("/usr/bin/zip",argv);
        	}
        	else{
            		while((wait(&dstatus1)) > 0);
            		char *argv[]={"rm","-rf","MUSIK", "FOTO", "FILM", NULL};
            		execv("/bin/rm",argv);
        	}   
	} else {
		while((wait(&day_status)) > 0);
	    	return;
	} 
}

int main() {
	pid_t pid, sid;        // Variabel untuk menyimpan PID
	pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
	if (pid < 0) {
	exit(EXIT_FAILURE);
	}

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
	if (pid > 0) {
	exit(EXIT_SUCCESS);
	}

	umask(0);

	sid = setsid();
	if (sid < 0) {
	exit(EXIT_FAILURE);
	}

	if ((chdir("/home/damai/Documents/modul2/")) < 0) {
	exit(EXIT_FAILURE);
	}

	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);

	while (1) {
    // Tulis program kalian di sini
		char task1[]="09-Apr 16:22";
	    	char task2[]="09-Apr 22:22";
	    	
	    	time_t waktu =time(NULL);
	    	char ultah[99];
	    	struct tm *now = localtime(&waktu);
	    	strftime(ultah, sizeof(ultah), "%d-%b %H:%M", now);

		//time_t waktu;
      		//struct tm* tm_skrg;

	      	//waktu = time(NULL);
      		//tm_skrg = localtime(&waktu);

			if(strcmp(ultah,task1) == 0){
				prepare();
				move_files();
			} else 
			if(strcmp(ultah,task2) == 0){
				day_D();
			}
		sleep(1);
	}
}
