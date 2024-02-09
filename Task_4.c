#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LOAD 1000
#define MAX_STATION 10

struct pqueue
{
    char name[20];
    int dispatch_no;
    char type;
    int gross_wt;
    int amount;
    int source;
    int destination;
    struct pqueue* next;
}*head=NULL,*front=NULL,*rear=NULL;

void enqueue(char name[],char type,int wt,int source,int destination);
void display_list();
void Create_dispatch();
void dequeue();

int main()
{
    head=(struct pqueue*)malloc(sizeof(struct pqueue));
    if(head==NULL)
    {
        printf("Memory Error");
        exit(0);
    }
    head->name[20]='\0';
    head->dispatch_no=0;
    head->gross_wt=0;
    head->amount=0;
    head->source=0; //to store total number of shippings done
    head->destination=0;
    head->next=NULL;
    char name[20];
    char type,temp;
    int wt,end,i,op,key;
    printf("\n\t\t\t***FASTAG CARGO SHIPPING***\t\t\t");
    printf("\nATTENTION! Maximum number of stations: %d",MAX_STATION);
    for(i=1;i<=MAX_STATION;i++)
    {
        key=1;
        while(key!=0)
        {
            printf ("\n\n>>>STATION-%d<<<   >>>STATION-%d<<<\n",i,i);
            printf ("\nTotal number of goods=%d | Occupied capacity=%d kg | Available capacity=%d kg | Total Amount=%d\n",head->dispatch_no,head->gross_wt,MAX_LOAD - head->gross_wt,head->amount);
	        printf ("..............................................................................................");
	        printf ("\nCharge for cargo shipping between any two consecutive stations: FRAGILE-12/kg  TOUGH-10/kg\n");
	        printf ("\nPress '1' to enqueue\t'2' to display\t'0' to exit\n");
	        scanf ("%d",&op);
	        if (op == 1)
	        {
	            if (i < MAX_STATION)
		        {
		            printf ("\nEnter your name:");
		            scanf ("%s", name);
		            scanf ("%c", &temp);
		            printf ("Enter the type of cargo(F-fragile/T-tough):");
		            scanf ("%c", &type);
		            if (type != 'F' && type != 'f' && type != 'T' && type != 't')
		            {
		                printf ("Invalid Input!");
		            }
		            else
		            {
		                printf ("Enter the weight of cargo(in kg):");
		                scanf ("%d", &wt);
		                if (wt > MAX_LOAD - head->gross_wt)
		            	{
			                printf ("OOPS!Weight of cargo is more than the available capacity\n");
			            }
		                else
			            {
			                printf ("Enter station code of destination:");
			                scanf ("%d", &end);
			                if (end > i && end <= MAX_STATION)
			                {
			                    enqueue (name, type, wt, i, end);
			                }
			                else
			                {
			                    printf ("Invalid destination!");
			                }
		            	}
		            }
		        }
	            else
		        printf ("Final station reached.Enqueue not possible");
	        }
	        else if (op == 2)
	        {
	            display_list ();
	        }
	        else
	        key = 0;
	        if (op != 0)
	        {
	            printf ("\nPress '1' to continue(enqueue or display) or '0' to exit(move to next station):");
	            scanf ("%d", &key);
	        }
            
        }
        if (front->destination == i)
	    {
	        printf ("\n#Details of the dispatched cargo");
	        printf ("\n.....................................................");
	        printf ("\nNAME\tTYPE\tWEIGHT\tSOURCE\tDESTINATION\tAMOUNT\n");
	        while (front != NULL && front->destination == i)
	        {
	            dequeue ();
	        }
	        printf (".....................................................\n");
	    }
        else
	    printf ("***No cargo to dispatch at station-%d***", i);
    }
    if (i >= MAX_STATION)
    printf ("\nFinal station reached");
    printf ("\n......................................");
    printf ("\n*** Total Amount collected = %d ***", head->amount);
    printf ("\n*** Total number of shippings = %d ***",head->source);
    printf ("\n\t\t\t***THANK YOU***\t\t\t");

    
    return(0);
}

void enqueue (char name[], char type, int wt, int start, int end)
{
    struct pqueue *ptr = head->next;
    struct pqueue *temp = NULL;
    temp = (struct pqueue *) malloc (sizeof (struct pqueue));
    if (temp == NULL)
    {
        printf ("Memory Error");
        exit;
    }
    strcpy (temp->name, name);
    temp->dispatch_no = 0;
    temp->type = type;
    temp->gross_wt = wt;
    temp->source = start;
    temp->destination = end;
    head->gross_wt = head->gross_wt + wt;
    head->dispatch_no++;
    head->source++;
    if (temp->type == 'F' || temp->type == 'f')
    {
        temp->amount = (end - start) * wt * 12;
    }
    else
    {
        temp->amount = (end - start) * wt * 10;
    }
    head->amount = head->amount + temp->amount;
    temp->next = NULL;
    if (head->next == NULL)
    {
        front = rear = temp;
        head->next = front;
    }
    else
    {
        if (ptr->destination > end)
	    {
	        temp->next = head->next;
	        head->next = temp;
	        front = temp;
	    }
        else
	    {
	        while (ptr->next != NULL && ptr->next->destination <= end)
	        {
	            ptr = ptr->next;
	        }
	        if (ptr->next == NULL)
	        {
	            ptr->next = temp;
	            rear = rear->next;
	        }
	        else
	        {
	            temp->next = ptr->next;
	            ptr->next = temp;
	        }
	    }
    }
  Create_dispatch ();
}

void display_list ()
{
    struct pqueue *ptr = front;
    if (front == NULL)
    {
        printf ("List is empty!!");
        return;
    }
    printf ("\nDISPATCH\tNAME\tTYPE\tWEIGHT\tSOURCE\tDESTINATION\tAMOUNT\n");
    while (ptr != NULL)
    {
        printf ("%d\t\t%s\t%c\t%d\t%d\t%d\t\t%d\n", ptr->dispatch_no, ptr->name, ptr->type, ptr->gross_wt, ptr->source, ptr->destination,ptr->amount);
        ptr = ptr->next;
    }
}

void Create_dispatch ()
{
    int i = 1;
    struct pqueue *temp = front;
    while (temp != NULL)
    {
        temp->dispatch_no = i;
        i++;
        temp = temp->next;
    }
}

void dequeue ()
{
    if (front == NULL)
    {
        printf ("Cargo container is EMPTY");
        return;
    }
    struct pqueue *temp = front;
    front = front->next;
    head->next = front;
    head->gross_wt = head->gross_wt - temp->gross_wt;
    head->dispatch_no--;
    printf ("%s\t%c\t%d\t%d\t%d\t\t%d\n", temp->name, temp->type, temp->gross_wt, temp->source, temp->destination, temp->amount);
    Create_dispatch ();
    free (temp);
}

