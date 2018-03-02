#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0

typedef struct mazeStruct{
 // char arr[32][32];  /* allows for a maze of size 30x30 plus outer walls */
 char **arr;           /* allows for a dynamic 2-D maze of any size */
 int **arr2;          /* dynamic 2-D array to keep track of visted positions */
 int xsize, ysize;
 int xstart, ystart;
 int xend, yend;
} maze;

struct nodeStruct
{
 int xpos, ypos;
 struct nodeStruct*  next;
};
 
typedef struct nodeStruct node;
typedef node* nodePtr; 

struct listStruct
{
  nodePtr   head;
};

typedef struct listStruct list;
/* call a function to intialize the list encased in a structure */
list init ()
{
  list s;
  s.head = NULL;
  return s;
}

void insertAtFront (node** hd, int x, int y)
{
 node* ptr = (node*) malloc (sizeof(node));
 ptr->xpos = x;
 ptr->ypos = y;
 ptr->next = *hd;       
 *hd = ptr;      
}

void removeFromFront (node** hd)
{
 node* ptr = *hd;

 if (ptr != NULL)
   {
    *hd = ptr->next;
    free (ptr);
   }
}

int main (int argc, char **argv){
  maze m1, mpos;
  node* head = NULL;
  list s1 = init();
  
  int xpos, ypos;
  int i,j;

  FILE *src;

  /* verify the proper number of command line arguments were given */
  if(argc != 2) {
     printf("Usage: %s <input file name>\n", argv[0]);
     exit(-1);
  }
   
  /* Try to open the input file. */
  if ( ( src = fopen( argv[1], "r" )) == NULL )
  {
    printf ( "Can't open input file: %s", argv[1] );
    exit(-1);
  }

  /* read in the size, starting and ending positions in the maze */
  fscanf (src, "%d %d", &m1.xsize, &m1.ysize);
  if(m1.xsize <= 0 || m1.ysize <= 0) // maze size is not 1 or more
    exit(-1);
  fscanf (src, "%d %d", &m1.xstart, &m1.ystart);
  fscanf (src, "%d %d", &m1.xend, &m1.yend);
  /* print them out to verify the input */
  printf ("size: %d, %d\n", m1.xsize, m1.ysize);
  printf ("start: %d, %d\n", m1.xstart, m1.ystart);
  printf ("end: %d, %d\n", m1.xend, m1.yend);

  /* allocate the maze and position array */
  m1.arr = (char **) malloc (sizeof(char *) * (m1.xsize+2) );
  for (i = 0; i < m1.xsize+2; i++)
     m1.arr[i] = (char *) malloc (sizeof(char ) * (m1.ysize+2) );
  
  m1.arr2 = (int **) malloc (sizeof(int *) * (m1.xsize+2) );
  for (i = 0; i < m1.xsize+2; i++)
     m1.arr2[i] = (int *) malloc (sizeof(int ) * (m1.ysize+2) );
  
  /* initialize the maze to empty */
  for (i = 0; i < m1.xsize+2; i++)
     for (j = 0; j < m1.ysize+2; j++)
       m1.arr[i][j] = '.';

  /* mark the borders of the maze with *'s */
  for (i=0; i < m1.xsize+2; i++)
    {
     m1.arr[i][0] = '*';
     m1.arr[i][m1.ysize+1] = '*';
    }
  for (i=0; i < m1.ysize+2; i++)
    {
     m1.arr[0][i] = '*';
     m1.arr[m1.xsize+1][i] = '*';
    }

  /* mark the starting and ending positions in the maze */
  m1.arr[m1.xstart][m1.ystart] = 's';
  m1.arr[m1.xend][m1.yend] = 'e';
		  
  /* mark the blocked positions in the maze with *'s */
  while (fscanf (src, "%d %d", &xpos, &ypos) != EOF)
    {
     m1.arr[xpos][ypos] = '*';
    }
  /* mark blocked positions/borders as visted */
  for (i = 0; i < m1.xsize+2; i++)
    for (j = 0; j < m1.ysize+2; j++)
    {
      if(m1.arr[i][j] == '.')
        m1.arr2[i][j] = FALSE;
      else if(m1.arr[i][j] == '*')
        m1.arr2[i][j] = TRUE;
    }

  /* print out the initial maze */
  for (i = 0; i < m1.xsize+2; i++)
    {
     for (j = 0; j < m1.ysize+2; j++)
       printf ("%c", m1.arr[i][j]);
     printf("\n");
    }
  
}