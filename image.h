#pragma once
#include <vector>
#include <string>
#include <fstream>


int stretch256(float noise_val)
{
    return (int)(((noise_val+1)/2)*256);
}

std::string terrain_color(float noise_val)
{
    float water_max = -1;
    float grass_max = 0.9;
    //snowy_max = 1;
    int r=0, g=0, b=0;
    if(noise_val<water_max)
    {
        r=0;
        g=0;
        b=stretch256(noise_val/2);
    }
    else if(noise_val < grass_max)
    {
        r=0;
        g=stretch256(noise_val);
        b=0;
    }
    else
    {
        r=stretch256(noise_val/2);
        g=stretch256(noise_val);
        b=stretch256(noise_val/2);
    }
    std::string str = std::to_string(r)+" "+std::to_string(g)+" "+std::to_string(b);
    return str;

}

template <typename T>
void ppm2d(std::vector<std::vector<T>> noise, std::string color_scheme = "")
{
    std::ofstream fout("test.ppm");

    fout<<"P3"<<"\n";
    fout<<noise.size()<<" "<<noise[0].size()<<"\n";
    fout<<"255"<<"\n";

    for(auto n:noise)
    {
        for(auto m:n)
        {
            if(color_scheme == "terrain")
            {
                fout<<terrain_color(m)<<"\n";
            }
            else
            {
                fout<<(int)(((m+1)/2)*256)<<" "<<0<<" "<<0<<" "<<"\n";
            }
        }
    }
    fout.close();
}
