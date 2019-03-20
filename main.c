int global_var =127;

void reset_handler(void)
{
	int a =1;	// claim a variable to see what happen in assembly code  
	a++;		// change a variable's value to see what will happen    
	a--;
	int b =2;	
	int c =3;
	int d =4;
	int result;
	result= compute(a,b,c,d);	//call a function which also has another function inside it 
}

int compute(int a,int b,int c,int d )	
{
	return a+b*sub(d,c);		// how did the result of function return 
}

int sub(int d,int c)			// how did the function call pass their augument 
{
	return d-c+global_var;
}

