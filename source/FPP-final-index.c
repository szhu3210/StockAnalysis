/*
 
File Preprocessing Program
This is to convert the original files into database file that can be accessed by my program directly and efficiently.
In this program I will read the data, skip all the useless part of data and analyze the data like MA, Newhigh, etc for convenience of the further trade which will be in the main program.
11.14.2015

Modified on 1.16.2016 by Troy (Fixed bugs and optimized for new datas)

Modified on 1.27.2016 by Troy (Add 10 more elements in x for further market analysis)
 
Modified on 2.15.2016 by Troy (Add the remaining 5 items, reorganize the existing 25 items)
 
Modified on 2.16.2016 by Troy (Update the comments of EPS, add one more data, totally 31 datas)
 
Modified on 2.19.2016 by Troy (This version is only for Phase 9, add more ma values to w)
 
Modified on 2.20.2016 by Troy (Just declare that this version is just for extended w so it can be inherited)
 
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
 10 ma200
 11 ma50 up rate [%]
 12 ma200 up rate [%]
 13 vma20
 14 vma50
 15 vma20 up rate [%]
 16 vma50 up rate [%]
 
Price interval (TODAY NOT INCLUDED) :
 
 17 highest high (20)
 18 highest high (50)
 19 highest high (200)
 20 highest high (historical)
 21 lowest low (20)
 22 lowest low (50)
 23 lowest low (200)
 24 lowest low (historical)
 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

 (The following is just for Phase 9)
MA's :
 25-84 ma21-ma80
 
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 
------------------------------------------------------------
EPS (NOT IN THIS CODE, ONLY APPLICABLE FOR STOCKS) :
 
 25 EPS
 26 EPSTTM
 27 EPSTTM up rate [%]
 28 ROETTM [%]
 29 ROETTM up rate [%]
 30 Liquid shares [10^9]
------------------------------------------------------------
 
 
*/

#include <stdio.h>
#include <string.h>

#define PARMS 85


void shift(double x[][PARMS])
{
    int i,j;
    //shift x up by one element
    for (i=0; i<200; i++)
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
    double x[201][PARMS];
    int i,j;
    
    for (i=0; i<=200; i++) {
        for (j=0; j<PARMS; j++) {
            x[i][j]=-1;
        }
    }
    
    double historicalhigh = 0;
    double historicallow = 65535;
    
    i=-1;
    
    while((fgets(s, 255, fi) != NULL)&&(strlen(s)>25))
    {
        i++;
        
        if (i>200)
        {
            shift(x);
            i=200;
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

            // 10 ma200
            if (i>=199) x[i][10]=ma(x,4,i,200);
            
            // 11 ma50 up rate
            if (i>=50) x[i][11]=100*(x[i][9]/x[i-1][9]-1);
            
            // 12 ma200 up rate
            if (i>=200) x[i][12]=100*(x[i][10]/x[i-1][10]-1);
            
            // 13 vma20
            if (i>=19) x[i][13]=ma(x,5,i,20);
            
            // 14 vma50
            if (i>=49) x[i][14]=ma(x,5,i,50);
            
            // 15 vma20 up rate
            if (i>=20) x[i][15]=100*(x[i][13]/x[i-1][13]-1);
            
            // 16 vma50 up rate
            if (i>=50) x[i][16]=100*(x[i][14]/x[i-1][14]-1);
            
            // 17 highest high in the past 20 days (today not included)
            if (i>=20) x[i][17]=highest(x,2,i,20);
            
            // 18 highest high in the past 50 days (today not included)
            if (i>=50) x[i][18]=highest(x,2,i,50);
            
            // 19 highest high in the past 200 days (today not included)
            if (i>=200) x[i][19]=highest(x,2,i,200);
            
            // 20 highest high (historical) (today not included)
            if (i>=1) {
                if (x[i-1][2]>historicalhigh) historicalhigh=x[i-1][2];
                x[i][20]=historicalhigh;
            }
            
            // 21 lowest low in the past 20 days (today not included)
            if (i>=20) x[i][21]=lowest(x,3,i,20);
            
            // 22 lowest low in the past 50 days (today not included)
            if (i>=50) x[i][22]=lowest(x,3,i,50);
            
            // 23 lowest low in the past 200 days (today not included)
            if (i>=200) x[i][23]=lowest(x,3,i,200);
            
            // 24 lowest low (historical) (today not included)
            if (i>=1) {
                if (x[i-1][3]<historicallow) historicallow=x[i-1][3];
                x[i][24]=historicallow;
            }
            
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            
            //25-84 ma21-ma80
            int k;
            for (k=25; k<85; k++) {
                if (i>=k-5) {
                    x[i][k]=ma(x,4,i,k-4);
                }
            }
            
            
            //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
            
            //
            
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
        j++;fclose(fi);
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
            j++;fclose(fi);
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
            j++;fclose(fi);
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
            j++;fclose(fi);
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
            j++;fclose(fi);
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
            j++;fclose(fi);
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
            j++;fclose(fi);
        }
        
    }
    
    //output status
    printf("Total searched file: %d\n",j);
}

