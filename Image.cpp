//
// Created by floodd on 23/03/2022.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Image.h"
#include <algorithm>
#include <Windows.h>
using namespace std;
using std::min;

bool Image::load(string filename)
{
    std::ifstream ifs;
    ifs.open(filename, std::ios::binary);

    try {
        if (ifs.fail()) {
            throw("Can't open input file");
        }
        std::string header;
        int w, h, b;
        ifs >> header;
        if (strcmp(header.c_str(), "P6") != 0) throw("Can't read input file");
        ifs >> w >> h >> b;
        this->w = w;
        this->h = h;
        this->pixels = new Rgb[w * h];
        ifs.ignore(256, '\n');
        unsigned char pix[3];
        for (int i = 0; i < w * h; ++i) {
            ifs.read(reinterpret_cast<char *>(pix), 3);
            this->pixels[i].r = pix[0];
            this->pixels[i].g = pix[1];
            this->pixels[i].b = pix[2];
        }
        ifs.close();
    }
    catch (const char err) {
        fprintf(stderr, "%s\n", err);
        ifs.close();
        return false;
    }

    return true;
}
bool Image::loadRaw(string filename)
{
    return false;
}
bool Image::savePPM(string filename)
{
    if (w == 0 || h == 0) { fprintf(stderr, "Can't save an empty image\n"); return false; }
    std::ofstream ofs;
    try {
        ofs.open(filename, std::ios::binary);
        if (ofs.fail()) throw("Can't open output file");
        ofs << "P6\n" << w << " " << h << "\n255\n";
        unsigned char r, g, b;

        for (int i = 0; i < w * h; ++i) {
            r = (pixels[i].r);
            g = (pixels[i].g);
            b = (pixels[i].b);
            ofs << r << g << b;
        }
        ofs.close();
    }
    catch (const char *err) {
        fprintf(stderr, "%s\n", err);
        ofs.close();
        return false;
    }
    return true;

}


void Image::filterRed()
{
    for (int c = 0; c < w * h; c++) {
        this->pixels[c].g = 0;
        this->pixels[c].b = 0;
    }
}
void Image::filterGreen()
{
    for (int c = 0; c < w * h; c++) {
        this->pixels[c].r = 0;
        this->pixels[c].b = 0;
    }
}
void Image::filterBlue()
{
    for (int c = 0; c < w * h; c++) {
        this->pixels[c].g = 0;
        this->pixels[c].r = 0;
    }
}
void Image::greyScale()
{
    for (int i = 0; i < w * h; ++i) {
        int gray = (pixels[i].r + pixels[i+1].g + pixels[i+2].b)/3;
        memset(pixels+i, gray, 3);
    }
}

// https://www.youtube.com/watch?v=Yn_8KXuBXMc - Source
void Image::flipHorizontal()
{
    int pixels[3];
    unsigned int img1;
    unsigned int img2;
    for(int y= 0; y < h; ++y)
    {
        for(int x =0; x <w/2; ++x)
        {
            img1 = x + y * w;
            img2 = (w - 1 - x) + y * w;

            pixels[0] = this->pixels[img1].r;
            pixels[1] = this->pixels[img1].g;
            pixels[2] = this->pixels[img1].b;

            this->pixels[img1] = this->pixels[img2];

            this->pixels[img2].r = pixels[0];
            this->pixels[img2].g = pixels[1];
            this->pixels[img2].b = pixels[2];
        }
    }
}

// https://www.youtube.com/watch?v=Yn_8KXuBXMc - Source
void Image::flipVertically()
{
    int pixels[3];
    unsigned int img1;
    unsigned int img2;
    for(int x= 0; x < w; ++x)
    {
        for(int y =0; y <h/2; ++y)
        {
            img1 = x + y * w;
            img2 = x + (h - 1 - y) * w;

            pixels[0] = this->pixels[img1].r;
            pixels[1] = this->pixels[img1].g;
            pixels[2] = this->pixels[img1].b;

            this->pixels[img1] = this->pixels[img2];

            this->pixels[img2].r = pixels[0];
            this->pixels[img2].g = pixels[1];
            this->pixels[img2].b = pixels[2];
        }
    }
}
void Image::AdditionalFunction2()
{

}
void Image::AdditionalFunction3()
{

}
void Image::AdditionalFunction1()
{
    for (int c = 0; c < w * h; c++) {
        this->pixels[c].g = 25;
    }
}

/* Functions used by the GUI - DO NOT MODIFY */
int Image::getWidth()
{
    return w;
}

int Image::getHeight()
{
    return h;
}

Rgb* Image::getImage()
{
    return pixels;
}