# ******************************************************************************
# Problem: Template Python file.
# Link:
# Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
# Solution: 
# ******************************************************************************

# Uncomment this line if the judge supports psyco
# NOTE: psyco is not supported in 2.7 and 3.x+
# import psyco
# psyco.full()

import time
import sys

def timeElapsed(fn):
    """ A time elapsed decorator """
    def wrapper(*args, **kwargs):
        start = time.time()
        res = fn(*args, **kwargs)
        sys.stderr.write("Time Elapsed: %f seconds\n"%(time.time()-start))
        return res
    return wrapper

@timeElapsed
def main():
    """ Main controller """
    # solve a problem here
    pass

if __name__ == "__main__":
    main()
