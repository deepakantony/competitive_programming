/*
  Problem: Kisses & Hugs
  Link: http://www.codechef.com/SEP12/problems/CKISSHUG
  Solution: derived a formula based on the series. 
  T[n] = T[n-1] + 2^(n/2) if n is even
  T[n] = T[n-1] + 2^((n-1)/2) if n is odd

  This solves to T[n] = 2*SumGP(2,n/2) + 2^(n/2) if n is even
  T[n] = 2*SumGP(2,(n/2)+1) if n is odd
  Author: deebee
*/

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.IOException;

class Main {
	private static int MOD = 1000000007;
	private static long modularPow(long base, long exp) {
		long res = 1;
		while(exp > 0) {
			if(exp%2 == 1) 
				res = (res * base) % MOD;
			exp = exp >> 1;
			base = (base * base) % MOD;
		}
		return res;
	}
	private static long gp(long n) {
		//if(n==0) return 0;
		long res = modularPow(2, n);
		return (res-1) < 0 ? MOD-1 : res-1;
	}
	public static void main(String[] args) throws IOException{
		BufferedReader inp =
			new BufferedReader(new InputStreamReader(System.in));
		int T = Integer.parseInt(inp.readLine());

		while(T-- > 0) {
			long n = Long.parseLong(inp.readLine());
			long res = 0;

			if(n%2 == 0) {// even
				long n2 = n/2;
				res = (2*gp(n2))%MOD;
				res = (modularPow(2, n2)+res)%MOD;
			} 
			else {
				long n2 = (n-1)/2;
				res = (2*gp(n2+1))%MOD;
			}
			System.out.println(res);
		}
	}
}
