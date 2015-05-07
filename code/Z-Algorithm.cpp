void Z(char G[], int z[]){
	int len = strlen(G);
	z[0] = len;
	int L = 0, R = 1;
	for ( int i = 1 ; i < len ; i++ ) {
		if ( i >= R || z[i-L] >= R-i ) {
			int x = (i>=R) ? i : R;
			while ( x < len && G[x] == G[x-i] )  
				x++;
			z[i] = x - i;
			if ( x > i )  L = i , R = x;	
		}		
		else z[i] = z[i-L];
	}
}

