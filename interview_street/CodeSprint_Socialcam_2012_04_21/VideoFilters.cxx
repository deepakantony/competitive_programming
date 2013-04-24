#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

#define REP(i, st, n) for(int (i) = (st); (i) < (n); ++(i))

struct RGB {
	unsigned char red, green, blue;
};

class Image {
public:
	Image(char *filename) {
		ifstream ifs(filename);
		if(ifs.good()) {
			ifs.read((char*)fileHeader, 14);
			ifs.read((char*)imageHeader, 40);
			width = *(int*)&imageHeader[4]; 
			height = *(int*)&imageHeader[8];
			//printf("Width: %d Height: %d\n", width, height);
			REP(row, 0, height)
				REP(col, 0, width) {
				ifs.read((char*)&pixels[row][col].red, 1);
				ifs.read((char*)&pixels[row][col].green, 1);
				ifs.read((char*)&pixels[row][col].blue, 1);
			}
		}

		ifs.close();
	}

	void writeToFile(char *filename) {
		ofstream ofs(filename);
		if(ofs.good()) {
			ofs.write((char*)fileHeader, 14);
			ofs.write((char*)imageHeader,40);
			REP(row, 0, height)
				REP(col, 0, width) {
				ofs.write((char*)&pixels[row][col].red, 1);
				ofs.write((char*)&pixels[row][col].green, 1);
				ofs.write((char*)&pixels[row][col].blue, 1);
			}
		}
		ofs.close();
	}

	void emboss() {
		RGB newPixels[500][500];

		REP(row, 1, height-1)
			REP(col, 1, width-1) {
			int temp;
			temp = -4*(int)pixels[row-1][col-1].red -
				2*(int)pixels[row-1][col].red -
				2*(int)pixels[row][col-1].red +
				(int)pixels[row][col].red +
				2*(int)pixels[row][col+1].red +
				2*(int)pixels[row+1][col].red +
				4*(int)pixels[row+1][col+1].red;
			if(temp<0) temp = 0;
			else if(temp>255) temp = 255;
			newPixels[row][col].red = (unsigned char) temp;

			temp = -4*(int)pixels[row-1][col-1].green -
				2*(int)pixels[row-1][col].green -
				2*(int)pixels[row][col-1].green +
				(int)pixels[row][col].green +
				2*(int)pixels[row][col+1].green +
				2*(int)pixels[row+1][col].green +
				4*(int)pixels[row+1][col+1].green;
			if(temp<0) temp = 0;
			else if(temp>255) temp = 255;
			newPixels[row][col].green = (unsigned char) temp;

			temp = -4*(int)pixels[row-1][col-1].blue -
				2*(int)pixels[row-1][col].blue -
				2*(int)pixels[row][col-1].blue +
				(int)pixels[row][col].blue +
				2*(int)pixels[row][col+1].blue +
				2*(int)pixels[row+1][col].blue +
				4*(int)pixels[row+1][col+1].blue;
			if(temp<0) temp = 0;
			else if(temp>255) temp = 255;
			newPixels[row][col].blue = (unsigned char) temp;

		}
		REP(row, 1, height-1)
			REP(col, 1, width-1) {
			pixels[row][col].red = newPixels[row][col].red;
			pixels[row][col].green = newPixels[row][col].green;
			pixels[row][col].blue = newPixels[row][col].blue;
		}

		RGB black; black.red = black.green = black.blue = 0;
		REP(row, 0, height) 
			pixels[0][row] = pixels[height-1][row] = pixels[row][0] = pixels[row][width-1] = black;
			
	}

private:
	RGB pixels[500][500];
	unsigned char fileHeader[14];
	unsigned char imageHeader[40];
	int width, height;
};

int main(int argc, char *argv[])
{
	char inpFilename[500], outFilename[500];
	scanf(" %s", inpFilename);
	scanf(" %s", outFilename);

	Image img(inpFilename);
	img.emboss();
	img.writeToFile(outFilename);

	return 0;
}
