#include <stdio.h>
#include "image/Image.h"

int main(int argc, char* argv[]){
    TGA tga = TGA();
    tga.open("aaaaa");
    tga.printFileName();
    return 0;
}


