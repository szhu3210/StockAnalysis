/*

File Preprocessing Program
This is to convert the original files into database file that can be accessed by my program directly and efficiently.
In this program I will read the data, skip all the useless part of data and analyze the data like MA, Newhigh, etc for convenience of the further trade which will be in the main program.
11.14.2015

Modified on 1.16.2016 by Troy (Fixed bugs and optimized for new datas)

Modified on 1.27.2016 by Troy (Add 10 more elements in x for further market analysis)

Modified on 2.15.2016 by Troy (Add the remaining 5 items, reorganize the existing 25 items)

Modified on 2.16.2016 by Troy (Update the comments of EPS, add one more data, totally 31 datas)

Temporarily modified on 3.5.2016 by Troy (only for Phase 11, analysis of the pivot time interval)

Modified on 3.13.2016 by Troy (modified the 19th and 23rd data into 220 day interval)

Modified on 3.16.2016 by Troy (rearrange whole structure)

x is defined as following:

Basic:

 0  date
 1  open
 2  high
 3  low
 4  close
 5  volume [hand]
 6  amount [CNY]
 7  up rate [%]

Moving average:

 8  ma20
 9  ma50

Price Interval:

 10 highest high (170)
 11 highest high (180)
 12 highest high (190)
 13 highest high (200)
 14 highest high (210)
 15 highest high (220)
 16 highest high (230)
 17 highest high (240)
 18 highest high (250)
 19 lowest low (170)
 20 lowest low (180)
 21 lowest low (190)
 22 lowest low (200)
 23 lowest low (210)
 24 lowest low (220)
 25 lowest low (230)
 26 lowest low (240)
 27 lowest low (250)

------------------------------------------------------------

 EPS (NOT IN THIS CODE, ONLY APPLICABLE FOR STOCKS) :

 28 EPS
 29 EPS up rate [%]
 30 ROE

------------------------------------------------------------


*/

#include <stdio.h>
#include <string.h>

#define PARMS 28
#define BUFFERSIZE 300

void shift(double x[][PARMS])
{
    int i,j;
    //shift x up by one element
    for (i=0; i<BUFFERSIZE; i++)
        for (j=0; j<PARMS; j++)
            x[i][j]=x[i+1][j];
}

double ma(double x[][PARMS], int p, int i, int n)
{
    double avg,sum=0;
    int j;
    //calculate moving average
    for (j=i-n+1; j<=i; j++)
        sum+=x[j][p];
    avg=sum/n;

    return avg;
}

//highest (p) in the past n days (today not included)
double highest(double x[][PARMS],int p, int i, int n)
{
    int j;
    double max=0;
    for (j=i-1;j>=i-n; j--)
        if (x[j][p]>max) max=x[j][p];
    return max;
}

//lowest (p) in the past n days (today not included)
double lowest(double x[][PARMS],int p, int i, int n)
{
    int j;
    double min=65535;
    for (j=i-1;j>=i-n; j--)
        if (x[j][p]<min) min=x[j][p];
    return min;
}

void process(FILE *fi,char fdir[])
{

    fscanf(fi, "%*[^\n]\n");
    fscanf(fi, "%*[^\n]\n");

//    This part is for test use.
//    char s11[255];
//    fgets(s11,255,fi);
//    printf("%s\n",s11);
//    printf("%s\n\n",fdir);

    printf("%s\n",fdir);

    FILE* fo=fopen(fdir, "w");
    char s[255];
    double x[BUFFERSIZE+1][PARMS];
    int i,j;

    for (i=0; i<=BUFFERSIZE; i++) {
        for (j=0; j<PARMS; j++) {
            x[i][j]=-1;
        }
    }

    i=-1;

    while((fgets(s, 255, fi) != NULL)&&(strlen(s)>25))
    {
        i++;

        if (i>BUFFERSIZE)
        {
            shift(x);
            i=BUFFERSIZE;
        }
        sscanf(s,"%lf %lf %lf %lf %lf %lf %lf",&x[i][0],&x[i][1],&x[i][2],&x[i][3],&x[i][4],&x[i][5],&x[i][6]);  //scan data
        if (x[i][3]>0)                                 //if negative value turned up, skip
        {

            // 7 up rate
            if (i>=1) x[i][7]=(x[i][4]/x[i-1][4]-1)*100;

            // 8 ma20
            if (i>=19) x[i][8]=ma(x,4,i,20);

            // 9 ma50
            if (i>=49) x[i][9]=ma(x,4,i,50);

            // 10 highest high in the past 170 days (today not included)
            if (i>=170) x[i][10]=highest(x,2,i,170);

            // 11 highest high in the past 180 days (today not included)
            if (i>=180) x[i][11]=highest(x,2,i,180);

            // 12 highest high in the past 190 days (today not included)
            if (i>=190) x[i][12]=highest(x,2,i,190);

            // 13 highest high in the past 200 days (today not included)
            if (i>=200) x[i][13]=highest(x,2,i,200);

            // 14 highest high in the past 210 days (today not included)
            if (i>=210) x[i][14]=highest(x,2,i,210);

            // 15 highest high in the past 220 days (today not included)
            if (i>=220) x[i][15]=highest(x,2,i,220);

            // 16 highest high in the past 230 days (today not included)
            if (i>=230) x[i][16]=highest(x,2,i,230);

            // 17 highest high in the past 240 days (today not included)
            if (i>=240) x[i][17]=highest(x,2,i,240);

            // 18 highest high in the past 250 days (today not included)
            if (i>=250) x[i][18]=highest(x,2,i,250);

            // 19 lowest low in the past 170 days (today not included)
            if (i>=170) x[i][19]=lowest(x,3,i,170);

            // 20 lowest low in the past 180 days (today not included)
            if (i>=180) x[i][20]=lowest(x,3,i,180);

            // 21 lowest low in the past 190 days (today not included)
            if (i>=190) x[i][21]=lowest(x,3,i,190);

            // 22 lowest low in the past 200 days (today not included)
            if (i>=200) x[i][22]=lowest(x,3,i,200);

            // 23 lowest low in the past 210 days (today not included)
            if (i>=210) x[i][23]=lowest(x,3,i,210);

            // 24 lowest low in the past 220 days (today not included)
            if (i>=220) x[i][24]=lowest(x,3,i,220);

            // 25 lowest low in the past 230 days (today not included)
            if (i>=230) x[i][25]=lowest(x,3,i,230);

            // 26 lowest low in the past 240 days (today not included)
            if (i>=240) x[i][26]=lowest(x,3,i,240);

            // 27 lowest low in the past 250 days (today not included)
            if (i>=250) x[i][27]=lowest(x,3,i,250);

            for (j=0;j<PARMS;j++) fprintf(fo,"%.2f ",x[i][j]);   //print
            fprintf(fo,"\n");
        }
    }

    fclose(fo);
}