//void filepreprocessIndividual(char s1[],char s2[])
//{
//    FILE *fi=NULL;  //file pointer for read
//    
//    int i,j=0;
//    char fdir[255]; //file directory
//    
//    char folderin[255];
//    char folderout[255];
//    
//    char b[255];
//    
//    sprintf(folderin,"/Volumes/DATA_0/2016/3Stock Analysis/1Data/%s/",s1);
//    sprintf(folderout,"/Volumes/DATA_0/2016/3Stock Analysis/1Data/%s/",s2);
//    
//    printf("File PreProcessing: %9s     \n",s2);
//    
//    //Indices
//
//    sprintf(fdir, "%sSH#999999.txt", folderin);	//SH999999
//    fi = fopen(fdir, "r");
//    if (fi != NULL)
//    {
//        sprintf(fdir, "%sSH#999999.txt", folderout);
//        process(fi,fdir);
//        j++;
//    }
//    fclose(fi);
//    
//    for (i = 700000; i < 700808; i++)
//    {
//        sprintf(b, "SH#%d.txt", i);                 //adjust the file name
//        b[3] = '0';
//        sprintf(fdir, "%s%s", folderin, b);			//create the file directory
//        fi = fopen(fdir, "r");
//        if (fi != NULL)
//        {
//            sprintf(fdir, "%s%s", folderout, b);
//            process(fi,fdir);
//            j++;
//        }
//        fclose(fi);
//    }
//    
//    for (i = 880305; i < 880561; i++)
//    {
//        sprintf(fdir, "%sSH#%d.txt", folderin, i);	//create the input file directory
//        fi = fopen(fdir, "r");
//        if (fi != NULL)
//        {
//            sprintf(fdir, "%sSH#%d.txt", folderout, i);
//            process(fi,fdir);
//            j++;
//        }
//        fclose(fi);
//    }
//    
//    for (i = 399001; i < 399942; i++)
//    {
//        sprintf(fdir, "%sSZ#%d.txt", folderin, i);	//create the input file directory
//        fi = fopen(fdir, "r");
//        if (fi != NULL)
//        {
//            sprintf(fdir, "%sSZ#%d.txt", folderout, i);
//            process(fi,fdir);
//            j++;
//        }
//        fclose(fi);
//    }
//    
//    //SH
//    for (i = 600000; i < 605000; i++)
//    {
//        sprintf(fdir, "%sSH#%d.txt", folderin, i);	//create the input file directory
//        fi = fopen(fdir, "r");
//        if (fi != NULL)
//        {
//            sprintf(fdir, "%sSH#%d.txt", folderout, i);
//            process(fi,fdir);
//            j++;
//        }
//        fclose(fi);
//    }
//
//    //SZ
//    for (i = 700000; i < 703000; i++)
//    {
//        sprintf(b, "SZ#%d.txt", i);                 //adjust the file name
//        b[3] = '0';
//        sprintf(fdir, "%s%s", folderin, b);			//create the file directory
//        fi = fopen(fdir, "r");
//        if (fi != NULL)
//        {
//            sprintf(fdir, "%s%s", folderout, b);
//            process(fi,fdir);
//            j++;
//        }
//        fclose(fi);
//    }
//    
//    //SZ-CYB
//    for (i = 300000; i < 301000; i++)
//    {
//        sprintf(fdir, "%sSZ#%d.txt", folderin, i);
//        fi = fopen(fdir, "r");
//        if (fi != NULL)
//        {
//            sprintf(fdir, "%sSZ#%d.txt", folderout, i);
//            process(fi,fdir);
//            j++;
//        }
//        fclose(fi);
//    }
//    
//    //output status
//    printf("Total searched file: %d\n",j);
//}

int main()
{
    
    //FPP just for Phase 9, add more ma values
    filepreprocess("3originalIndexData","6indexdata-FPP");
    
    //FPP: Individual
    //filepreprocessIndividual("1OriginalStockData(2016.1.15)","14Exceptions(temp)");
    
    //from original stockdata to standardstockdata(without EPS)
    //filepreprocess("1OriginalStockData(2016.1.15)","11StandardStockData(Mid-withoutEPS)");
    
    //from original indexdata to standardindexdata
    //filepreprocess("2OriginalIndexData(2016.1.15)","13StandardIndexData(Final)");
    
}
