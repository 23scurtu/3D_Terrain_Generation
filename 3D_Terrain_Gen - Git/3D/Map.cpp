#include <iostream>
#include "Map.h"
#include <vector>
#include <time.h>

using namespace std;

Map::Map(int x, int y)
{
    this->x = x;
    this->y = y;
    totalsize = x* y;

	vector<float> tempvec;

    for(int i = 0; i != y; i++)
    {
        elements.push_back(tempvec);

        for(int j = 0; j != x; j++)
        {
            elements[i].push_back(0);
        }
    }
}

Map::Map(vector<vector<float> > input, int x, int y)
{
    this->x = x;
    this->y = y;//change to be autommatic
    totalsize = x* y;

    elements= input;


}

void Map::display(){
    for(int i = 0; i != y; i++)
    {
        for (int u = 0; u != x; u++)
        {

            cout << elements[i][u];
        }
        cout << endl;
    }

}

bool Map::isedge(int x, int y)
{
    if (x == this->x -1 || y == this->y -1 || x == 0 || y==0) return true;
    else return false;

}

bool Map::isPastEdge(int x, int y)
{
	if (x > this->x - 1 || y > this->y - 1 || x < 0 || y < 0) return true;
	else return false;
}


void Map::clearElements() //optimize //maybe make zero map
{
  for(int ry = 0; ry != y; ry++)
    {
        for (int rx = 0; rx != x; rx++)
        {
            elements[ry][rx] = 0;
        }
    }
}

int Map::getX()
{
    return x;
}

int Map::getY()
{
    return y;
}

int Map::getTotalsize()
{
	return totalsize;
}
vector<vector<float> > Map::getElements()
{
    return elements;

}
void Map::setElement(int x, int y, int val)
{
    elements[y][x] = val;
}
float Map::getElement(int x, int y)
{
	return elements[y][x];
}

void Map::loadElements(vector<vector<float> > input) //maybe also do new equal to and new clear?
{
    elements = input;
}

void Map::square(int x, int y, int size, int offset)
{
	elements[y][x] = (elements[y + size][x + size] +
		elements[y - size][x - size] +
		elements[y + size][x - size] +
		elements[y - size][x + size]) / 4 + offset;
}

void Map::diamond(int x, int y, int size, int offset)
{
	if (x - size < 0)
	{
		elements[y][x] = (elements[y][x + size] +
			elements[y + size][x] +
			elements[y - size][x]) / 3 + offset;
	}
	else if (x + size > this->x - 1)
	{
		elements[y][x] = (elements[y][x - size] +
			elements[y + size][x] +
			elements[y - size][x]) / 3 + offset;
	}
	else if (y - size < 0)
	{
		elements[y][x] = (elements[y][x + size] +
			elements[y][x - size] +
			elements[y + size][x]) / 3 + offset;
	}
	else if (y + size > this->y - 1)
	{
		elements[y][x] = (elements[y][x + size] +
			elements[y][x - size] +
			elements[y - size][x]) / 3 + offset;
	}
	else
	{
		elements[y][x] = (elements[y ][x + size] +
			elements[y][x - size] +
			elements[y + size][x] +
			elements[y - size][x]) / 4 + offset;
	} // optomize so not going through all 4 before this 

}
void Map::generate(int size, int roughness) //size is just x but make x better first, sidelength
{
	srand(time(NULL));
	int squaresize = (size - 1) / 2;

	while(squaresize>0)//for(int i = 0; i < (size); i = i+2) //fix to a for loop
	{
		for (int y= 0; y < size/(squaresize*2); y++)
		{
			for (int x = 0; x < size / (squaresize * 2 ); x++)
			{
				square((x*squaresize * 2) + squaresize, 
					   (y*squaresize * 2 ) + squaresize, 
					   squaresize, 
					   rand() % roughness*squaresize*2 - squaresize*roughness);
			}
		}
		
		int rowtype = 1;

		for (int y = 0; y < size; y += squaresize)//follows diff for loop logic then square 
		{
			if (rowtype == 1)
			{
				for (int x = squaresize; x < size; x += 2*squaresize)
				{
					diamond(x, y, squaresize, rand() % roughness*squaresize * 2 - squaresize);
				}
			}
			if (rowtype == -1)
			{
				for (int x = 0; x < size; x += squaresize*2)
				{
					diamond(x, y, squaresize, rand() % roughness*squaresize * 2 - squaresize);
				}
			}
			rowtype *= -1;
		}

		squaresize *= 0.5;
	}
}

