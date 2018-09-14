//
// Created by yiner on 11/04/2018.
//

/*
 * tcpm.c
 * trivially copy a file via mmap/memcpy.
 * SYNOPSIS:
 * tcpm source target
 * DESCRIPTION:
 * The tcpm utility copies the contents of the source to target. That is, behaves entirely the same as tcp(1).
 * Unlike tcp(1), tcpm uses mmap(2) and memcpy(2) instead of read(2) and  write(2), which is why it can be rewarded with up to 10 extra credit points.
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <sys/mman.h>



int main(int argc, char *argv[]){
    
    //test if arguments are valid
    if (argc != 3){
        fprintf(stderr, "usage: %s source target \n", argv[0]);
        exit(1);
    }

    int fdin, n, fdout;
    
    
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

    void *start;
    void *end;
    struct stat sb;

    fstat(fdin,&sb);

    //这块必须给fout一个需求大小的偏移，因为mmap没有扩展空间的能力
    if(lseek(fdout,sb.st_size-1,SEEK_SET) < 0 ){
        exit(EXIT_FAILURE);
    }
    if(write(fdout, &sb,1) != 1 ){
        exit(EXIT_FAILURE);
    }

    //void * mmap(void *addr, size_t len, int prot, int flags, int fd, off_t offset);

    start = mmap(NULL,sb.st_size,PROT_READ,MAP_PRIVATE,fdin,0);
    if(start == MAP_FAILED) exit(EXIT_FAILURE);


    end = mmap(0,(size_t)sb.st_size,PROT_WRITE,MAP_SHARED,fdout,0);
    if(end == MAP_FAILED) exit(EXIT_FAILURE);

    memcpy(end,start,(size_t)sb.st_size);

    munmap(start,sb.st_size); //关闭映射
    munmap(end,sb.st_size);


    close(fdin);
    close(fdout);


    return 0;
}