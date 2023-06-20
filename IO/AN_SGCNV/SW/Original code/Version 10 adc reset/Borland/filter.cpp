#include <stdio.h>
#include <math.h>

int main()
{
   float old_value, new_value, filt_value, filter , prosent;
   short cnt, i ;

   old_value = 0.0 ;
   filt_value = old_value ;
   new_value = 10.0 ;
   filter = 6 ;
   cnt = 0 ;

   for ( i = 0; i < 100; i++ ) {
      filt_value += (new_value - filt_value)/ filter ;
      cnt++ ;
      prosent = (new_value - filt_value) * 100 / new_value ;
      if (prosent < 0.05) {
      	i = 100 ;
      }
   }
	printf("Filter %f, Count = %i, filt_value = %f, prosent = %f\n", filter, cnt, filt_value, prosent ) ;
	printf("ARISTON Surveyor       %i sekunder\n", (int) (cnt * 0.6) ) ;
	printf("Skarpenord CARGOMASTER %i sekunder\n", (int) (cnt * 7.0) ) ;
}
