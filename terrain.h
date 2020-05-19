#include <vector>
#include <random>

#define Hmap std::vector<std::vector<double>>
class Terrain
{
    public:
    const static int SIZE = 512;
    //std::vector<std::vector<double>> heightmap;
    double heightmap[SIZE][SIZE] ;
    Terrain(FastNoise::NoiseType nt, int seed = -1)
    {
        if (seed == -1)
        {
            srand(time(NULL));
            seed = rand()%1000;
        }

        FastNoise noisy;
        noisy.SetSeed(seed);
        noisy.SetNoiseType(nt);

        //heightmap = std:(SIZE, std::vector<double> (SIZE, 0));

        for (int x = 0; x < SIZE; x++)
        {
            for (int y = 0; y < SIZE; y++)
            {
                heightmap[x][y] = noisy.GetNoise(x,y);
                heightmap[x][y] += noisy.GetNoise(x*2,y*2)/2;
                heightmap[x][y] += noisy.GetNoise(x*4,y*4)/4;
                heightmap[x][y] += noisy.GetNoise(x*8,y*8)/8;
            }
        }
    }


    //@void get_lowest_direction: sets low_x and low_y as a discrete vector for raindrop descent
    void get_lowest_direction(int x, int y, int& low_x, int& low_y)
    {
        double min = 9999;

        //check surrounding tiles for descent
        //if offset == 0, 0: local minimum reached
        for(int i=-1; i<2; i++)
        {
            for (int j=-1; j<2; j++)
            {
                //keep x+i and y+j bounded to heightmap grid
                if(x+i < SIZE && x+i >= 0   &&   y+i < SIZE && y+i >= 0)
                {
                    //if neighbor tile is lower
                    if(heightmap[x+i][y+j] < min)
                    {
                        min = heightmap[x+i][y+j];
                        low_x = x+i;
                        low_y = y+j;
                    }
                }
            }
        }
        return;
    }

    void droplet(int x, int y)
    {
        int low_x =-1, low_y=-1;
        //int curr_x = x, curr_y = y;

        while(1)
        {
            get_lowest_direction(x, y, low_x, low_y);

            if(low_x == x && low_y == y)
            {
                //evaporate
                break;
            }
            else //(low_x != 0 || low_y != 0)
            {
                //scrape terrain
                //std::cout<<x<<" "<<y<<std::endl;//" "<<" != "<<low_x<<" "<<low_y<<std::endl;
                heightmap[x][y] -= (heightmap[x][y]-heightmap[low_x][low_y])/10;
                //heightmap[x][y]  = .999999;
            }
            x = low_x;
            y = low_y;
        }
    }

    void rain(int drops)
    {
        for(int i=0; i<drops; i++)
        {
            int randx = rand()%SIZE;
            int randy = rand()%SIZE;
            droplet(randx, randy);
        }
    }

    Hmap get_vector()
    {
        std::vector<std::vector<double>> h(SIZE, std::vector<double> (SIZE, 0));
        for(int i=0; i<SIZE; i++)
        {
            for(int j=0; j<SIZE; j++)
            {
                h[i][j] = heightmap[i][j];
            }
        }
        return h;
    }
};
