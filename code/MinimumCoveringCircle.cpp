node center(node p0, node p1, node p2) {
	node a = p1-p0;
	node b = p2-p0;
	double c1 = a.len2()/2;
	double c2 = b.len2()/2;
	double d = a^b;
	double x = p0.x + (c1 * b.y - c2 * a.y) / d;
	double y = p0.y + (a.x * c2 - b.x * c1) / d;
	return node(x, y);
}

pair<node,double> mcc(node p[], int n) {
	random_shuffle(p, p+n);
	node oo;
	double r2 = 0;
	for(int i=0; i<n; i++) {
		if ((oo-p[i]).len2() <= r2) continue;
		oo = p[i];
		r2 = 0;
		for(int j=0; j<i; j++) {
			if ((oo-p[j]).len2() <= r2) continue;
			oo = (p[i]+p[j]) / 2;
			r2 = (oo-p[j]).len2();
			for(int k=0; k<j; k++) {
				if ((oo-p[k]).len2() <= r2) continue;
				oo = center(p[i], p[j], p[k]);
				r2 = (oo-p[k]).len2();
			}
		}
	}
	return make_pair(oo, r2);
}

