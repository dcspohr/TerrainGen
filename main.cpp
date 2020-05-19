#include <iostream>
#include <chrono>

#include "image.h"
#include "FastNoise.h"
#include "terrain.h"



int main()
{
    std::cout<<"Starting generation..."<<std::endl;
    auto start = std::chrono::high_resolution_clock::now();

    Terrain map = Terrain(FastNoise::Simplex);
    map.rain(1000000);
    ppm2d(map.get_vector(), "terrain");

    auto finish = std::chrono::high_resolution_clock::now();
    std::cout<<"Done.\nExecution time: "<<std::chrono::duration_cast<std::chrono::milliseconds>(finish-start).count()<<"ms"<<std::endl;
    return 0;
}
