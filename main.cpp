
#include <iostream>
#include "Color.h"
#include "Raster.h"
using namespace std;

    int main()
    {
        Raster copy= Raster(12,12,Green);
        copy.drawLine_DDA(1,8,-5,15,Red);
        copy.drawLine_DDA(3,8,-5,15,Red);
        copy.drawLine_DDA(5,9,-5,15,Red);
        copy.writeToPPM();
        }
