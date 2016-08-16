#include <stdio.h>
#include "helper.c"
 
char k1[] = "68FF3CE3491C5EDA"; 
char k2[] = "95EFFBE191E22DB4";
char k3[] = "9CC98A29456677A6";

char plainText[] = "ASDF48723498";

/**
 *
 *
 *	- Needed Matrices
 * 	 key[ 1  ][4][4], key[ 2  ][4][4], key[ 3  ][4][4];
 * 	 key[ 10 ][4][4], key[ 11 ][4][4], key[ 12 ][4][4], key[ 13 ][4][4];
 * 	 key[ 20 ][4][4], key[ 21 ][4][4], key[ 22 ][4][4], key[ 23 ][4][4];
 * 	 key[ 30 ][4][4], key[ 31 ][4][4], key[ 32 ][4][4], key[ 33 ][4][4];
 *
 */

// *  Last index needed is "33", so size will be 33
int key[34][4][4];

/**
 * Zigzag Indexes, will be used in transposition stage
 */

	int zigZagIndex[4][4] = 
	{ 
 		{ 0, 1,	 5,	 6  },	
	 	{ 2, 4,	 7,  12 },	
	 	{ 3, 8,	 11, 13	},	
	 	{ 9, 10, 14, 15	}	
 	};


/**
 * Foldinng Indexes will used in folding stage
 */
 	int foldingIndex[4][4] = 
 	{
 		{15, 13, 14,12},
 		{7,  10, 9, 4 },
 		{11, 6,  5, 8 },
 		{3,  1,  2, 0 }
 	};


// * text 4x4, Matrix will used in every step operation
// * It will be derived from plain text string
int text[4][4];

// * tmpText is also 4x4 matrix, will be used to get Old values.
// * It is a past pf text matrix olds old indexes,
int tmpText[4][4];



// * charStatus 4x4, Matrix will have binary values that holds is that
// 	 position should be character or digit.
//   If i th data is character charStatus [i] will be 1
int charStatus [4][4];
// * same as tmpText, tmpCharStatus have values of old
// 	 indexes of charStatus data
int tmpCharStatus [4][4];

// * currentKeys holds two adjacency derived keys for each round.
int currentKeys[2];


int main(int argc, char const *argv[])
{	
	int i, j, d, M, n, ti, tj, ix1, ix2, ix3, ix4, k, kx10;
	int zi, position, tempInt, shiftMargin, RI, RJ, RX, round;
	
	d = 4;
	RI = 1; RJ = 0;


/**
 *
 * PlainText to 2D Array;
 * Currently taking PT.length < 16  
 *
 */
	for ( i = 0; plainText[i] != '\0'; i++)
	{
		ti = i / 4;
		tj = i % 4;
		text[ ti ][ tj ] = 	plainText[i];
	}


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
				
				ti = i / 4;
				tj = i % 4;

			/*
			 * Save  main three keys in 4x4 matrix
			 */
				key[1] [ti][tj] = toAZindex( k1[i] );
				key[2] [ti][tj] = toAZindex( k2[i] );
				key[3] [ti][tj] = toAZindex( k3[i] );
		}





	/**
	 * Expand keys 
	 * Key1 is expanded into key 10 , key 11 , key 12 , k 13..
	 * by shifting each row..
	 */

		for ( i = 0; i < 4; i++)
		{
			for ( j = 0; j < 4; j++)
			{
				/**
				 *
				 * KEY 1 will be expanded to Key10, Key11, Key12, Key13 and so on for KEY 2 and 3.
				 * Shifting column indexes are ix1, ix2, ix3, ix4
				 *
				 * 	suppose i = 0 and j = 0, then ix1 = (0+0) % 4 = 0 that means, 
				 *	we have to save ij data at 0th column for key 10
				 *	 ix2 =  (0+0 + 1) %4 = 1, so for key11 [i][j] data will be used is key11 [i][ 1 ],
				 *   As we can see, index has been shifted as per algorithm
				 *
				 *
				 *
				 * 	suppose i = 0 and j = 1, then ix1 = 0+1 % 4 = 1 that means, 
				 *	here ix1 is 1, indicates that for new j th loop, first row will be shifted left
				 *
				 */


				ix1 = (j+i  )%4; 	//Shift column for index 1st key
				ix2 = (j+i+1)%4; 	//Shift column for index 2nd key
				ix3 = (j+i+2)%4; 	//Shift column for index 3rd key
				ix4 = (j+i+3)%4; 	//Shift column for index 4th key

				for( k = 1; k <=3 ; k++){

					// suppose kx10 = 1*10 = 10
					kx10 = k*10;

					// * ...then keys will be generated are..
					//		k[ 10 ], k[ 10 +1 ], k[ 10 +2 ] , k[ 10 +3 ] 
					key[ (kx10)		][i][j] = key[ k ][i][ ix1 ];
					key[ (kx10)	+ 1	][i][j] = key[ k ][i][ ix2 ];
					key[ (kx10)	+ 2	][i][j] = key[ k ][i][ ix3 ];
					key[ (kx10)	+ 3	][i][j] = key[ k ][i][ ix4 ];

				}

			}

		}


