#include<stdio.h>
#include<time.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<syslog.h>
#include<unistd.h>



char* cipher(char string[]){
	int f;
	for(f=0;string[f]!='\0';f++){
		char queue = string[f];
		if(queue>='A' && queue<='Z'){
			queue+=5;
			if(queue>'Z'){
			queue=queue-'Z'+'A'-1;
			}
			string[f] = queue;
		}
		else if(queue>='a' && queue<='z'){
			queue+=5;
			if(queue>'z'){
			queue=queue-'z'+'a'-1;
			}
			string[f] = queue;
		}
	}
	
	return string;
}

/*void createkill(const *char node){
	FILE *fap;
	fap = fopen("Killer.sh", "w+");
	if(strcmp(node, "-z")==0){
	fprintf(fap, "#!/bin/bash\n killall -9 ./3a\n echo \'program killed\'\n rm -r Killer.sh");
	}
	else if(strcmp(node, "-x")==0){
	fprintf(fap, "#!/bin/bash\n kill %d \n echo \'program killed\'\n rm -r Killer.sh", getpid());
	}	
	
}*/

int main(int argc, char *argv[]){
	if(argc!=2 || strcmp(argv[1], "-z")!=0 || strcmp(argv[1],"-x")!=0 )
	{
	printf("Invalid command\n");
	exit(0);
	}
	
	int node;
	if(strcmp(argv[1],"-z")==0)node=1;
	else if(strcmp(argv[1], "-x")==0)node=2;
	
	FILE *fap;
	fap = fopen("Killer.sh", "w+");
	fprintf("#!/bin/bash\n node=%d if [ $node -eq 1]\n then\n killall -9 ./3a\n else\n kill %d\n fi echo /`program killed/`\n rm -r Killer.sh", node, getpid()+1);
	fclose(fap);
	
	
	//createkill(node);

	while(1){
		time_t rawtime;
		struct tm *info;
		char buffer[80];
	
		time( &rawtime );
	
		info = localtime( &rawtime );
	
		strftime(buffer,80,"%Y-%m-%d_%H:%M:%S", info);
		
		char filename[100];
		strcpy(filename,buffer);
		strcat(filename,".zip");
		
	
		pid_t pid_1;
		
		pid_1 = fork();
		if(pid_1 < 0){
		exit(EXIT_FAILURE);
		}
		if(pid_1 ==0){
		//soal 3a
		char *argv[] = {"mkdir", buffer, NULL};
		execv("/bin/mkdir", argv);
		}
		
		int status;
		
		while(wait(&status)>0);
		
		pid_t pid_2;
		pid_2 = fork();
		
		if(pid_2 < 0){
		exit(EXIT_FAILURE);
		}
		if(pid_2 == 0){
		//soal 3b
		chdir(buffer);
		int i=0;
		while(i<10){
		time_t ctime = time(NULL);
		struct tm *current;
		char buffer2[80];
		current = localtime( &ctime );
		strftime(buffer2, 80, "%Y-%m-%d_%H:%M:%S", current);
		char chphoto[1001];
		sprintf(chphoto, "https://picsum.photos/%ld", (ctime % 1000) + 50);	
		
		pid_t pid_3;
		pid_3 = fork();
		
		if(pid_3<0){
		exit(EXIT_FAILURE);
		}
		if(pid_3==0){
			char *arg[]={"wget", chphoto, "-O", buffer2, NULL};
			execv("/bin/wget", arg);
			}
		i++;
		sleep(5);
		}
		
		//soal 3c
		if(i>=0){
		char meslog[100] = "Download Success";
		char temp[100];
		strcpy(temp, meslog);
		cipher(temp);
		strcpy(meslog,temp);
		
		FILE *fp;
		
		fp = fopen("status.txt","w+");
		fputs(meslog, fp);
		fclose(fp);
		}
		
		chdir("..");
		char zip[100];
		strcpy(zip, filename);
		
		
		pid_t pid_4;
		if(pid_4=fork()<0){
		exit(EXIT_FAILURE);
		}
		if(pid_4 == 0){
			char *argl[]={"zip", "-r", zip, buffer, NULL};
			execv("/bin/zip", argl);
		}
		char *arglp[]={"rm", "-r", buffer, NULL};
		execv("/bin/rm", arglp);
	}
		
	sleep(40);
}	
}

