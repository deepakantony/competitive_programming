#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <cmath>

#define XOR(a,b) 

using namespace std;

char to_char(string str) {
  char x = 0;
  for(string::const_iterator it = str.begin(); it != str.end(); it++)
    if(isdigit(*it))
      x = x*10 + (*it - '0');
  return x;
}

string ascii_to_string(char *filename, char delim = ',') {
  string res;
  ifstream in(filename);
  char line[100];
  while(in.getline(line, 100, ',')) {
    res += (to_char(string(line)));
  }
  cout << endl;
  in.close();
  return res;
}

string decipher(string text, char code, int start_at) {
  string res;
  for(string::const_iterator it = text.begin() + start_at;
      it < text.end(); it+=3)
    res += *it ^ code;
  return res;
}

string decipher(string text, char *code) {
  string res;
  for(string::const_iterator it = text.begin(); it != text.end();)
    for(int i = 0; it != text.end() && i < 3; i++, it++)
      res += *(it) ^ code[i];
  return res;
}

double gaussian(double mean, double sigma_2, double x) {
  double sqrt_denom = sqrt(2*3.14*sigma_2);
  double power = -(x-mean)*(x-mean)/(2*sigma_2);
  return (1.f/sqrt_denom)*exp(power);
}
    
double analyze(string str) {
  int alpha = 0;
  int e = 0, t = 0, a = 0, o = 0, i = 0;
  int spaces = 0;
  int punct = 0;
  int special = 0;
  for(string::const_iterator it = str.begin(); it != str.end(); it++) {

    if(isspace(*it)) spaces++;
    else if(isalpha(*it)){
      alpha++; 

      switch(*it) {
      case 'e': e++; break;
      case 't': t++; break;
      case 'a': a++; break;
      case 'o': o++; break;
      case 'i': i++; break;
      }
    }
    else if(ispunct(*it)) punct++;
    else special++;
  }

  int total = str.size();

  double alpha_p = alpha*100.f/total;
  double spaces_p = spaces*100.f/total;
  double special_p = special*100.f/total;
  double punct_p = punct*100.f/total;

  double alpha_score = gaussian(0.75, 0.1, (double)alpha/(double)total)*100.0/gaussian(0.75, 0.1, 0.75);
  double spaces_score = gaussian(0.12, 0.03, (double)spaces/(double)total)*100.0/gaussian(0.12, 0.03, 0.12);
  double special_score = gaussian(0.01, 0.005, (double)special/(double)total)*100.0/gaussian(0.01, 0.005, 0.01);
  double punct_score = gaussian(0.1, 0.02, (double)punct/(double)total)*100.0/gaussian(0.1, 0.02, 0.1);

  double a_score = gaussian(0.08, 0.05, (double)a/(double)alpha)*100.0/gaussian(0.08, 0.05, 0.08);
  double t_score = gaussian(0.09, 0.05, (double)t/(double)alpha)*100.0/gaussian(0.09, 0.05, 0.09);
  double e_score = gaussian(0.13, 0.05, (double)e/(double)alpha)*100.0/gaussian(0.13, 0.05, 0.13);
  double o_score = gaussian(0.075, 0.05, (double)o/(double)alpha)*100.0/gaussian(0.075, 0.05, 0.075);
  double i_score = gaussian(0.07, 0.05, (double)i/(double)alpha)*100.0/gaussian(0.07, 0.05, 0.07);
  
  return (alpha_score + spaces_score + special_score + punct_score + a_score + t_score + e_score + o_score + i_score)/9.0;
}

long sum_of_ascii(string text) {
  int sum = 0;
  for(string::const_iterator it = text.begin(); it != text.end(); it++)
    sum += *it;
  return sum;
}

int main(int argc, char **argv) {
  string encrypted_text = ascii_to_string(argv[1]);
  double max = 0.0;
  char code[3], final_code[3];
  cout << encrypted_text.size() << endl;

  for(int start_at = 0; start_at < 3; start_at++) {
    max = 0.0;
    for(char a = 'a'; a <= 'z'; a++) {
      string text = decipher(encrypted_text, a, start_at);
      double score = analyze(text);
      if(score > max) {
	final_code[start_at] = a;
	max = score;
      }
    }
  }
  
  copy(final_code, final_code+3, ostream_iterator<char>(cout,""));
  cout << endl;
  string deciphered = decipher(encrypted_text, final_code);
  cout << deciphered.size() << endl;
  cout << deciphered << endl;
  cout << "Sum of ascii: " << sum_of_ascii(deciphered) << endl;
  return 0;
}
