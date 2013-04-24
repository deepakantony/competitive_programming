import java.util.*;
import java.lang.Math;
import java.io.*;

class Main
{
	private static int[] cycleLength;
	private static int calculateCycleLength(int n) {
		if(n > 1000000 || n < 0) {
			if((n >>> 1) != ((n-1)>>>1)) return (1 + calculateCycleLength(n >>> 1));
			else return (1 + calculateCycleLength(3*n+1));
		}
		else {
			if(cycleLength[n] != 0) return cycleLength[n];
			if( n%2 == 0 ) return cycleLength[n] = 1 + calculateCycleLength(n>>1);
			else return cycleLength[n] = 1 + calculateCycleLength(3*n+1);
		}
	}

	private static int getMax(int low, int high) {
		if(low > high) return getMax(high, low);
		int maxcl = calculateCycleLength(high);
		for(int i = low; i < high; ++i)
			maxcl = Math.max(maxcl, calculateCycleLength(i));

		return maxcl;
	}
					
	public static void main(String[] args) {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		
		cycleLength = new int[1000001];
		cycleLength[0] = 0; cycleLength[1] = 1;
		String line;
		try {
			while( (line = in.readLine()) != null ) {
				String cleanLine = line.trim().replaceAll("\\s+", " ");
				String[] linesplit = cleanLine.split("\\s+");
				if(linesplit.length != 2) continue;
				int low = Integer.parseInt(linesplit[0]);
				int high = Integer.parseInt(linesplit[1]);

				System.out.println( low + " " + high + " " + getMax(low,high));
			}
		}
		catch(IOException exp) {
			//System.err.println("IO ERROR");
		}
	}
}

