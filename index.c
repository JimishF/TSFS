#include <stdio.h>
#include "helper.c"
 
char k1[] = "66FF3CE3491C5EDA"; 
char k2[] = "95EFFBE191E22DB4";
char k3[] = "9CC98A29456677A6";

int zigZagIndex[4][4];

int main(int argc, char const *argv[])
{	
	int i, j, m, n, ti, tj, zi;

	/**
	 *
	 * Making zigzag index array
	 *	0	1	5	6	
	 *	2	4	7	12	
	 *	3	8	11	13	
	 *	9	10	14	15	
	 *
	 */

		for (i = n = 0; i < m * 2; i++)
		{
			for (j = (i < m) ? 0 : i-m+1; j <= i && j < m; j++)
			{	
				zi = (i&1)? j*(m-1)+i : (i-j)*m+j;
				ti = zi / 4;
				tj = zi % 4;
				zigZagIndex[ ti ][ tj ] = n++;
			}

		}



	// for ( i = 0; i < 4; i++)
	// {
	// 	for ( j = 0; j < 4; j++)
	// 	{
	// 		printf("%d\t", zigZagIndex[i][j]);
	// 	}
	// 	printf("\n");
	// }

	return 0;
}

