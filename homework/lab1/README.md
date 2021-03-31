# Assignment 1
Convert a `.bmp` file into `.yuv` file. Change its colorspace from RGB to YUV.
* Note: You are not allowed to use any package func such as `cv.imread`, `cv2.cvtColor()`.
* Deadline for 2 weeks.
## Get Started
* Open Windows Terminal
* `cd \path_to_the_project\homework\lab1\` direct to the program.
* `$ gcc conversion.c` to compile.
* Input the name of source image (in `.bmp` format) and the output image (whatever you want, better in `.yuv` format or the program won't recognize). Sample script: `$ .\conversion.exe test.bmp out.yuv`
* Check the output image in `yuvplayer`. You may download it here: https://nchc.dl.sourceforge.net/project/raw-yuvplayer/yuvplayer-2.5.zip
* As for my test image (`test.bmp`), set the size to **WQVGA** (416x240), and the color to **YUV420** (which means in the YUV color space, Y:U:V is 4:2:0).
* See the result.
> Note: Inappropriate setting in `yuvplayer` may cause torn image output.
## Sample Output
### test.bmp

![test.bmp](/homework/lab1/images/test.bmp)

### out.yuv

<img src="/homework/lab1/images/out.png" alt="out.yuv" style="zoom: 50%;" />
