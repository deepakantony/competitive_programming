
import java.util.*;
import java.lang.Math;
import java.io.*;

class the3n1problem
{
	public static void main(String[] args) {
		BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		
		SegmentTree st = new SegmentTree(1, 1000000);
		String line;
		String[] linesplit;
		try {
			while( (line = in.readLine()) != null ) {
				linesplit = line.split(" ");
				if(linesplit.length != 2) break;
				long low = Integer.parseInt(linesplit[0]);
				long high = Integer.parseInt(linesplit[1]);
				long max;
				if(low < high) max = st.query(low,high);
				else max = st.query(high, low);
				System.out.println( low+" "+high+" "+max);
			}
		}
		catch(IOException exp) {
			//System.err.println("IO ERROR");
		}
	}
}

class SegmentTree {
	class SNode {
		SNode() {}
		SNode left, right;
		long max, low, high, mid;
	}
	private SNode root;
	private long[] maxCycle;

	public SegmentTree(long start, long end) {
		maxCycle = new long[1000001];
		root = new SNode();
		buildSegmentTree(root, start, end);
	}

	private void buildSegmentTree(SNode cur, long low, long high) {
		if(low > high) return;
		cur.low = low; cur.high = high;
		cur.mid = (low+high)/2;
		if(low == high) {
			cur.left = cur.right = null;
			cur.max = getMaxCycleLen(low);
			//System.err.println(cur.max);
		}
		else {
			cur.left = new SNode();
			cur.right = new SNode();
			buildSegmentTree(cur.left, low, cur.mid);
			buildSegmentTree(cur.right, cur.mid+1, high);
			cur.max = Math.max(cur.left.max, cur.right.max);
			//System.err.println(cur.max);
		}
	}

	private long getMaxCycleLen(long n) {
		if(maxCycle[(int)n] == 0)
			return calculateCycleLen(n);
		else
			return maxCycle[(int)n];
	}

	private long calculateCycleLen(long n) {
		if(n < 0) return 0;
		if(n > 1000000) {
			if(n%2 == 0) return calculateCycleLen(n>>1);
			else return calculateCycleLen(3*n+1);
		}
		else {
			if(maxCycle[(int)n] != 0) return maxCycle[(int)n];
			if(n == 1) return maxCycle[(int)n] = 1;
			if(n%2 == 0) return maxCycle[(int)n] = 1+calculateCycleLen(n>>1);
			return maxCycle[(int)n] = 1+calculateCycleLen(3*n+1);
		}
	}

	public long query(long i, long j) {
		return query(root, i, j);
	}

	private long query(SNode cur, long low, long high) {
		if(cur == null) return 0;
		if(cur.low >= low && cur.high <= high) return cur.max;
		if(low > cur.mid)
			return query(cur.right, low, high);
		else if(high <= cur.mid)
			return query(cur.left, low, high);
		else 
			return Math.max(query(cur.left, low, high), query(cur.right, low, high));
	}
}