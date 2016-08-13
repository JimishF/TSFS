int toAZindex(char c)
{

 	if(c >= 'a' && c <= 'z')
    {
     	c = c - 97;
    }
    else if(c >= 'A' && c <= 'Z')
    {	
		c = c - 65;   
    }
    else if(c >= '1' && c <='9' ){
		c = c-48;   
    }

    return c;
}


void multiply(int a[4][4],int b[4][4],int mult[4][4])
{
    int i,j,k;
    
    for(i=0; i<4;i++)
        for(j=0; j<4; j++)
            mult[i][j] = 0;
        

    for(i=0; i<4;i++)
        for(j=0; j<4; j++)
            for(k=0; k<4; k++)  
                mult[i][j]+=a[i][k]*b[k][j];
    
}


void show4x4(int tmp[4][4]){
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                printf("%d\t", tmp[i][j]);
            }
            printf("\n");
        }

}