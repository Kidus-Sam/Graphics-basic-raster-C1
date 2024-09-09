#ifndef RASTER_H
#define RASTER_H
#include "Color.h"
class Raster{
    private:
        int width;
        int height;
    public:
        Color* pixels;
        Raster();
        Raster(int pwidth, int pheight, Color pfillColor);
        ~Raster();
        int getWidth();
        int getHeight();
        Color getColorPixel(int x, int y);
        void setColorPixel(int x, int y, Color pFillColor);
        void clear(Color pFillColor);
        void writeToPPM();
        void drawLine_DDA(float x1, float y1, float x2, float y2, Color pFillColor);
        void swap(float& x1, float& y1, float& x2, float& y2, float m);
        void check(float& x1, float& y1, float& x2, float& y2, float m);


};







#endif