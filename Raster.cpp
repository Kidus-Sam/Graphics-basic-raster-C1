#include "Color.h"
#include "Raster.h"
#include <iostream>
#include <fstream>
#include <cmath>
Raster::Raster(){
    width = 0;
    height = 0;
}

Raster::Raster(int pWidth, int pHeight, Color pFillColor){
    width = pWidth;
    height = pHeight;
    pixels = new Color[width*height];
    for(int i = 0; i < width*height; i++){
        pixels[i] = pFillColor;
    }
}

Raster::~Raster(){
    delete[] pixels;
}

int Raster::getWidth(){
    return width;
}

int Raster::getHeight(){
    return height;
}

Color Raster::getColorPixel(int x, int y){
    int origin= (width*height)-width;
    return pixels[origin + x - (y*width)];
}

void Raster::setColorPixel(int x, int y, Color pFillColor){
    int origin= (width*height)-width;
    pixels[origin + x - (y*width)]=pFillColor;
}

void Raster::clear(Color pFillColor){
    for(int i = 0; i < width*height; i++){
        pixels[i] = pFillColor;
    }
}


//some code taken/adapted from video tutorial "" 
void Raster::writeToPPM(){
    std::ofstream fout("FRAME_BUFFER.ppm");
    if(fout.fail()){std::cout<<"The file could not be opened."<<std::endl; exit(1);}
    fout<<"P3"<<std::endl;
    fout<<width<<" "<<height<<std::endl;
    fout<<"255"<<std::endl;
    for(int i = height-1; i >=0; i--){
        for(int j = 0; j <width; j++){
            Color temp = getColorPixel(j, i);
            fout<<int(temp.red*255)<<" "<<int(temp.green*255)<<" "<<int(temp.blue*255)<<" ";
        }
        fout<<std::endl;
    }
}


void Raster::drawLine_DDA(float x1, float y1, float x2, float y2, Color pFillColor){
    swap(x1,y1,x2,y2);
    float dx= x2-x1;
    float dy= y2-y1;
    float m = dy/dx;
    
    if(abs(m)<=1){
        float y = y1;
        for(int x=x1; x<=x2; x++){
            setColorPixel(x, y, pFillColor);
            y+=m;
        }
    }
    else{
        float x=x1;
        m = dx/dy;
        for(int y=y1; y<=y2; y++){
            setColorPixel(x, y, pFillColor);
            x+=m;
        }
    }

}

void Raster::swap(float& x1, float& y1, float& x2, float& y2){
    if(x1>x2){
        float temp = x1;
        x1 = x2;
        x2 = temp;
        temp = y1;
        y1 = y2;
        y2 = temp;
    }
}