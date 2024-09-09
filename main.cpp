
#include <iostream>
#include "Color.h"
#include "Raster.h"
using namespace std;

    int main()
    {
        Raster copy= Raster(12,12,Green);
        copy.drawLine_DDA(-2,-2,5,5,Red);
        copy.writeToPPM();
        }
