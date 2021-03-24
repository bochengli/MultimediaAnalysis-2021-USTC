
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include"bmp.h"
void rgb_to_yuv(unsigned char* rgbBuf, unsigned char* yBuf, unsigned char* uBuf, unsigned char* vBuf, int Width, int Height)
{
	int y = 0;
	for (int i = 0; i < Width * Height * 3; i = i + 3)
	{
		yBuf[y] = 0.114 * rgbBuf[i] + 0.587 * rgbBuf[i+1] + 0.299 * rgbBuf[i+2];
		if (yBuf[y] > 235)
			yBuf[y] = 235;
		if (yBuf[y] < 16)
			yBuf[y] = 16;
		y++;
	}
	int u = 0, v = 0;
	for (int i = 0; i < Width * Height * 3;)
	{
		uBuf[u] = 0.5 * (rgbBuf[i] + rgbBuf[i + 3] + rgbBuf[i + Width * 3] + rgbBuf[i + Width * 3 + 3])/4
			- 0.3316 * (rgbBuf[i + 1] + rgbBuf[i + 4] + rgbBuf[i + Width * 3 + 1] + rgbBuf[i + Width * 3 + 4])/4
			- 0.1684 * (rgbBuf[i + 2] + rgbBuf[i + 5] + rgbBuf[i + Width * 3 + 2] + rgbBuf[i + Width * 3 + 5])/4 + 128;
		vBuf[v] = -0.083 * (rgbBuf[i] + rgbBuf[i + 3] + rgbBuf[i + Width * 3] + rgbBuf[i + Width * 3 + 3])/4
			- 0.4187 * (rgbBuf[i + 1] + rgbBuf[i + 4] + rgbBuf[i + Width * 3 + 1] + rgbBuf[i + Width * 3 + 4])/4
			+ 0.5 * (rgbBuf[i + 2] + rgbBuf[i + 5] + rgbBuf[i + Width * 3 + 2] + rgbBuf[i + Width * 3 + 5])/4 + 128;
		u++;
		v++;
		if (uBuf[u] > 240)
			uBuf[u] = 240;
		if (uBuf[u] < 16)
			uBuf[u] = 16;
        if (vBuf[v] > 240)
			vBuf[v] = 240;
		if (vBuf[v] < 16)
			vBuf[v] = 16;
		if ((i / 3) % 256 == 254)
			i = i + 258 * 3;
		else
			i = i + 6;
	}
}

int main()
{
    unsigned char* rgbBuf,*yBuf,*vBuf,*uBuf;
    FILE * fpBMP, *fpOutput;
    BITMAPFILEHEADER *fileHeader;
    BITMAPINFOHEADER *infoHeader;
    if ((fpBMP = fopen("test.bmp", "rb")) == NULL)
    {
        printf("FAILED TO OPEN FILE");
        exit(0);
    }
    if ((fpOutput = fopen("sampleoutput.yuv", "wb")) == NULL)
    {
        printf("FAILED TO CREATE FILE");
        exit(0);
    }
    fileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    infoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    fread(fileHeader, sizeof(BITMAPFILEHEADER), 1, fpBMP);
    fread(infoHeader, sizeof(BITMAPINFOHEADER), 1, fpBMP);
    fileHeader->bfOffBits = sizeof( BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD);
    fileHeader->bfSize = fileHeader->bfOffBits + infoHeader->biSizeImage;
    rgbBuf = (unsigned char *)malloc(sizeof (char) * (infoHeader->biHeight * infoHeader->biWidth * 3));
    yBuf = (unsigned char *)malloc(sizeof (char) * (infoHeader->biWidth * infoHeader->biHeight));
	uBuf = (unsigned char *)malloc(sizeof (char) * (infoHeader->biWidth * infoHeader->biHeight / 4));
	vBuf = (unsigned char *)malloc(sizeof (char) * (infoHeader->biWidth * infoHeader->biHeight / 4));
    fread(rgbBuf, sizeof(unsigned char), (infoHeader->biHeight * infoHeader->biWidth * 3), fpBMP);
    rgb_to_yuv(rgbBuf, yBuf, uBuf, vBuf, infoHeader->biWidth, infoHeader->biHeight);
    fwrite(yBuf, sizeof(unsigned char), infoHeader->biWidth * infoHeader->biHeight, fpOutput);
	fwrite(uBuf, sizeof(unsigned char), infoHeader->biWidth * infoHeader->biHeight / 4,fpOutput);
	fwrite(vBuf, sizeof(unsigned char), infoHeader->biWidth * infoHeader->biHeight / 4, fpOutput);
    free(fileHeader);
    free(infoHeader);
    fclose(fpBMP);
    fclose(fpOutput);
    printf("CONVERTION DONE.\n");
    return 0;
}