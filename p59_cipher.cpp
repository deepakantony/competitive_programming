#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cctype>

#define XOR(a,b) 

using namespace std;

string decipher(char *filename,unsigned char *code) {
  string res;

  ifstream in(filename);
  code[0] = 'g'; code[1] = 'o'; code[2] = 'd';
  while(in.good()) {
    for(int i = 0; in.good() && i < 3; i++) {
      char c;
      in.get(c);
      cout << c;
      unsigned char c2 = c;
      if((c^code[i]) == ' ') cout << "yes" << endl;
      unsigned char c1 = c2^code[i];
      cout << c1 << endl;
      res += (c^code[i]);
    }
  }
  in.close();
  cout << res << endl;
  exit(0);
  return res;
}

bool analyze(string str) {
  int alpha = 0;
  int spaces = 0;
  int special = 0;
  for(string::const_iterator it = str.begin(); it != str.end(); it++) {

    if(isspace(*it)) spaces++;
    else if(isalpha(*it)) alpha++;
    else special++;
  }

  int total = str.size();

  int alpha_p = alpha*100/total;
  int spaces_p = spaces*100/total;
  int special_p = special*100/total;
  if(spaces > 0) cout << spaces << endl;

  return (special_p < 5) && (spaces_p < 15 && spaces_p > 0) && 
    (alpha_p > 80 && alpha_p < 100);

  //return (alpha*100/total);//*0.6+(spaces*100/total)*0.3
	  // +(special*100/total)*0.1);
}

int main(int argc, char **argv) {
  unsigned char code[3];
  for(char a = 'a'; a <= 'z'; a++) {
    code[0] = a;
    for(char b = 'a'; b <= 'z'; b++) {
      code[1] = b;
      for(char c = 'a'; c <= 'z'; c++) {
	code[2] = c;
	string text = decipher(argv[1], code);
	if(analyze(text)) {
	  cout << code[0] << code[1] << code[2] << endl;
	  cout << text << endl;
	}
      }
    }
  }
  return 0;
}
