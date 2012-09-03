/*
  Problem: Racing Horses
  Link: http://www.codechef.com/SEP12/problems/HORSES
  Author: deebee
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

import java.util.Arrays;
import java.util.Collections;

import java.lang.Math;

class Main {
	public static void main(String []args) throws IOException {
		BufferedReader inp = 
			new BufferedReader(new InputStreamReader(System.in));

		// shoule be list of longs of numbers
		long[] listOfIntegers = new long[5000];
		int T = Integer.parseInt(inp.readLine());
		for(int test = 0; test < T; ++test) {
			int N = Integer.parseInt(inp.readLine());
			String[] tok = inp.readLine().split("\\s");
			for(int curIndex = 0; curIndex < N; ++curIndex)
				listOfIntegers[curIndex] = Long.parseLong(tok[curIndex]);

			Arrays.sort(listOfIntegers, 0, N);

			long minDiff = listOfIntegers[1]-listOfIntegers[0]; // infinity
			for(int curIndex = 2; curIndex < N; ++curIndex)
				minDiff = 
					Math.min(minDiff, 
							 listOfIntegers[curIndex] - 
							 listOfIntegers[curIndex-1]);



			System.out.println(minDiff);
		}
	}
}
