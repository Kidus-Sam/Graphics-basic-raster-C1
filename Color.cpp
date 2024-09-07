#include <iostream>
#include <cmath>
#include "Color.h"
using namespace std;

    float red;
    float green;
    float blue;

    Color::Color(){
        red = 0.0f;
        green = 0.0f;
        blue = 0.0f;
    }
    Color::Color(float pred, float pgreen, float pblue){
        red = pred;
        green = pgreen;
        blue = pblue;
    }

    void Color::clamp(){
        //brute force method
        // if(red>1.0f){
        //     red = 1.0f;
        //     }
        // if(green>1.0f){
        //     green=1.0f;
        // }
        // if(blue>1.0f){
        //     blue=1.0f;
        // }
        // if(red<0.0f){
        //     red=0.0f;
        // }
        // if(green<0.0f){
        //     green=0.0f;
        // }
        // if(blue<0.0f){
        //     blue=0.0f;
        // }

        //better method
        red = fmin( red ,1.0f);
        red = fmax( red ,0.0f);
        green = fmin( green ,1.0f);
        green = fmax( green ,0.0f);
        blue = fmin(blue, 1.0f);
        blue= fmax(blue, 0.0f);
    }

    Color Color::operator+(const Color& color){
        Color newColor;
        newColor.red = red + color.red;
        newColor.green = green + color.green;
        newColor.blue = blue + color.blue;
        newColor.clamp();
        return newColor;
    }
    Color Color::operator-(const Color& color){
        Color newColor;
        newColor.red = red - color.red;
        newColor.green = green - color.green;
        newColor.blue = blue - color.blue;
        newColor.clamp();
        return newColor;
    }
    Color Color::operator*(const float& scalar){
        Color newColor;
        newColor.red = red * scalar;
        newColor.green = green * scalar;
        newColor.blue = blue * scalar;
        newColor.clamp();
        return newColor;
    }

