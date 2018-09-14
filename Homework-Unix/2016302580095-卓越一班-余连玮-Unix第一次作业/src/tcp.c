//
// Created by yiner on 11/04/2018.
//

/*
 * tcp.c
 * trivially copy a file.
 * SYNOPSIS:
 * tcp source target
 * DESCRIPTION:
 * The tcp utility copies the contents of the source to target.
 * If target is a directory, tcp will copy source into this directory.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>

#define BUFFSIZE 64



int main(int argc, char *argv[]){

    //test if arguments are valid
    if (argc != 3){
         fprintf(stderr, "usage: %s source target \n", argv[0]);
         exit(1);
    }

    int fdin, n, fdout;
    char buf[BUFFSIZE];



    //test if source is existed
    if ((fdin=open(argv[1],O_RDONLY)) < 0 ){
        fprintf(stderr, "error: %s doesn't exist \n", argv[1]);
        exit(EXIT_FAILURE);
    }


    //open the target file
    //create the target file if it is not existed
    //test if it is directory

    if ((fdout=open(argv[2],O_CREAT|O_RDWR|O_TRUNC,S_IRWXU|S_IRGRP|S_IWGRP|S_IRWXO)) < 0){
        if (errno==EISDIR){
            char* target;
            target=argv[2];
            //get source file name
            char ch = '/';
            char *fname = strrchr(argv[1],ch);
            //get target file full path
            strcat(target,fname);
            //create a new target file
            close(fdout);
            fdout = open(target,O_CREAT|O_TRUNC|O_RDWR,S_IRWXU|S_IRGRP|S_IWGRP|S_IRWXO);

        }
        else{
            fprintf(stderr, "error: can't open %s: %s\n", argv[2],strerror(errno));
            exit(1);
        }

    }



    //read and write
    while ((n = read(fdin,buf,BUFFSIZE))>0){

        int cur = lseek(fdout,0,SEEK_CUR);

        while (write(fdout,buf,n) != n){
            lseek(fdout,cur,SEEK_SET);
        }
    }



    close(fdin);
    close(fdout);

 	return 0;
}