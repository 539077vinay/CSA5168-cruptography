#include<stdio.h>
#include<string.h>
int main(){
	char msg[10];
    int i,j;
    printf("enter the message:");
    scanf("%s",&msg);
	char al[]="abcdefghijklmnopqrstuvwxyz";
	char su[]="uvwxyzabcdefghijklmnopqrst";
	for(i=0;i<strlen(msg);i++)
	{
		for(j=0;j<strlen(al);j++)
		{
			if(msg[i]==al[j])
			{
				printf("%c ",su[j]);
			}
		}
	}
	return 0;
}
