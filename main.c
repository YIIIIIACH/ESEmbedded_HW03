void reset_handler(void)
{
	int a =1;	// claim a variable to see what happen in assembly code  <observation 1>
	a++;		// change a variable's value to see what will happen     <observation 2>
	a--;
	int b =2;	
	int c =3;
	int d =4;
	int result;
	result= compute(a,b,c,d);	//call a function which also has another function inside it <observation 3>
}

int compute(int a,int b,int c,int d )	
{
	return a+b*sub(d,c);		// how did the result of function return <observation 5>
}

int sub(int d,int c)			// how did the function call pass their augument <observation 4>
{
	return d-c;
}

