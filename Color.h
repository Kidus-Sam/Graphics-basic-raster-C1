#ifndef COLOR_H
#define COLOR_H
#define Red Color(1.0, 0.0, 0.0)
#define Green Color(0.0, 1.0, 0.0)
#define Blue Color(0.0, 0.0, 1.0)
#define Black Color(0.0, 0.0, 0.0)
#define White Color(1.0, 1.0, 1.0)
struct Color{
    private:
    public:
        float red;
        float green;
        float blue;
        Color();
        Color(float pred, float pgreen, float pblue);
        void clamp();
        Color operator+(const Color& color);
        Color operator-(const Color& color);
        Color operator*(const float& scalar);
};





#endif