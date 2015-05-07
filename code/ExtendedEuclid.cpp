int ext_gcd(int a, int b, int &x, int &y){
	int x2;
	if( b==0 ) {
		x=1, y=0;
		return a;
	}
	int gcdn=ext_gcd(b, a%b, x, y), x2=x;
	x=y, y=x2-a/b*y;
	return gcdn;
}
int ext_gcd(int a, int b, int &x, int &y){
	int t, px=1, py=0, tx,ty;
	x=0, y=1;
	while(a%b!=0) {
		tx=x, ty=y;
		x=x*(-a/b)+px, y=y*(-a/b)+py;
		px=tx, py=ty;
		t=a, a=b, b=t%b;
	}
	return b;
}

