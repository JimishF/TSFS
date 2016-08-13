#include <stdio.h>
#include "helper.c"
 
char k1[] = "66FF3CE3491C5EDA"; 
char k2[] = "95EFFBE191E22DB4";
char k3[] = "9CC98A29456677A6";

int key1[4][4], key2[4][4], key3[4][4];

int key10[4][4], key11[4][4], key12[4][4], key13[4][4];
int key20[4][4], key21[4][4], key22[4][4], key23[4][4];
int key30[4][4], key31[4][4], key32[4][4], key33[4][4];
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
	 * Expand keys 
	 * Key1 is expanded into key 10 , key 11 , key 12 , k 13..
	 * by shifthing each row..
	 */

		for ( i = 0; i < 4; i++)
		{
			for ( j = 0; j < 4; j++)
			{
				ix1 = (j+i)%4;
				ix2 = (j+i+1)%4;
				ix3 = (j+i+2)%4;
				ix4 = (j+i+3)%4;

				key10[i][j] = key1[i][ ix1 ];
				key11[i][j] = key1[i][ ix2 ];
				key12[i][j] = key1[i][ ix3 ];
				key13[i][j] = key1[i][ ix4 ];

				key20[i][j] = key2[i][ ix1 ];
				key21[i][j] = key2[i][ ix2 ];
				key22[i][j] = key2[i][ ix3 ];
				key23[i][j] = key2[i][ ix4 ];

				key30[i][j] = key3[i][ ix1 ];
				key31[i][j] = key3[i][ ix2 ];
				key32[i][j] = key3[i][ ix3 ];
				key33[i][j] = key3[i][ ix4 ];
			}

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

