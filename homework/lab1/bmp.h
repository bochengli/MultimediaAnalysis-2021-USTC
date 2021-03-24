
# ifndef BMP_H
# define BMP_H

#pragma pack(1)
typedef struct tagBITMAPFILEHEADER
{
    unsigned char  bfType[2];     
    unsigned int   bfSize;        
    unsigned short bfReserved1;   
    unsigned short bfReserved2;   
    unsigned int   bfOffBits;     
}BITMAPFILEHEADER;
#pragma pack()

#pragma pack(1)
typedef struct tagBITMAPINFOHEADER
{
    unsigned int    biSize;          
    long            biWidth;         
    long            biHeight;        
    unsigned short  biPlanes;        
    unsigned short  biBitCount;      
    unsigned int    biCompression;   
    unsigned int    biSizeImage;     
    long            biXPelsPerMeter; 
    long            biYPelsPerMeter; 
    unsigned int    biClrUsed;       
    unsigned int    biClrImportant;  
}BITMAPINFOHEADER;
#pragma pack()

#pragma pack(1)
typedef struct tagRGBQUAD
{
    unsigned char rgbBlue;   
    unsigned char rgbGreen;  
    unsigned char rgbRed;    
    unsigned char rgbReserved;
}RGBQUAD;
#pragma pack()

#endif