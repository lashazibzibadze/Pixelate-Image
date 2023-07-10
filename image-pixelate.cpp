/* 
Author: Lasha Zibzibadze
Course: CSCI-135
Instructor: Genady Maryash
*/

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>
using namespace std;

const int MAX_H = 512;
const int MAX_W = 512;
int out_file[MAX_H][MAX_W];
//read image function
void readImage(int image[MAX_H][MAX_W], int &height, int &width) {
	char c;
	int x;
	ifstream instr;
	instr.open("inImage.pgm");

	instr >> c;
	assert(c == 'P');
	instr >> c;
	assert(c == '2');

	while ((instr>>ws).peek() == '#') {
		instr.ignore(4096, '\n');
	}

	instr >> width;
	instr >> height;

	assert(width <= MAX_W);
	assert(height <= MAX_H);
	int max;
	instr >> max;
	assert(max == 255);

	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			instr >> image[row][col];
	instr.close();
	return;

}
//write image function
void writeImage(int image[MAX_H][MAX_W], int height, int width) {
	ofstream ostr;
	ostr.open("outImage.pgm");
	if (ostr.fail()) {
		cout << "Unable to write file\n";
		exit(1);
	};

	ostr << "P2" << endl;
	ostr << width << ' ';
	ostr << height << endl;
	ostr << 255 << endl;

	for (int row = 0; row < height; row++) {
		for (int col = 0; col < width; col++) {
			assert(image[row][col] < 256);
			assert(image[row][col] >= 0);
			ostr << image[row][col] << ' '; 
			ostr << endl;
		}
	}
	ostr.close();
	return;

}
//pixelate image function
int Pixelateimage(int image[MAX_H][MAX_W], int h, int w){

    int count_pixels_changed = 0;  //temporary

    //main logic
    for(int row = 0; row < h; row ++) {
        for(int col = 0; col < w; col ++){
            //out_file[row][col] = (image[row][col]+image[row+1][col]+image[row][col+1]+image[row+1][col+1]) / 4;
            if(row % 2 == 0){
                count_pixels_changed++;
            
                if(col % 2 == 0){
                    out_file[row][col]= ((image[row][col]+image[row+1][col]+image[row][col+1]+image[row+1][col+1]) / 4);
                }
                else{
                    out_file[row][col]= ((image[row][col]+image[row+1][col]+image[row][col-1]+image[row+1][col-1]) / 4);
                }
            }

            else{
               count_pixels_changed++;
               if(col % 2 == 0){
                    out_file[row][col]= ((image[row][col]+image[row-1][col]+image[row-1][col+1]+image[row][col+1]) / 4);
               } 
               else{
                    out_file[row][col]= ((image[row][col]+image[row-1][col]+image[row][col-1]+image[row-1][col-1]) / 4);
               }
            }

        }
    }
    

    return out_file[MAX_H][MAX_W];
}
// main execution fucntion
int main() {

    int img[MAX_H][MAX_W];
    int h, w;

    readImage(img, h, w);
    Pixelateimage(img, h, w);

    writeImage(out_file, h, w);
    return 0;

}
