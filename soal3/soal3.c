#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

struct waktu{
   int hours, minutes, seconds, day, month, year;
};

typedef struct waktu Struct;
Struct getTime(){
   //setup time
   time_t now;
   time(&now);
   struct tm *local = localtime(&now);
   
   Struct n;
   
   n.day = local->tm_mday;
   //month start form 0 to 11           
   n.month = local->tm_mon + 1;
   // year start from 1900      
   n.year = local->tm_year + 1900;  
   n.hours = local->tm_hour;          
   n.minutes = local->tm_min;        
   n.seconds = local->tm_sec; 
   
   return n;

};

void encrypt(char folder[]){
   FILE *fp;
   char txtpath[40];
   snprintf(txtpath,sizeof txtpath,"./%s/status.txt",folder);
   fp  = fopen (txtpath, "w");
   int key=5;
   //caesar cipher algorithm
   char message[]="Download Success", ch;
   for(int i = 0; message[i] != '\0'; ++i){
		ch = message[i];
		if(ch >= 'a' && ch <= 'z'){
			ch = ch + key;
			if(ch > 'z'){
				ch = ch - 'z' + 'a' - 1;
			}
			message[i] = ch;
		}
		else if(ch >= 'A' && ch <= 'Z'){
			ch = ch + key;
			if(ch > 'Z'){
				ch = ch - 'Z' + 'A' - 1;
			}
			message[i] = ch;
		}
	}
   //write to txt
   printf("Download Success = %s\n",message);
   for (int i = 0;i<16; i++) 
      fputc(message[i], fp);
   fclose(fp);
}

int main(int argc, char **argv){
   // int createdir;
   char image[30],folder[30],imagepath[100],link[50];
   Struct timeNow;
   pid_t pid, sid, parent_id;        
   parent_id = getpid();
   int status;
   pid = fork();
   sid = setsid();

   //exit after finish forking
   if (pid > 0)
      exit(EXIT_SUCCESS);

   FILE *killer;
   killer = fopen("killer.sh", "w");
   //when -z stop everything immediatly when -x stop after ziping
   if (strcmp(argv[1], "-z") == 0)
      fprintf(killer, "#!/bin/bash\nkill -9 -%d\n rm killer.sh", getpid());
   else if (strcmp(argv[1], "-x") == 0)
      fprintf(killer, "#!/bin/bash\nkill %d\n rm killer.sh", getpid());
      
   fclose(killer);
   //to be executable bash
   if(fork() == 0){
      char *argvmod[] = {"chmod", "+x", "killer.sh", NULL};
      execv("/bin/chmod", argvmod);
   }
   //close read input and write output
   close(STDIN_FILENO);
   close(STDOUT_FILENO);

   while(1){
      //take present time
      timeNow=getTime();
      //concate folder name
      snprintf(folder,sizeof folder,"%02d-%02d-%02d_%02d:%02d:%02d",timeNow.year,timeNow.month,timeNow.day,timeNow.hours,timeNow.minutes,timeNow.seconds);
      
      pid_t child1,child2,child3;
      child1=fork();
      if(child1 == 0){
         child2=fork();
         if(child2==0){
         // createdir= mkdir(folder, S_IRUSR | S_IRGRP | S_IROTH | S_IXUSR | S_IXGRP | S_IXOTH | S_IWUSR | S_IWGRP | S_IWGRP);
            char *argvmk[] = {"mkdir", "-p", folder, NULL};
            execv("/bin/mkdir",argvmk);
         }
         else{
            while(wait(&status)>0);
            // download image
            for(int i=0;i<10;i++){
               if(fork()==0){
                  printf("Duar\n");
                  //epoch time
                  int epoch = (int)time(NULL);
                  epoch = (epoch % 1000)+100;
                  //update present time in every loop
                  timeNow=getTime();
                  //image naming
                  snprintf(image,sizeof image,"%02d-%02d-%02d_%02d:%02d:%02d.jpg",timeNow.year,timeNow.month,timeNow.day,timeNow.hours,timeNow.minutes,timeNow.seconds);
                  snprintf(imagepath,sizeof imagepath,"./%s/%s",folder,image); 
                  snprintf(link,sizeof link,"https://picsum.photos/%d.jpg",epoch);
                  //blank space due to bugs on wget that are redirecting to log file afterworth
                  //ga ngerti epoch cuy
                  execl("/usr/bin/wget", "wget", "-q","-O",imagepath, link,"", NULL);
               }
               sleep(5);
            }
            encrypt(folder);
            //zip file
            char zipfile[40];
            snprintf(zipfile,sizeof zipfile,"%s.zip",folder);
            execl("/usr/bin/zip","zip","-rm",zipfile,folder,"-x","*.c",NULL);
         }
      }
      else sleep(40);
   }
   return 0;
}
