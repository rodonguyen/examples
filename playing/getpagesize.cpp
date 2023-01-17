#include <unistd.h>
#include <stdio.h>

using namespace std;


int main()
{
  int pagesize = getpagesize();
  printf( "pagesize in bytes: %d \n", pagesize );
  // pagesize in bytes: 4096
}