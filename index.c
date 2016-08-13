#include <stdio.h>
#include "helper.c"
 
char k1[] = "66FF3CE3491C5EDA"; 
char k2[] = "95EFFBE191E22DB4";
char k3[] = "9CC98A29456677A6";

int key1[4][4], key2[4][4], key3[4][4];
int zigZagIndex[4][4];

char plainText[] = "ASDF48723498";

int main(int argc, char const *argv[])
{	
	int i, j, m, n, ti, tj, ix1, ix2, ix3, ix4, zi;

	m = 4;
/**
 *
 * KEY EXPANSION
 *
 */

	 /**
	  * Derive A-z indexes for keys 
	  * a = 0, B = 1 ... z = 25
	  *	1 = 1 , 2 = 2, 0 = 0 
	  */
	 

		for( i = 0; k1[i] != '\0' ; i++ ){
			
			/**
			 * 1D 1x16 marrix to 2D 4x4 
			 */
				
				ti = i / 4;
				tj = i % 4;

				key1 [ti][tj] = toAZindex( k1[i] );
				key2 [ti][tj] = toAZindex( k2[i] );
				key3 [ti][tj] = toAZindex( k3[i] );
		}


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

