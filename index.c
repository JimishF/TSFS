#include <stdio.h>
#include "helper.c"
 
char k1[] = "68FF3CE3491C5EDA"; 
char k2[] = "95EFFBE191E22DB4";
char k3[] = "9CC98A29456677A6";

/**
 *
 *
 *	- Needed Matrices
 * 	int key[1][4][4], key[2][4][4], key[3][4][4];
 * 	int key[10][4][4], key[11][4][4], key[12][4][4], key[13][4][4];
 * 	int key[20][4][4], key[21][4][4], key[22][4][4], key[23][4][4];
 * 	int key[30][4][4], key[31][4][4], key[32][4][4], key[33][4][4];
 *
 */

// *  Last index needed is "33", so size will be 33
int key[34][4][4];

int zigZagIndex[4][4];

char plainText[] = "ASDF48723498";

int main(int argc, char const *argv[])
{	
	int i, j, m, n, ti, tj, ix1, ix2, ix3, ix4, k, kx10, zi;

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

				key[1] [ti][tj] = toAZindex( k1[i] );
				key[2] [ti][tj] = toAZindex( k2[i] );
				key[3] [ti][tj] = toAZindex( k3[i] );
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
				// Shifting index
				ix1 = (j+i)%4; 		//Shift 1
				ix2 = (j+i+1)%4; 	//Shift 2
				ix3 = (j+i+2)%4; 	//Shift 3
				ix4 = (j+i+3)%4; 	//Shift 4

				for( k = 1; k <=3 ; k++){
					kx10 = k*10;

					key[ (kx10)		][i][j] = key[ k ][i][ ix1 ];
					key[ (kx10)	+ 1	][i][j] = key[ k ][i][ ix2 ];
					key[ (kx10)	+ 2	][i][j] = key[ k ][i][ ix3 ];
					key[ (kx10)	+ 3	][i][j] = key[ k ][i][ ix4 ];

				}

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

	show4x4( key[21] );

	return 0;
}

