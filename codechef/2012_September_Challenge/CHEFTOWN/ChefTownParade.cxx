/*
  Problem: ChefTown Parade
  Link: http://www.codechef.com/SEP12/problems/CHEFTOWN
  Author: deebee (deepakantony)
  Soln: Sliding window algorithm. Ascending minima algorithm.
*/

#include <cstdio>
#include <deque>
#include <functional>
#include <cctype>

using namespace std;

typedef deque<int> DI;

#define REP(i, n) for(int i = 0; i < (n); ++i)
#define FOR(i, st, nd) for(int i = (st); i < (nd); ++i)


#include <cstdlib>
#include <stdint.h>
#include <unistd.h>
class FastInput {
public:
    FastInput() {
        m_dataOffset = 0;
        m_dataSize = 0;
        m_v = 0x80000000;
    }
    uint32_t ReadNext() {
        if (m_dataOffset == m_dataSize) {
            int r = read(0, m_buffer, sizeof(m_buffer));
            if (r <= 0) return m_v;
            m_dataOffset = 0;
            m_dataSize = 0;
            int i = 0;
            if (m_buffer[0] < '0') {
                if (m_v != 0x80000000) {
                    m_data[m_dataSize++] = m_v;
                    m_v = 0x80000000;
                }
                for (; (i < r) && (m_buffer[i] < '0'); ++i);
            }
            for (; i < r;) {
                if (m_buffer[i] >= '0') {
                    m_v = m_v * 10 + m_buffer[i] - 48;
                    ++i;
                } else {
                    m_data[m_dataSize++] = m_v;
                    m_v = 0x80000000;
                    for (i = i + 1; (i < r) && (m_buffer[i] < '0'); ++i);
                }
            }
        }
        return m_data[m_dataOffset++];
    }
public:
    uint8_t m_buffer[32768];
    uint32_t m_data[16384];
    size_t m_dataOffset, m_dataSize;
    uint32_t m_v;
};


//template<class T>
//inline void insert(LI &l, LI &li, int index, int newVal, T cmp) {
//	while(l.size() > 0 && cmp(newVal, l.back()))
//		l.pop_back(), li.pop_back();
//	l.push_back(newVal), li.push_back(index);
//}


int main(int argc, char *argv[]) {
	int N, W;
	// mn is list of mins and mni is the indices; similarly mx is for max
	//FastInput fin;
	int *allNumbers;
	if(scanf("%d%d", &N, &W) != EOF) {
		int W_1 = W-1;
		//N = fin.ReadNext();
		//W = fin.ReadNext();
		allNumbers = new int[N];
		DI mn, mni, mx, mxi; 
		int ways = 0;
		REP(i, W) {
			scanf("%d", &allNumbers[i]);
			//allNumbers[i] = fin.ReadNext();
			//insert<less<int> > (mn, mni, i, allNumbers[i], less<int>() );
			while(mn.size() > 0 && allNumbers[i] < mn.back())
				mn.pop_back(), mni.pop_back();
			mn.push_back(allNumbers[i]), mni.push_back(i);
			while(mx.size() > 0 && allNumbers[i] > mx.back())
				mx.pop_back(), mxi.pop_back();
			mx.push_back(allNumbers[i]), mxi.push_back(i);
		}

		if((mx.front() - mn.front()) == W_1) ++ways;
		FOR(i, W, N) {
			scanf("%d", &allNumbers[i]);
			//allNumbers[i] = fin.ReadNext();
			//mn.erase(allNumbers[i-W]), mx.erase(allNumbers[i-W]);
			//mn.insert(allNumbers[i]), mx.insert(allNumbers[i]);
			if(mni.front() < i-W+1) mni.pop_front(), mn.pop_front();
			if(mxi.front() < i-W+1) mxi.pop_front(), mx.pop_front();
			while(mn.size() > 0 && allNumbers[i] < mn.back())
				mn.pop_back(), mni.pop_back();
			mn.push_back(allNumbers[i]), mni.push_back(i);
			while(mx.size() > 0 && allNumbers[i] > mx.back())
				mx.pop_back(), mxi.pop_back();
			mx.push_back(allNumbers[i]), mxi.push_back(i);

			if((mx.front() - mn.front()) == W_1) ++ways;
		}
		printf("%d\n", ways);
	}
	return 0;
}

