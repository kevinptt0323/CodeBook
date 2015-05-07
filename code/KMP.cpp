int KMP(char pat[5005], char str[5005]) {
	if( strlen(pat)>strlen(str) ) return -1;
	int failure[5005];
	int len=strlen(pat);
	for(int i=1, j=failure[0]=-1; i<len; ++i) {
		while( j>=0 && pat[j+1]^pat[i] ) j=failure[j];
		if( pat[j+1]==pat[i] ) ++j;
		failure[i]=j;
	}
	for(int i=0, j=-1; str[i]; ++i) {
		while( j>=0 && str[i]^pat[j+1] ) j=failure[j];
		if( str[i]==pat[j+1] ) ++j;
		if( j==len-1 ) {
			return i-len+1; // rec this!!
			j=failure[j];
		}
	}
	return -1;
}

