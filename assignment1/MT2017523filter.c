#include <stdio.h>
int main(){
	//using cut-off freq as 20HZ and sampling frequency as 120HZ, following coeffiecients were obtained.
	char x[6000];
	float b0 = .1550;
	float b1 = .3101;
	float b2 = .1550;
	float a1 = .6202;
	float a2 = -.2404;
	int n = 0;
	int x1 = 0;
	int x2 = 0;
	float y = 0;
	float y1 = 0;
	float y2 = 0;
	FILE *fr = fopen("data.csv","r");
	FILE *fw = fopen("out.csv","w+");
	while(!feof(fr)){
		fscanf(fr,"%s",&x);
		//second order bilinear butterworth filter is used
		y = b0*atoi(x) + b1*x1 + b2*x2 + a1*y1 + a2*y2;
		if(n == 0){
			x1 = atoi(x);
			x2 = 0;
			y1 = y;
			y2 = 0;
			n = n + 1;
		}else{
			x2 = x1;
			x1 = atoi(x);
			y2 = y1;
			y1 = y;
		}
		fprintf(fw,"%f\n",y);
	}
	fclose(fr);
	fclose(fw);
}