void Map::generate(int size, float roughness) //size is just x but make x better first, sidelength
{
	srand(time(NULL));
	int squaresize = (size - 1) / 2;

	while (squaresize>0)//for(int i = 0; i < (size); i = i+2) //fix to a for loop
	{
		for (int y = 0; y < size / (squaresize * 2); y++)
		{
			for (int x = 0; x < size / (squaresize * 2); x++)
			{
				square((x*squaresize * 2) + squaresize,
					(y*squaresize * 2) + squaresize,
					squaresize,
					rand() % int(squaresize*roughness * 2) - squaresize*roughness);
			}
		}

		int rowtype = 1;

		for (int y = 0; y < size; y += squaresize)//follows diff for loop logic then square 
		{
			if (rowtype == 1)
			{
				for (int x = squaresize; x < size; x += 2 * squaresize)
				{
					diamond(x, y, squaresize, rand() % int(squaresize*roughness * 2) - squaresize*roughness);
				}
			}
			if (rowtype == -1)
			{
				for (int x = 0; x < size; x += squaresize * 2)
				{
					diamond(x, y, squaresize, rand() % int(squaresize*roughness * 2) - squaresize*roughness);
				}
			}
			rowtype *= -1;
		}

		squaresize /= 2;
	}
}

//generates with caps during generation, both set up for time randomsness, not generated
void Map::generate(int size, int roughness, int min, int max) //size is just x but make x better first, sidelength
{
	srand(time(NULL));
	
	int random;
	int squaresize = (size - 1) / 2;

	while (squaresize>0)//for(int i = 0; i < (size); i = i+2) //fix to a for loop
	{
		for (int y = 0; y < size / (squaresize * 2); y++)
		{
			for (int x = 0; x < size / (squaresize * 2); x++)
			{
				random = rand() % roughness*squaresize * 2 - squaresize*roughness;
				if (random > max) random = max;
				else if (random < min) random = min;

				square((x*squaresize * 2) + squaresize,
					(y*squaresize * 2) + squaresize,
					squaresize,
					random);
			}
		}

		int rowtype = 1;

		for (int y = 0; y < size; y += squaresize)//follows diff for loop logic then square 
		{

			if (rowtype == 1)
			{
				for (int x = squaresize; x < size; x += 2 * squaresize)
				{
					random = rand() % roughness*squaresize * 2 - squaresize*roughness;
					if (random > max) random = max;
					else if (random < min) random = min;

					diamond(x, y, squaresize, random);
				}
			}
			if (rowtype == -1)
			{
				for (int x = 0; x < size; x += squaresize * 2)
				{
					random = rand() % roughness*squaresize * 2 - squaresize*roughness;
					if (random > max) random = max;
					else if (random < min) random = min;

					diamond(x, y, squaresize, random);
				}
			}
			rowtype *= -1;
		}
		squaresize /= 2;
	}
} 

void Map::generate(int size, float mag, float roughness) //size is just x but make x better first, sidelength
{
	srand(time(NULL));
	int squaresize = (size - 1) / 2;

	while (squaresize>0)//for(int i = 0; i < (size); i = i+2) //fix to a for loop
	{
		for (int y = 0; y < size / (squaresize * 2); y++)
		{
			for (int x = 0; x < size / (squaresize * 2); x++)
			{
				square((x*squaresize * 2) + squaresize,
					(y*squaresize * 2) + squaresize,
					squaresize,
					rand() % int(2 * mag) - mag);
			}
		}

		int rowtype = 1;

		for (int y = 0; y < size; y += squaresize)//follows diff for loop logic then square 
		{
			if (rowtype == 1)
			{
				for (int x = squaresize; x < size; x += 2 * squaresize)
				{
					diamond(x, y, squaresize, rand() % int(2 * mag) - mag);
				}
			}
			if (rowtype == -1)
			{
				for (int x = 0; x < size; x += squaresize * 2)
				{
					diamond(x, y, squaresize, rand() % int(2 * mag) - mag);
				}
			}
			rowtype *= -1;
		}

		mag *= roughness;
		squaresize *= 0.5;
	}
}

void Map::capData(int lower, int upper)
{
	for (int y = 0; y < this->y; y++)
	{
		for (int x = 0; x < this->x; x++)
		{
			if (elements[y][x] > upper) elements[y][x] = upper;
			if (elements[y][x] < lower) elements[y][x] = lower;
		}
	}
}

void Map::multiplyData(float multiple)
{
	for (int y = 0; y < this->y; y++)
	{
		for (int x = 0; x < this->x; x++)
		{
			elements[y][x] *= multiple;
		}
	}
}

void Map::smooth(int filterSize, int passes)
{
	vector<vector<float>> newelements = elements;

	for (int i = 0; i != passes; i++)
	{
		for (int Y = 0; Y != this->y; Y++)
		{
			for (int X = 0; X != this->x; X++)
			{
				float surroundingTotal = -elements[Y][X];
				int aroundNum = -1;

				for (int y = -filterSize; y <= filterSize; y++)
				{
					for (int x = -filterSize; x <= filterSize; x++)
					{
						if (X + x > -1 && X + x < this->x && Y + y > -1 && Y + y < this->y)
						{
							surroundingTotal += elements[Y + y][X + x];
							aroundNum++;
						}
					}
				}			
				newelements[Y][X] = (elements[Y][X] + (surroundingTotal / aroundNum)) / 2;
			}
		}
		elements = newelements;
	}
}

void Map::dynamicHeightSmooth(int filterSize, int passMin, int passMax)
{
	// MAKE SMOOTH BY HEIGHT
}
