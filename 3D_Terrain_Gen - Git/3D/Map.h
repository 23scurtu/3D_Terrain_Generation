#ifndef MAP_H
#define MAP_H

#include <vector>

using  namespace std;

class Map
{
        int totalsize, x, y; 
        vector<vector<float> > elements;

    public:

        Map(int x, int y);
		Map(vector<vector<float> > input, int x, int y);

        void display(); //Output data to console
        void clearElements();
        bool isedge(int x, int y);
        int getX();
        int getY();
		int getTotalsize();
		float getElement(int x, int y);
        vector<vector<float> > getElements();
        void setElement(int x, int y, int val);
        void loadElements(vector<vector<float> > input);

		//variouse overloaded functions to generate the heightmap
		//based on various parameters.
		void generate(int size, int roughness, int min, int max);
		void generate(int size, int roughness);
		void generate(int size, float roughness);
		void generate(int size, float mag, float roughness);

		void square(int x, int y, int size, int offset);
		void diamond(int x, int y, int size, int offset);
		bool isPastEdge(int x, int y);

		//Caps the heightmap data by setting values greater than
		//upper equal to upper and vice versa
		void capData(int lower, int upper);
		void multiplyData(float multiple);

		//Smooths terrain using a mean/box filter
		void smooth(int filterSize, int passes);
		void dynamicHeightSmooth(int filterSize, int passMin, int passMax);



};

#endif // MAP_H
