// WriteTransients.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "stdio.h"
#include "stdlib.h"
#include "shlwapi.h"

int iNumTrans = 1;
int iNumLines = 1;

int iLeftY=534;
int iLeftCb=253;
int iLeftCr=207;
int iLeftSize=50;

int iRightY=251;
int iRightCb=771;
int iRightCr=817;
int iRightSize=50;

int iNumYWrittenInLine=0;

unsigned short usTransY[10];
unsigned short usTransCb[5];
unsigned short usTransCr[5];

bool bWriteTransient(FILE *f)
{
	unsigned short usOut[4];

	for(int i=0; i < 5; i++)
	{
		unsigned short usCb = (unsigned short) usTransCb[i];
		unsigned short usY1 = (unsigned short) usTransY[i*2+0];
		unsigned short usCr = (unsigned short) usTransCr[i];
		unsigned short usY2 = (unsigned short) usTransY[i*2+1];

		usOut[0] = (usCb>>8) | (usCb<<8);// Cb 
		usOut[1] = (usY1>>8) | (usY1<<8);// Y 
		usOut[2] = (usCr>>8) | (usCr<<8);// Cr 
		usOut[3] = (usY2>>8) | (usY2<<8);// Y 

		fwrite(&usOut, sizeof(usOut), 1, f);
	}

	iNumYWrittenInLine+=10;

	return TRUE;
}


bool bWriteSustainedLeft(FILE *f)
{
	unsigned short usOut[4];
	unsigned short usCb = (unsigned short) iLeftCb;
	unsigned short usY = (unsigned short) iLeftY;
	unsigned short usCr = (unsigned short) iLeftCr;

	usOut[0] = (usCb>>8) | (usCb<<8);// Cb 
	usOut[1] = (usY>>8) | (usY<<8);// Y 
	usOut[2] = (usCr>>8) | (usCr<<8);// Cr 
	usOut[3] = (usY>>8) | (usY<<8);// Y 

	for(int i=0; i < iLeftSize; i+=2)
	{
		fwrite(&usOut, sizeof(usOut), 1, f);
		iNumYWrittenInLine+=2;
	}

	return TRUE;
}

bool bWriteSustainedRight(FILE *f)
{
	unsigned short usOut[4];
	unsigned short usCb = (unsigned short) iRightCb;
	unsigned short usY = (unsigned short) iRightY;
	unsigned short usCr = (unsigned short) iRightCr;

	usOut[0] = (usCb>>8) | (usCb<<8);// Cb 
	usOut[1] = (usY>>8) | (usY<<8);// Y 
	usOut[2] = (usCr>>8) | (usCr<<8);// Cr 
	usOut[3] = (usY>>8) | (usY<<8);// Y 

	for(int i=0; i < iLeftSize; i+=2)
	{
		fwrite(&usOut, sizeof(usOut), 1, f);
		iNumYWrittenInLine+=2;
	}

	return TRUE;
}


int main(int argc, char* argv[])
{
	char string [256];
	char string1 [256];
	char string2 [256];
    char path[MAX_PATH];
	FILE *fp;

	int k;

	if (argc < 2)
	{
		printf("Usage: WriteTransients.exe <ini_file_name>");
	    return 1;
	}

	GetModuleFileName(0,path,MAX_PATH);
	PathRemoveFileSpec(path);
//	strcat(path,"\\WriteTransients.ini");
	strcat(path,"\\");
	strcat(path,argv[1]);

	GetPrivateProfileString("Common", "NumTrans", "1", string, 10, path);
	iNumTrans = atoi(string);

	GetPrivateProfileString("Common", "NumLines", "1", string, 10, path);
	iNumLines = atoi(string);

	if ((fp=fopen("out.uyvy_be", "wb"))==NULL) {
		printf("Cannot open file.\n");
		exit (1);
	}

	for (int i=0; i<iNumLines; i++)
	{
		iNumYWrittenInLine=0;
		for(int j = 1; j < iNumTrans+1; j++)
		{
			sprintf(string1, "Transient%d", j);

			GetPrivateProfileString(string1, "LeftY", "0", string, 10, path);
			iLeftY = atoi(string);

			GetPrivateProfileString(string1, "LeftCb", "0", string, 10, path);
			iLeftCb = atoi(string);

			GetPrivateProfileString(string1, "LeftCr", "0", string, 10, path);
			iLeftCr = atoi(string);

			GetPrivateProfileString(string1, "LeftSz", "0", string, 10, path);
			iLeftSize = atoi(string);


			GetPrivateProfileString(string1, "RightY", "0", string, 10, path);
			iRightY = atoi(string);

			GetPrivateProfileString(string1, "RightCb", "0", string, 10, path);
			iRightCb = atoi(string);

			GetPrivateProfileString(string1, "RightCr", "0", string, 10, path);
			iRightCr = atoi(string);

			GetPrivateProfileString(string1, "RightSz", "0", string, 10, path);
			iRightSize = atoi(string);

            for(k=1; k <11; k++)
			{
				sprintf(string2, "Y%02d", k);
				GetPrivateProfileString(string1, string2, "0", string, 10, path);
			    usTransY[k-1] = atoi(string);
			}

            for(k=1; k <6; k++)
			{
				sprintf(string2, "Cb%02d", k);
				GetPrivateProfileString(string1, string2, "0", string, 10, path);
			    usTransCb[k-1] = atoi(string);
			}

	        for(k=1; k <6; k++)
			{
				sprintf(string2, "Cr%02d", k);
				GetPrivateProfileString(string1, string2, "0", string, 10, path);
			    usTransCr[k-1] = atoi(string);
			}

			bWriteSustainedLeft(fp);
			bWriteTransient(fp);
			bWriteSustainedRight(fp);
		}
	}

	printf("NumTrans= %d\n Imagesize=%dx%d\n",iNumTrans, iNumYWrittenInLine, iNumLines );
	return 0;
}

