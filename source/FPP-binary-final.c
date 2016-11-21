//FPP-binary

//Created by Troy on 4/25/2016

//This code is to convert text files into binary form.

#include <stdio.h>
#define BMN 1

void convert(FILE *in, FILE *out)
{
	double temp;
	//loop until eof
	while (fscanf(in,"%lf",&temp)>0) 
	{
        //read a double from in 
		//it's already read in "temp"

        //write a double binary into out
        fwrite(&temp, sizeof(double), 1, out);
    }
}

int main()
{
	char benchmarkdir[255],b[255], filenamedir[255], filedir[255];
	char folder[255]="/home/troy/Stock Analysis/1Data/5stockdata-final";
	FILE *filename=NULL;
	FILE *t=NULL;
	FILE *out=NULL;
	int i=0, j=0;
	char outpath[255];

	//loop BMN
	for (i = 0; i < BMN; ++i)
	{

		j=0;

		//set benchmarkdir
		sprintf(benchmarkdir,"%s/Test%d",folder, i);
		sprintf(filenamedir,"%s/filename%d.txt",benchmarkdir,i);

		//open filename.txt
		filename=fopen(filenamedir,"r");

		//loop through filenames
		while (fscanf(filename,"%s\n",b)>0) 
		{
        	printf("%s\n",b);
        	sprintf(filedir, "%s/%s", benchmarkdir, b);	//create the file directory
        	//printf("%s\n",filedir);
        	t= fopen(filedir, "r");
        	if (t != NULL)
       		{
            	//t is the file pointer of a certain stock data file, a.k.a. input

            	//make outpath and out pointer
       			sprintf(outpath,"/home/troy/Stock Analysis/1Data/8stockdata-binary/Test%d/%c%c%c%c%c%c%c%c%c.bin",i,b[0],b[1],b[2],b[3],b[4],b[5],b[6],b[7],b[8]);
       			out=fopen(outpath,"wb");

            	//convert, with parms: t, out.
            	convert(t,out);

            	//close t, out.
            	fclose(t);
            	fclose(out);

            	//counter ++
            	j++;
        	}	
    	}
    
    	//close filename
    	if (filename!=NULL) fclose(filename);

    	//print total searched stocks
    	printf("total stock # in benchmark %d: %d\n", i, j);

	}

}