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
