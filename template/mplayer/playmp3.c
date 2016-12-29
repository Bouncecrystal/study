#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct lrctype{
	char lyrics[100];
	int time;
}Lrctype;

Lrctype lrctype[100];

//Lrctype lrctype[100]=(Lrctype)malloc(sizeof(Lrctype));

int chartoint(char ch)
{
	return ch-'0';
}

int strtoint(char str[])
{
	int num1=chartoint(str[0]);
	int num2=chartoint(str[1]);
	int num3=chartoint(str[3]);
	int num4=chartoint(str[4]);
	int num5=chartoint(str[6]);
	int num6=chartoint(str[7]);
	return ((num1*10+num2)*60+(num3*10+num4))*1000000+(num5*100+num6*10)*1000;
}

void swap(Lrctype* a,Lrctype* b)
{
	Lrctype t=*a;
	*a=*b;
	*b=t;
}

int read_lrc(FILE* fp)
{
	int i=0,j=0,start=0,end=0;
	char t[9]={0};
	char temp[100]={0};
	
	while(1)
		{
			char a=fgetc(fp);
			if(a==EOF)
				break;
			if(a=='[')  //time
			{
				fgets(t,9,fp);
				fgetc(fp);
				lrctype[i++].time=strtoint(t);
				j++;
			}
			else  //lyrics
			{
				fseek(fp,-1,SEEK_CUR);
				memset(temp,100,sizeof(char));			
				fgets(temp,100,fp);
				for(;j>0;j--)
					strcpy(lrctype[i-j].lyrics,temp);
			}
		}
	return i;
}

void sort_lyrics(int n)
{
	int i,j;
    for(i=1;i<n;i++)
    	{
        	for(j=0;j<i;j++)
        		if(lrctype[i].time<lrctype[j].time)
               		swap(&lrctype[i],&lrctype[j]);
				else
					continue;   		
        }
}		

int main(int argc,char* argv[])
{
	int i=1,n=0;
	char str1[100]={0};
	char str2[100]={0};
	sprintf(str1,"mplayer %s.mp3 -quiet",argv[1]);
	sprintf(str2,"%s.lrc",argv[1]);
	FILE* fp=fopen(str2,"r");
	if(fp==NULL)
	{
		perror(argv[1]);
		exit(1);  
	}
	n=read_lrc(fp);
	fclose(fp);
	sort_lyrics(n);
	/*for(i=0;i<n;i++)
		printf("%d %s\n",lrctype[i].time,lrctype[i].lyrics);*/

	int mypid=fork();
	if(mypid==0) //child process
	{	
		system(str1);
	}
	else         //parent process
	{
		printf("\033[2J\033[1;1H\033[?25l"); //clear
		usleep(lrctype[0].time+100000);
		printf("%s",lrctype[0].lyrics);
		for(i=1;i<n;i++)
		{
			printf("\033[2J\033[1;1H");		//clear
			usleep(lrctype[i].time - lrctype[i-1].time);
			printf("%s",lrctype[i].lyrics);
		}
	}
	return 0;
}
