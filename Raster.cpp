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


//some code taken/adapted from video tutorial "https://www.youtube.com/watch?v=6byB1jX3Fnk" 
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
    float dx= x2-x1;
    float dy= y2-y1;
    float m = dy/dx;
    swap(x1,y1,x2,y2,m);
    check(x1,y1,x2,y2,m);
    std::cout<<"m:"<<m<<std::endl;
    std::cout<<"X1: "<<x1<<" Y1: "<<y1<<" X2: "<<x2<<" Y2: "<< y2<<std::endl;
    if(fabs(m)<=1){
        std::cout<<"X:"<<x1<<std::endl;
        float y = y1;
        for(int x=x1; x<=float(round(x2)); x++){
            setColorPixel(x, float(round(y)), pFillColor);
            y+=m;
        }
        std::cout<<"Using y=mx+b"<<std::endl;
    }
    else{
        float x=x1;
        m = dx/dy;
        for(int y=y1; y>=float(round(y2)); y--){
            setColorPixel(float(round(x)), y, pFillColor);
            x-=m;
        }
        std::cout<<"Using x=my+b"<<std::endl;
    }

}

void Raster::swap(float& x1, float& y1, float& x2, float& y2, float m){
    if(fabs(m)>1){
        if(y2>y1){
            std::swap(x1,x2);
            std::swap(y1,y2);
        }
    }
    else{
        std::cout<<"slope is less than 1"<<std::endl;
        if(x1>x2){
            std::swap(x1,x2);
            std::swap(y1,y2);
        }
    }
}

void Raster::check(float& x1, float& y1, float& x2, float& y2, float m){
    //calculate the y and x intercepts depending on the slope
    float xIntercept;
    float yIntercept;
    std::cout<<"Entered the check method"<<std::endl;
    //for the formula y=mx+b
    if(fabs(m)<=1){
        yIntercept= y1 - m*x1;
        xIntercept= -yIntercept/m;
        std::cout<<"xintercept:"<<xIntercept<<std::endl;
        std::cout<<"yintercept:"<<yIntercept<<std::endl;
        if(x1<0 && y1>0){
            x1=0;
            y1= yIntercept;
            std::cout<<"x1 is less than 0 and y1 is greater than 0"<<std::endl;
        }
        if(x1<0&&y1<0&&yIntercept>=0){
            x1=0;
            y1= yIntercept;
            std::cout<<"x1 is less than 0 and y1 is less than 0 and Xintercept is greater than 0"<<std::endl;
        }
        if(x1<0&&y1<0&&yIntercept<=0){
            x1=xIntercept;
            y1= 0;
            std::cout<<"x1 is less than 0 and y1 is less than 0 and Xintercept is less than 0"<<std::endl;
        }
        if(x2>=width&&y2<0){
            x2=width-1;
            y2= m*width + yIntercept;
            std::cout<<"x2 is greater than width and y2 is less than 0"<<std::endl;
        }
        if(y1>=height&&x1<0){
            y1=height;
            x1= (height-yIntercept)/m;
            std::cout<<"y1 is greater than height and x1 is less than 0"<<std::endl;
        }
        if(y2<0&&x2<width){
            y2=0;
            x2= (0-yIntercept)/m;
            std::cout<<"y2 is less than 0 and x2 is less than width"<<std::endl;
        }
        if(x2>=width&&y2<=height){
            x2=width-1;
            y2= m*width + yIntercept;
            std::cout<<"x2 is greater than width and y2 is less than or equal to height"<<std::endl;
        }
        if(x2>=width&&y2>=height){
            x2=width-1;
            y2=m*width + yIntercept;
            std::cout<<"x2 is greater than width and y2 is greater than height"<<std::endl;
        }
    }
    //for the formula x=my+b
    else{
        m=(x1-x2)/(y1-y2);
        xIntercept= x1 - m*y1;
        yIntercept= -xIntercept/m;
        std::cout<<"xintercept:"<<xIntercept<<std::endl;
        std::cout<<"yintercept:"<<yIntercept<<std::endl;
        std::cout<<"m-corrected:"<<m<<std::endl;
        if(x2<0&&y2>0&&xIntercept>=0){
            x2= xIntercept;
            y2=0;
            std::cout<<"x2 is less than 0 and y2 is greater than 0 and xintercept is greater than 0"<<std::endl;
        }
        if(x2<0&&y2>0&&xIntercept<0){
            x2=0;
            y2= yIntercept;
            std::cout<<"x2 is less than 0 and y2 is greater than 0 and Xintercept is less than 0"<<std::endl;
        }
        if(x2<0&&y2<0&&yIntercept>=0){
            x2=0;
            y2= yIntercept;
            std::cout<<"x2 is less than 0 and y2 is less than 0 and the yintercept is greater than 0"<<std::endl;
        }
        else if(x2<0&&y2<0&&yIntercept<0){
            x2= xIntercept;
            y2=0;
            std::cout<<"x2 is less than 0 and y2 is less than 0 and yintercept is less than 0"<<std::endl;
        }
        if(x2>=width&&y2<0){
            x2= width-1;
            y2= (x2-xIntercept)/m;
            std::cout<<"x1 is greater than width and y1 is less than 0"<<std::endl;
        }
        if(y2>=height&&x2<0){
            y2=height;
            x2= m*height + xIntercept;
            std::cout<<"y2 is greater than height and x2 is less than 0"<<std::endl;
        }
        if(y1<0&&x1<width){
            y1=height;
            x1= m*height + xIntercept;
            std::cout<<"y1 is less than 0 and x1 is less than width"<<std::endl;
        }
        if(y1>=height&&x1>=width&&(m*height + xIntercept)<height){
            y1=height;
            x1= m*height + xIntercept;
            std::cout<<"y1 is greater than height and x1 is greater than width"<<std::endl;
        }
        if(y1>=height&&x1>=width&&(m*height + xIntercept)>height){
            y1=(height-xIntercept)/m;
            x1=width-1;
            std::cout<<"y1 is greater than height and x1 is greater than width"<<std::endl;
        }
        if(x1<0&&y1>=height&&yIntercept<height){
            x1=0;
            y1= yIntercept;
            std::cout<<"x1 is less than 0 and y1 is greater than height"<<std::endl;
        }
        if(x1<0&&y1>=height&&yIntercept>height){
            x1= (height-yIntercept)/m;
            y1=height;
            std::cout<<"x1 is less than 0 and y1 is greater than height"<<std::endl;
        }
    }
}
