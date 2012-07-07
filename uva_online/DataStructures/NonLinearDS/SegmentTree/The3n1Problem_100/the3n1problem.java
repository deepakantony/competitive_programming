
import java.util.*;

class the3n1problem
{
	public static void main(String[] args) {
		System.out.println("");
	}
}

class SegmentTree {
	class SNode {
		SNode left, right;
		int max, low, high, mid;
	}
	private SNode root;
	private ArrayList<int> maxCycle;

	public SegmentTree(int start = 1, int end = 1000000) {
		maxCycle = new ArrayList<Integer>(Collections.nCopies(1000000, -1));
		buildSegmentTree(root, start, end);
		
	}

	private void buildSegmentTree(SNode cur, int low, int high) {
		if(low > high) return;
		cur.low = low; cur.high = high;
		cur.mid = (low+high)/2;
		if(low == high) {
			cur.left = cur.right = null;
			cur.max = getMaxCycleLen(low);
		}
		else {
			cur.left = new SNode();
			cur.right = new SNode();
			buildSegmentTree(cur.left, low, cur.mid);
			buildSegmentTree(cur.right, cur.mid+1, high);
			cur.max = max(cur.left.max, cur.right.max);
		}
	}

	private int getMaxCycleLen(int n) {
		if(maxCycle[n] == -1)
			return calculateCycleLen(n);
		else
			return maxCycle[n];
	}

	public int query(int i, int j) {
		return query(root, i, j);
	}

	private int query(SNode cur, int low, int high) {
		if(cur == null) return 0;
		if(cur.low >= low && cur.high <= high) return cur.max;
		if(low > cur.mid)
			return query(cur.right, low, high);
		else if(high <= cur.mid)
			return query(cur.left, low, high);
		else 
			return max(query(cur.left, low, high), query(cur.right, low, high));
	}
}