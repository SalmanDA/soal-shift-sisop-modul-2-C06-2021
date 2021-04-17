#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <dirent.h>
#include <string.h>

int main()
{
    /**
     * @Variable Info : 
     * pid_t --> this variable is used to create process and it's children
    **/
    pid_t firstChildProcessId, secondChildProcessId, childProcess;
    firstChildProcessId = fork();
    secondChildProcessId = fork();

    // This condition to handle process if can't start
    if (firstChildProcessId < 0 || secondChildProcessId < 0)
    {
        exit(EXIT_FAILURE);
    }

    /** --Number 2A Answer-- **/
    // This condition is the first child process to create folder modul2/petshop
    if (firstChildProcessId > 0 && secondChildProcessId > 0)
    {
        printf("\n--Start soal2.c C06 Program--\n");
        printf("Creating modul2/petshop folder\n");
        char *commandLinuxArg[] = {"mkdir", "-p", "modul2/petshop", NULL};
        execv("/bin/mkdir", commandLinuxArg);
    }
    // This condition is the second child process to unzip pets.zip to modul2/petshop
    else if (firstChildProcessId == 0 && secondChildProcessId > 0)
    {
        printf("Unzipping jpg files on pets.zip\n");
        char *commandLinuxArgv[] = {"unzip", "pets.zip", "*.jpg", "-d", "modul2/petshop", NULL};
        execv("/bin/unzip", commandLinuxArgv);
    }
    /** --End of Number 2A Answer-- **/

    // This condition is the third child process to execute another command based on question 2B 2C 2D 2E
    else if (firstChildProcessId > 0 && secondChildProcessId == 0)
    {
        sleep(1);
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

                // Condition to skip name listing while dir gets folder not files
                if ( !strcmp( dirFile->d_name, "."  )) continue;
                if ( !strcmp( dirFile->d_name, ".." )) continue;

                // Copy and Append string fileDir to create path to jpeg after unzip
                strcpy(fileDir, "modul2/petshop/");
                strcat(fileDir, dirFile->d_name);
                
                // Copy and Append string name to create directory Folder per Pet's Category
                strcpy(folderCategory,"modul2/petshop/");
                strcpy(temp, dirFile->d_name);
		        strcat(folderCategory, strtok(temp, ";"));

                /** --Number 2B Answer-- **/
                // This condition to create folder per Pet Category
                if (childProcess = fork() == 0)
                {
                    printf("Creating folder on %s\n", folderCategory);
                    char *commandLinuxArgs[] = {"mkdir", "-p", folderCategory, NULL};
                    execv("/bin/mkdir", commandLinuxArgs);
                }
                /** --End of Number 2B Answer-- **/

                sleep(1);
                
                /** --Number 2D Answer-- **/
                // This condition to check if jpeg contain 2 pets or not
                if (strchr(dirFile->d_name, '_'))
                {
                    // Split 2 pet identity on same jpeg
                    char *temp2 = strtok(dirFile->d_name, "_");
                    while(temp2 != NULL)
                    {
                        /** --Number 2E Answer [type: doublePet]-- **/
                        // Create file keterangan.txt to store petIdentity
                        strcpy(fileDirTxt, folderCategory);
                        strcat(fileDirTxt, "/keterangan.txt");

                        // Get petIdentity
                        int i = 0;
                        strcpy(doublePets, temp2);
                        char *temp3 = strtok(doublePets, ";");

                        while(temp3 != NULL)
                        {
                            strcpy(petIdentity[i], temp3);
                            temp3 = strtok(NULL, ";");
                            i++;
                        }

                        // This condition to check if in last petIdentity has .jpg or not
                        if(strstr(petIdentity[2], ".jpg"))
                        {
                            strtok(petIdentity[2], "j");
                            petIdentity[2][strlen(petIdentity[2])-1] = '\0'; 
                        }

                        // File handling to write and add petIdentity
                        printf("Write %s's identity on keterangan.txt files\n", petIdentity[1]);
                        FILE *fptr;
                        fptr = fopen(fileDirTxt, "a");
                        fprintf(fptr, "nama : %s\n", petIdentity[1]);
                        fprintf(fptr, "umur : %s\n\n", petIdentity[2]);
                        fclose(fptr);
                        /** --End of Number 2E Answer [type: doublePet]-- **/

                        // Copy and Append fileDirDoublePets to locate filePath after unzip
                        strcpy(fileDirDoublePets, "modul2/petshop/");
                        strcat(fileDirDoublePets, temp2);

                        // condition to check string contain jpg or not
                        if(!strstr(temp2, ".jpg"))
                        {
                            strcat(fileDirDoublePets, ".jpg"); 
                        }

                        printf("Moving %s\n", fileDirDoublePets);

                        // Condition to copy jpg for each other pet (if it's contain double pet)
                        if (childProcess = fork() == 0)
                        {
                            char *commandLinuxArgs[] = {"cp", fileDir, fileDirDoublePets, NULL};
                            execv("/bin/cp", commandLinuxArgs);
                        }

                        sleep(1);

                        // Copy and Append newFileName to create new picture name based on pet's name
                        strcpy(newFileName, folderCategory);
                        strcat(newFileName, "/");
                        strcat(newFileName, petIdentity[1]);
                        strcat(newFileName, ".jpg");

                        /** --Number 2C Answer (move) [type: doublePet]-- **/
                        // Condition to move picture to pet's category
                        if (childProcess = fork() == 0)
                        {
                            strcpy(folderCategory,"modul2/petshop/");
                            strcpy(temp, temp2);
                            strcat(folderCategory, strtok(temp, ";"));

                            char *commandLinuxArgs[] = {"mv", fileDirDoublePets, folderCategory, NULL};
                            execv("/bin/mv", commandLinuxArgs);
                        }
                        /** --End of Number 2C Answer (move) [type: doublePet]-- **/

                        sleep(1);

                        // Condition to check if temp2 contain jpg or not
                        strcat(folderCategory, "/");
                        strcat(folderCategory, temp2);
                        if(!strstr(temp2, ".jpg"))
                        {
                            strcat(folderCategory, ".jpg"); 
                        }
                        
                        /** --Number 2C Answer (rename) [type: doublePet]-- **/
                        // Condition to rename file with pet's name
                        if (childProcess = fork() == 0)
                        {
                            printf("Renaming %s to %s\n\n", folderCategory, newFileName);
                            char *commandLinuxArgs[] = {"mv", folderCategory, newFileName, NULL};
                            execv("/bin/mv", commandLinuxArgs);
                        }
                        /** --End of Number 2C Answer (rename) [type: doublePet]-- **/
                        temp2 = strtok(NULL, "_");
                    }

                    sleep(1);

                    // Condition to remove original picture after unzip
                    if (childProcess = fork() == 0)
                    {
                        char *commandLinuxArgs[] = {"rm", fileDir, NULL};
                        execv("/bin/rm", commandLinuxArgs);
                    }
                }
                /** --End of Number 2D Answer-- **/
                else
                {
                    /** Number 2E Answer **/
                    // Create file keterangan.txt to store petIdentity
                    strcpy(fileDirTxt, folderCategory);
                    strcat(fileDirTxt, "/keterangan.txt");

                    // Get petIdentity
                    int i = 0;
                    strcpy(tempFileName, dirFile->d_name);
                    char *temp2 = strtok(tempFileName, ";");

                    while(temp2 != NULL)
                    {
                        strcpy(petIdentity[i], temp2);
                        temp2 = strtok(NULL, ";");
                        i++;
                    }
                
                    // Break string start on char 'j' on petIdentity last name (jpg) and remove '.' after age
                    strtok(petIdentity[2], "j");
                    petIdentity[2][strlen(petIdentity[2])-1] = '\0';

                    // File handling to write and append petIdentity on keterangan.txt
                    printf("Write %s's identity on keterangan.txt files\n", petIdentity[1]);
                    FILE *fptr;
                    fptr = fopen(fileDirTxt, "a");
                    fprintf(fptr, "nama : %s\n", petIdentity[1]);
                    fprintf(fptr, "umur : %s\n\n", petIdentity[2]);
                    fclose(fptr);
                    /** End of Number 2E Answer **/

                    /** Number 2C Answer (Move) **/
                    // This condition is used to handle moving picture to folder Pet Category
                    if (childProcess = fork() == 0)
                    {
                        printf("Moving %s to %s\n", fileDir, folderCategory);
                        char *commandLinuxArgs[] = {"mv", fileDir, folderCategory, NULL};
                        execv("/bin/mv", commandLinuxArgs);
                    }
                    /** End of Number 2C Answer (Move) **/

                    sleep(1);
                    
                    // Copy and Append string to create newFileName with pet's name
                    strcpy(newFileName, folderCategory);
                    strcat(newFileName, "/");
                    strcat(newFileName, petIdentity[1]);
                    strcat(newFileName, ".jpg");

                    // Append string to locate originalFile path
                    strcat(folderCategory, "/");
                    strcat(folderCategory, dirFile->d_name);
                    
                    /** Number 2C Answer (Rename) **/
                    // This condition is to handle renaming file
                    if (childProcess = fork() == 0)
                    {
                        printf("Renaming %s to %s\n\n", folderCategory, newFileName);
                        char *commandLinuxArgs[] = {"mv", folderCategory, newFileName, NULL};
                        execv("/bin/mv", commandLinuxArgs);
                    }
                    /** End of Number 2C Answer (Rename) **/
                }
            }
            closedir(typeDir);
        }
    }
    return 0;
}
