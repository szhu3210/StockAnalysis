//
//  Filename and Benchmark Generator - binary.c
//  Phase 29
//
//  Modified by Shengxiang Zhu on 04/25/116.
//  Copyright © 2016 Shengxiang Zhu. All rights reserved.
//

//  This script is based on Phase 5 but I just create some filenames for different benchmarks instead of copying a lot of stock files.
//  This script works with Phase 29 and above.

//  This script is for binary files.

#define MAXFILE 3000
#define BMN 11
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

void initialfile(char filenames[][255],int *filenum)
{
    int i, j;
    FILE *t;
    char folder[]="/home/troy/Stock Analysis/1Data/8stockdata-binary/Test0/";
    char filename[255];
               
    //search stock files and save to filenames array
    char a[255];
    j = 0;										//stock counter
    
    //SH
    for (i = 600000; i < 605000; i++)
    {
        sprintf(filename,"SH#%d.bin", i);
        sprintf(a, "%s%s", folder, filename);	//create the file directory
        t = fopen(a, "r");
        if (t != NULL)
        {
            sprintf(filenames[j], "%s", filename);
            j++;
        }
    }
    //printf("Stock #: %d\n", j);

    //SZ
    for (i = 700000; i < 703000; i++)
    {
        sprintf(filename, "SZ#%d.bin", i);				//adjust the file name
        filename[3] = '0';
        sprintf(a, "%s%s", folder, filename);			//create the file directory
        t = fopen(a, "r");
        if (t != NULL)
        {
            sprintf(filenames[j], "%s", filename);
            j++;
        }
    }
    //printf("Stock #: %d\n", j);

    //SZ-CYB
    for (i = 300000; i < 301000; i++)
    {
        sprintf(filename,"SZ#%d.bin", i);
        sprintf(a, "%s%s", folder, filename);   //create the file directory
        t = fopen(a, "r");
        if (t != NULL)
        {
            sprintf(filenames[j], "%s", filename);
            j++;
        }
    }
    
    *filenum = j;
    printf("Stock #: %d\n", j);
}


int main()
{
    FILE *out;
    int STOCKNUM = 2000;
    char filenames[MAXFILE][255];
    char outpath[255];
    int filemark[MAXFILE];
    int filenum,i,j,k,r;

    srand(time(NULL));
    
    initialfile(filenames,&filenum);

    for (k=0;k<BMN;k++)
    {
        
        //set output path
        sprintf(outpath,"/home/troy/Stock Analysis/1Data/8stockdata-binary/Test0/filename%d.txt",k);
        out=fopen(outpath,"w");

        if (k>0) {

        	//reset filemark
        	for (i=0;i<MAXFILE;i++) filemark[i]=0;

        	//randomly choose files
        	for (j=0;j<STOCKNUM;)
        	{

           		r=rand() % filenum;

            	if (filemark[r]==0)
            	{

            	    filemark[r]=1;

            	    fprintf(out,"%s\n",filenames[r]);

            	    j++;

            	}
            
        	}

        } else {

        	//k==0
        	for (j=0;j<filenum;j++) fprintf(out,"%s\n",filenames[j]);
            
        }
        
        fclose(out);

    }
}
