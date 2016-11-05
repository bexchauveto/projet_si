


/*
 * test
 ****/
int fibo(int *pt, int x)
{
	int res;
	if(x < 1)
		res = 0;
	else if(x == 1)
		res = 1;
	else
	{
		res = fibo(pt,x-1);
		res = res + *(pt+x-2);
	}
	*(pt+x) = res;
	return res;
}


int main()
{
	int t[10];
	print(fibo(&t,10));
	
	return 0;
}




