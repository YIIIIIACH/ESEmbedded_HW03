void reset_handler(void)
{
	int a =1;
	a++;
	a--;
	int b =2;
	int c =3;
	int d =4;
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