for( round = 0; round < 12; round ++ )	 
{

	/*==================================================================
	=			      Algo. Starts (1 iteration of TSFS)		  	   =
	==================================================================*/

	/**
	 *
	 * GET TWO KEYS SHOULD BE USED IN THIS ROUND
	 * ---------------------------------------------
	 * 	initial RI =1 & RJ = 0'
	 *	RX will be 1*10 +0 = 10
	 * 	cunrrentKeys should be taken as 10 & RX+1 = 11
	 * --------------
	 *	In other case if RJ == 4 && RI = 1 then 
	 *	Current key will be fine but 
	 *	Next key must be taken as 20
	 *	to do so, set RJ = 0 & RI ++;
	 *	and recalculate : (RI*10)+RJ = (2*10)+0 = 20
	 * --------------
	 * 	In case of Last round, we will need next key = 10
	 *  For that We will just ReInitialize RI to 0
	 *
	 */


		RX = (RI*10)+RJ;

		currentKeys[ 0 ] = RX;
		RJ++;

		if( RJ == 4 )
		{
				
			RJ = 0;
			RI ++;
			
			if( RI == 4 ){
				RI = 1;
			}

			RX = (RI*10)+RJ;
			currentKeys[ 1 ] = RX;

		}
		else{
			currentKeys[ 1 ] = RX+1;
		}


	/**
	 *
	 * TRANSPOSITION
	 *
	 */

	 		//  Initially copy tmpText  
	 		copy4x4( tmpText, text );

	 		if( round != 0)
	 		{
	 			copy4x4( tmpCharStatus, charStatus);
	 		}

	 		for ( i = 0; i < 4; i++)
			{
				for ( j = 0; j < 4; j++)
				{
					// Position represents which index element should be here at I J
					// It fetches from zigZagIndex matrix 
					position = 	zigZagIndex[ i ][ j ];
					ti = position / 4;
					tj = position % 4;
					
					if( round == 0 ){
						if(isChar(tmpText[i][j]) )
						{
							charStatus[ ti ][ tj ] = 1;
							text [ ti ][ tj ] = toAZindex( tmpText[i][j] );
						}
						else{
							text [ ti ][ tj ] =  tmpText[i][j] ;
						}

					}else{
						text [ ti ][ tj ] 		=   tmpText[i][j];
						charStatus[ ti ][ tj ] 	= 	tmpCharStatus[ i ][ j ];
					}

				}
			}


	/**
	 *
	 * SUBSTITUTION
	 *
	 */

			M = 26;

	 		for ( i = 0; i < 4; i++)
			{
				for ( j = 0; j < 4; j++)
				{
													
	//			>> 	E(x)			= (	( ( k1 							+ p 	  ) mod M  ) + k2						 ) mod M				
					text [ i ][ j ] = ( ( ( key[ currentKeys[0] ][i][j] + text[i][j] ) % M ) + key[ currentKeys[1] ][i][j] ) % M ; 
				}

			}

			
	/**
	 *
	 * FOLDING
	 *
	 */

	 	// copy text into tmpText& charStatus to tmpCharStatus
	 	   copy4x4( tmpText, text );
 		   copy4x4( tmpCharStatus, charStatus );
	 		
			for ( i = 0; i < 4; i++)
			{
				for ( j = 0; j < 4; j++)
				{	
					//Fetch folding position of data should be here
					position = foldingIndex[i][j];
					// get i j value of that position
					ti = position / 4;
					tj = position % 4;
					
					// save that value at current position
					text [ ti ][ tj ] = tmpText[ i ][ j ]; 		
					charStatus [ ti ][ tj ] = tmpCharStatus[ i ][ j ]; 		
				

				}
			}




	/**
	 *
	 * SHIFTING
	 *
	 */

	 		shiftMargin = 0;

			for ( i = 0; i < 4; i++)
			{
				for ( j = 0; j < 4; j++)
				{	
					text [ i ][ j ] = ( text [ i ][ j ] + (26- shiftMargin) ) %26;
					shiftMargin++;
				}
			}

	
	printf("\n\n");
	showInt4x4( text );
	printf("\n");
	showInt4x4( charStatus );
	
}


	return 0;
}

