# ***************************************************************************
# Problem: Template Python file.
# Link:
# Author: Deepak Antony - "deebee" "drunkbeast" "dAbeAst"
# Solution: 
# ***************************************************************************

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
