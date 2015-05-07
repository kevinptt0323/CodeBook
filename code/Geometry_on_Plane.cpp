struct node {
	double x,y;
	node() {}
	node(double _x, double _y) : x(_x),y(_y) {}
	node operator+(const node& rhs)const
		{ return node(x+rhs.x,y+rhs.y); }
	node operator-(const node& rhs)const
		{ return node(x-rhs.x,y-rhs.y); }
	node operator*(const double& rhs)const
		{ return node(x*rhs,y*rhs); }
	node operator/(const double& rhs)const
		{ return node(x/rhs,y/rhs); }
	double operator*(const node& rhs)const
		{ return x*rhs.x+y*rhs.y; }
	double len2()const{ return x*x+y*y; }
	double len()const{ return sqrt(x*x+y*y); }
	node unit()const{ return *this/len(); }
	double operator^(const node& rhs)const{ return x*rhs.y-y*rhs.x; }
	node T()const{ return node(-y,x); }
	node rot(double rad)const{ //逆時針旋轉 弧度
		return node(cos(rad)*x-sin(rad)*y, sin(rad)*x+cos(rad)*y);
	}
};
node __mirror(node normal, double constant, node point){ //2D3D
	double scale=(normal*point+constant)/(normal*normal);
	return point-normal*(2*scale);
}
node mirror(node p1, node p2, node p3){ //2D3D
	return __mirror((p2-p1).T(),(p2-p1).T()*p1*(-1),p3);
}
double ori(const node& p1,const node& p2, const node& p3){ //平行四邊形面積(帶正負)
	return (p2-p1)^(p3-p1);
}
bool intersect(const node& p1, const node& p2, const node& p3, const node& p4){
	return (ori(p1,p2,p3)*ori(p1,p2,p4)<0 && ori(p3,p4,p1)*ori(p3,p4,p2)<0);
}
pair<node,node> two_circle_intersect(node p1, double r1, node p2, double r2){
	double degree=acos(((p2-p1).len2()+r1*r1-r2*r2)/(2*r1*(p2-p1).len()));
	return make_pair(p1+(p2-p1).unit().rot(degree)*r1, p1+(p2-p1).unit().rot(-degree)*r1);
}
node intersectionPoint(node p1, node p2, node p3, node p4){
	double a123 = (p2-p1)^(p3-p1);
	double a124 = (p2-p1)^(p4-p1);
	return (p4*a123-p3*a124)/(a123-a124);
}