void filepreprocess(char s1[],char s2[])
{
    FILE *fi=NULL;  //file pointer for read

    int i,j=0;
    char fdir[255]; //file directory

    char folderin[255];
    char folderout[255];

    char b[255];

    sprintf(folderin,"/home/troy/Stock Analysis/1Data/%s/",s1);
    sprintf(folderout,"/home/troy/Stock Analysis/1Data/%s/",s2);

    printf("File PreProcessing: %9s     \n",s2);

    //Indices
    sprintf(fdir, "%sSH#999999.txt", folderin);	//SH999999
    fi = fopen(fdir, "r");
    if (fi != NULL)
    {
        sprintf(fdir, "%sSH#999999.txt", folderout);
        process(fi,fdir);
        j++;
	fclose(fi);
    }

    for (i = 700000; i < 700808; i++)
    {
        sprintf(b, "SH#%d.txt", i);                 //adjust the file name
        b[3] = '0';
        sprintf(fdir, "%s%s", folderin, b);			//create the file directory
        fi = fopen(fdir, "r");
        if (fi != NULL)
        {
            sprintf(fdir, "%s%s", folderout, b);
            process(fi,fdir);
            j++;
	    fclose(fi);
        }
        
    }

    for (i = 880305; i < 880561; i++)
    {
        sprintf(fdir, "%sSH#%d.txt", folderin, i);	//create the input file directory
        fi = fopen(fdir, "r");
        if (fi != NULL)
        {
            sprintf(fdir, "%sSH#%d.txt", folderout, i);
            process(fi,fdir);
            j++;
	    fclose(fi);
        }
        
    }

    for (i = 399001; i < 399942; i++)
    {
        sprintf(fdir, "%sSZ#%d.txt", folderin, i);	//create the input file directory
        fi = fopen(fdir, "r");
        if (fi != NULL)
        {
            sprintf(fdir, "%sSZ#%d.txt", folderout, i);
            process(fi,fdir);
            j++;
	    fclose(fi);
        }
        
    }

    //SH
    for (i = 600000; i < 605000; i++)
    {
        sprintf(fdir, "%sSH#%d.txt", folderin, i);	//create the input file directory
        fi = fopen(fdir, "r");
        if (fi != NULL)
        {
            sprintf(fdir, "%sSH#%d.txt", folderout, i);
            process(fi,fdir);
            j++;
	    fclose(fi);
        }
        
    }

    //SZ
    for (i = 700000; i < 703000; i++)
    {
        sprintf(b, "SZ#%d.txt", i);                 //adjust the file name
        b[3] = '0';
        sprintf(fdir, "%s%s", folderin, b);			//create the file directory
        fi = fopen(fdir, "r");
        if (fi != NULL)
        {
            sprintf(fdir, "%s%s", folderout, b);
            process(fi,fdir);
            j++;
	    fclose(fi);
        }
        
    }

    //SZ-CYB
    for (i = 300000; i < 301000; i++)
    {
        sprintf(fdir, "%sSZ#%d.txt", folderin, i);
        fi = fopen(fdir, "r");
        if (fi != NULL)
        {
            sprintf(fdir, "%sSZ#%d.txt", folderout, i);
            process(fi,fdir);
            j++;
	    fclose(fi);
        }
        
    }

    //output status
    printf("Total searched file: %d\n",j);
}

int main()
{

    //from original stockdata to standardstockdata(without EPS)
    filepreprocess("2originalStockData","4stockdata-FPP/Test0");

    //from original indexdata to standardindexdata
    //filepreprocess("3originalIndexData","6indexdata-FPP");

}
