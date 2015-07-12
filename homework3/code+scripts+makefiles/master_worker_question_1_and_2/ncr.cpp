#include <cilk/cilk.h>
using namespace std;
int nCr( int n, int r )
{
        if ( r > n ) return 0;
        if ( ( r == 0 ) || ( r == n ) ) return 1;
        int x, y;
        x = cilk_spawn nCr( n - 1, r - 1 );
        y = nCr( n - 1, r );
        cilk_sync;
        return ( x + y );
}
extern "C++" int nCr_CPP( int n, int r )
{
        return nCr(n, r );
}
