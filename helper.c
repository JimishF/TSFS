int toAZindex(char c)
{

    if(c >= 'A' && c <= 'Z')
    {   
        c = c - 65;   
    }
    else if(c >= 'a' && c <= 'z')
    {
        c = c - 97;
    }else if(c > 47 && c < 58 ){
        c = c - 48;   
    }

    return c;
}
int toAZChar(int c)
{
    return (c + 65);
}

int isChar( char c ){
 
   printf("%c \t", c);
     
        if( (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') )
        {   
          return 1;   
        }
       
    return 0;
}


/* Matrix copy fnction*/
/**
 *
 * Since we've all important data declared as GLOBAL,
 * we are not going to return anything from these functions
 * 
 */

void copy4x4( int a[4][4], int b[4][4]){
    int i,j;
    for(i=0; i<4;i++){
    	for(j=0; j<4; j++){
    	    a[i][j] = b[i][j];
    	}
    }
}


void showInt4x4(int tmp[4][4])
{
	int i,j;
	printf("\n");
	for(i=0; i<4; i++)
	{
	    for(j=0; j<4; j++)
		printf("%4d",tmp[i][j]);
	    printf("\n");
	}
	// getch();
}

void showChar4x4(int tmp[4][4],int charStatus[4][4])
{
	int i,j;
	for(i=0; i<4; i++)
	{
	    for(j=0; j<4; j++)
	    {
		if(charStatus[i][j])
		    printf("%c \t",toAZChar(tmp[i][j]));
		else
		    printf("%d \t",tmp[i][j]);
	    }
	printf("\n");
	}
}

void displayKeys(int key[34][4][4])
{
	int i,k;
	for (i=1; i<=3; ++i)
	{
	    k=i*10;
	    printf("\n       Key %d \n   -------------",i);
	    showInt4x4(key[i]);
	    printf("\nExpanded Keys of %d\n------------------",i);
	    showInt4x4(key[k]);
	    showInt4x4(key[k+1]);
	    showInt4x4(key[k+2]);
	    showInt4x4(key[k+3]);
	}
}

void showChar4x4InSequence(int tmp[4][4], int charStatus[4][4] ){
	int i,j;
	printf("\n= = = = = = = = = DECRYPTED MESSAGE = = = = = = = = = = = = \n"   );

	for ( i = 0; i < 4; i++)
	{
	    for ( j = 0; j < 4; j++)
	    {
		if( tmp[i][j] == 0 &&  charStatus[i][j] != 1  ){
		    continue;
		}
		if( charStatus[i][j] ){
		    printf("%c", toAZChar( tmp[i][j]) );
		}else{
		    printf("%d",  tmp[i][j] );
		}

	    }
	}
	printf("\n \n");

}
