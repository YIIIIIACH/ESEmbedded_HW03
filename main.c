void reset_handler(void)
{
	int a =1;   	// claim a variable to see what happen in assembly code  <conservation 1>
	a++;		// change a variable's value to see what will happen     <conservation 2>
	a--;
	int b =2;  	// claim a variable to see what happen in assembly code  
	int c =3;  	// claim a variable to see what happen in assembly code  
	int d =4;  	// claim a variable to see what happen in assembly code  
	int result;
	result= compute(a,b,c,d);
}

int compute(int a,int b,int c,int d )
{
	return a+b*sub(d,c);
}

int sub(int d,int c)
{
	return d-c;
}

