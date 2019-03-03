#include<stdio.h>
#include<string.h>

char city_names[50][50]; //stores the city names
int inum;
int arr[10][10], done[10], n, cost=0;
int result[10], index=0;

void input()
{
	int i, k;
    printf("Enter the number of cities: ");   
	scanf("%d", &n);
	for(i=0;i<n;i++)
	{
		printf("Enter the %dth city: ", i+1);
		scanf(" %[^\n]", city_names[i]); //takes in city names
	}
	printf("\nEnter the cost matrix\n");
	for(i=0;i<n;i++)
	{
		printf("\nEnter elements of row %d as per the cost matrix\n",i+1);
		for(k=0;k<n;k++)
		{
			if(i==k) //checks for same city
				arr[i][k]=0; //assigning same city as 0
			else
			{
				printf("Enter the distance between %s and %s: ", city_names[i], city_names[k]);
				scanf("%d", &arr[i][k]); //taking distance between cities
			}
		}
		done[i]=0;
	}
	printf("\nThe cost matrix is:\n");
    	for(i=0;i<n;i++) //printing the cost matrix
	{
        	for(k=0;k<n;k++)
        	{
        		printf("\t%d", arr[i][k]);
		}
		printf("\n");
	}
}

void calc(int city)
{
	int nex_city;
	done[city]=1; //marking the city which has been already visited
	printf("%s--->", city_names[city]); //printing
	result[index]=city; //storeing the final path in another array
	index++;
	nex_city=least_city(city); //searching for the nearest city
	if(nex_city==999999) //chekcing if the cycle is complete
	{
		nex_city=inum-1;
		printf("%s", city_names[nex_city]);
		result[index]=nex_city;
		index++;
		cost+=arr[city][nex_city];
		return;
	}
	calc(nex_city); //going to the next node
}

int least_city(int i)
{
	int temp=999999, k, nc=999999;
	for(k=0;k<n;k++)
	{
		if((arr[i][k]!=0)&&(done[k]==0)) //checking if its a different node and weather its visited or not
		{
			if(arr[i][k]<temp) //checking if its the nearest city or not
			{
				temp=arr[i][k]; //storing the running nearest city
				nc=k;	
			}
		}
	}
	if(temp!=999999) //if next city is found
	{
		cost+=temp; //incriment the distance travelled
	}
	return nc; //return next city
}

void storage()
{
	FILE *fp;
	int i, k, num=123;
	char temp[10];
	fp=fopen("data.txt", "a");
	fputs("The city list is\n", fp);
	for(i=0;i<n;i++)
	{
		fputs(city_names[i] , fp);
		fputs("\n" , fp);		
	}
	fputs("The cost matrix is\n", fp);
	for(i=0;i<n;i++)    
	{
        for(k=0;k<n;k++)
        {
			itoa(arr[i][k], temp, 10);
			fputs(temp, fp);
			fputc('\t', fp);
		}
		fputc('\n', fp);
	}
	fputs("The starting city is ", fp);
	fputs(city_names[inum-1], fp);
	fputs("\nThe final path is\n", fp);
	for(i=0;i<n;i++)
	{
		fputs(city_names[result[i]], fp);
		fputs("--->", fp);
	}
	fputs(city_names[inum-1], fp);
	fputs("\nMinimum distance required to travel is ", fp);
	itoa(cost, temp, 10);
	fputs(temp, fp);
	fputs("\n=====================================\n", fp);
	fclose(fp);
}

void main() 
{    
	int i;
	input();
	printf("\nEnter the number of the starting city: ");
	scanf("%d", &inum);
	printf("The path is\n");
	calc(inum-1);
	storage();
	printf("\nMinimum distance required to travel is %d\n ",cost);
    getch();
}
