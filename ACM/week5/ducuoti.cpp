#include<bits/stdc++.h>
using namespace std;
int main(){
	
	double a,x,y;
	int flag = -1,cnt = -1;
	int xxx = 0;
	cin>>a>>x>>y;

	if(y >= (a*5)){
        int i = 7;
		y = y - (a*5);

        while(y >= a*2){
            y = y - a*2;
            i = i+3;
        }

       /* printf("%lf\n\n",y); */

        
        if(y < a*2 && y > a){
            /* printf("%lf\n",x); */
            if(fabs(x) > 0 && a > fabs(x)){
                if(x < 0){
                    cnt = -10;
                    printf("%d\n",i+2);
                }
                else{
                    cnt = 10;
                    printf("%d\n",i+3);
                }
            }
            else
                printf("-1\n");
        }
        else if(y < a && y > 0){
            if(fabs(x) >= 0 && fabs(x) < a/2){
                cnt = 1;
                printf("%d\n",i+1);
            }
            else{
                printf("-1\n");
            }
        }
        else{
            printf("-1\n");
        }

        exit(0);
	}

	
	//printf("%lf\n",y);

	
	
	if(y < 0){
		printf("-1\n");
		exit(0);
	}
	for(double i = 0;i <= a*4;i+=a){
		//printf("%lf  %lf\n\n",i,i+a);
		if(y > i && y < i+a){
			flag = xxx;
			if(flag == 2 || flag == 4){
				if(fabs(x) > 0 && a > fabs(x)){
					if(x < 0){
						cnt = -10;
					}
					else{
						cnt = 10;
					}
				}
			}
			else{
				if(fabs(x) >= 0 && fabs(x) < a/2){
					cnt = 1;
				}
			}
		}
		xxx++;
	}
	
	if(flag!=-1 && cnt!=-1){
		if(cnt == 1){
			if(flag == 0){
				printf("1\n");
			}
			else if(flag == 1){
				printf("2\n");
			}
			else if(flag == 3){
				printf("5\n");
			}
		}
		if(cnt == -10){
			if(flag == 2){
				printf("3\n");
			}
			if(flag == 4){
				printf("6\n");
			}
		}
		else if(cnt == 10){
			if(flag == 2){
				printf("4\n");
			}
			if(flag == 4){
				printf("7\n");
			}
		}
	}
	else{
		printf("-1\n");
	}
	//printf("\n%d %d\n",cnt,flag);
	return 0;
}
