/******************************************************************************
Author: SACHIN TYAGI(B11030) and SAHIL MUTNEJA(B11031)
Namr: AI_assignment.c
Puprpose: Solving 8/15/24 puzzle game
Features: 1.User can select which puzzle to solve.
          2.User can select the algorithm which he want to use from:-
                 a.Hill Climbing
                 b.Best Firsrt Search
                 c.A* 
          3.User can select heuristic evaluation function. 
*****************************************************************************/


#include<stdio.h>
#include<stdlib.h>

int puzzle=0;
int lastind=0;
int movesarr[10000];
int closedind=0;

int checkstate(int state[puzzle][puzzle],int closed[][puzzle][puzzle])
{
  int k;
  for(k=0;k<closedind;k++)
    {
      if(acheived(closed[k],state))
	return 0;
    }
  return 1;
}
/***it will compare the goal and board state if equal return 1 else 0********/
int acheived(int board[][puzzle],int goal[][puzzle])
{
  int row,col;
  for(row=0;row<puzzle;row++)
    {
      for(col=0;col<puzzle;col++)
	{
	  if(board[row][col]!=goal[row][col])
	    return 0;
	}
    }
  return 1;
}

/*****copy the old state to the new state********/
copy(int oldstate[][puzzle],int newstate[][puzzle])
{
  int i,j;
  for(i=0;i<puzzle;i++)
    {
      for(j=0;j<puzzle;j++)
	{
	  newstate[i][j]=oldstate[i][j];
	}
    }
}


/***it has to evaluation function depending on the choice it will use one and will evaluate the states accordingly****************/

calculatehval(int state[][puzzle],int goal[][puzzle],int heuristicval[],int index,int funchoice,int algochoice)
{

  int i,j,k,l;
  int hval=0;
  /*****************for manhattan heuristic function***********/
  if(funchoice==1)
    {
      for(i=0;i<puzzle;i++)
	{
	  for(j=0;j<puzzle;j++)
	    {
	      if(state[i][j]!=0)
		{
		  for(k=0;k<puzzle;k++)
		    {
		      for(l=0;l<puzzle;l++)
			{
			  if(state[i][j]==goal[k][l])
			    {
			      int hdiff=l-j;
			      if(hdiff<0)
				hdiff=-hdiff;
			      int vdiff=k-i;
			      if(vdiff<0)
				vdiff=-vdiff;
			      hval+=hdiff+vdiff;
			    }
			}
		    }
		}
	    }
	}
      heuristicval[index]=hval;
    }

  /********************for hamming heuristic function***************/
  else if(funchoice==2)
    {
      for(i=0;i<puzzle;i++)
	{
	  for(j=0;j<puzzle;j++)
	    {
	      if(state[i][j]!=goal[i][j])
		{
		  hval+=1;
		}
	    }
	}
      heuristicval[index]=hval;
    }
    /***************************************************/
}

/******this function will generate the states*****************/     
generate_states(int board[][puzzle],int queueforstates[][puzzle][puzzle],int heuristicval[],int goalstate[][puzzle],int index,int parent[][puzzle],int funchoice,int algochoice,int closed[][puzzle][puzzle])
{
  int row,col;
  int rowindex=0,colindex=0;
  for(row=0;row<puzzle;row++)
    {
      for(col=0;col<puzzle;col++)
	{
	  if(board[row][col]==0)//finding the location of the empty tile
	    {
	      rowindex=row;
	      colindex=col;
	      break;
	    }
	}
    }

  int tempstate[puzzle][puzzle];
  if(rowindex==0 && colindex==0)//if empty tile is at top left corner we will get two states
    {
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex][colindex+1];
      tempstate[rowindex][colindex+1]=0;
      //if(!acheived(tempstate,parent))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//calculating the hvalue of the state
	  index++;
	}
      
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex+1][colindex];
      tempstate[rowindex+1][colindex]=0;
      //if(!acheived(tempstate,parent))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//calculating the hvalue if the state
	  index++;
	}
      lastind=index;
    }
  else if(rowindex==0 && colindex!=0 && colindex!=puzzle-1)//if empty tile is at top row, excluding the top left corner and top right corner, the we have three states
    {
	 
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex][colindex+1];
      tempstate[rowindex][colindex+1]=0;
      //      if(!acheived(tempstate,parent))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of the state 
	  index++;
	}
      
      
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex+1][colindex];
      tempstate[rowindex+1][colindex]=0;
      //      if(!acheived(tempstate,parent))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluatning the hvalue of the state
	  index++;
	}
      
      
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex][colindex-1];
      tempstate[rowindex][colindex-1]=0;
      //      if(!acheived(tempstate,parent))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of the state
	  index++;
	}
      lastind=index;
    }
  else if(rowindex==0 && colindex==puzzle-1)//if empty tile is at top right corner,the we will have two states
    {
	 
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex][colindex-1];
      tempstate[rowindex][colindex-1]=0;
      //      if(!acheived(tempstate,parent))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of the state
	  index++;
	}
      
      
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex+1][colindex];
      tempstate[rowindex+1][colindex]=0;
      //      if(!acheived(tempstate,parent))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of the state
	  index++;
	}
      lastind=index;
    }
   
  else if(rowindex==puzzle-1 && colindex==0)//if empty tile is at bottom left corner,then we will have two states
    {
      
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex][colindex+1];
      tempstate[rowindex][colindex+1]=0;
      // if(!acheived(parent,tempstate))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//calculating the hvalue of the state
	  index++;
	}
      
      
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex-1][colindex];
      tempstate[rowindex-1][colindex]=0;
      //      if(!acheived(parent,tempstate))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//calculating the hvalue of the state
	  index++;
	}
	lastind=index;
    }
   
  else if(rowindex==puzzle-1 && colindex!=0 && colindex!=puzzle-1)//if empty tile is at bottom row, except bottom left and bottom right corner,the we will have three states
    {
	 
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex][colindex+1];
      tempstate[rowindex][colindex+1]=0;
      //if(!acheived(parent,tempstate))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of the state
	  index++;
	}
      
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex-1][colindex];
      tempstate[rowindex-1][colindex]=0;
      //      if(!acheived(parent,tempstate))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of the state
	  index++;
	}
      
      
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex][colindex-1];
      tempstate[rowindex][colindex-1]=0;
      //      if(!acheived(parent,tempstate))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of the state
	  index++;
	}
      lastind=index;
    }
    
  else if(rowindex==puzzle-1 && colindex==puzzle-1)//if empty tile is at bottom right corner,then we will have two states
    {
	 
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex][colindex-1];
      tempstate[rowindex][colindex-1]=0;
      //if(!acheived(parent,tempstate))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of the state
	  index++;
	}
      
      
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex-1][colindex];
      tempstate[rowindex-1][colindex]=0;
      //      if(!acheived(parent,tempstate))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of the state
	  index++;
	}
      lastind=index;
    }
    
  else if(rowindex!=0 && colindex==0 && rowindex!=puzzle-1)//if empty tile is in left col, except the top left and bottom right corner, then we will have three states
    {
	 
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex][colindex+1];
      tempstate[rowindex][colindex+1]=0;
      //      if(!acheived(parent,tempstate))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of hte state
	  index++;
	}
      
	 
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex-1][colindex];
      tempstate[rowindex-1][colindex]=0;
      //      if(!acheived(parent,tempstate))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of the state
	  index++;
	}
      
      
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex+1][colindex];
      tempstate[rowindex+1][colindex]=0;
      //      if(!acheived(parent,tempstate))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of the state
	  index++;
	}
      lastind=index;
    }

  else if(rowindex!=puzzle-1 && colindex==puzzle-1 && rowindex!=0)//if empty tile is at right col,except the top right and bottom right corner then we will have three states
    {
	 
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex][colindex-1];
      tempstate[rowindex][colindex-1]=0;
      //      if(!acheived(parent,tempstate))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of the state
	  index++;
	}
      
      
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex-1][colindex];
      tempstate[rowindex-1][colindex]=0;
      //      if(!acheived(parent,tempstate))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of the state
	  index++;
	}
      
      
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex+1][colindex];
      tempstate[rowindex+1][colindex]=0;
      //      if(!acheived(parent,tempstate))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of the state
	  index++;
	}
      lastind=index;
    }
    
  else //if tile is somwhere inside then we will have four states
    {
	 
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex][colindex+1];
      tempstate[rowindex][colindex+1]=0;
      //      if(!acheived(parent,tempstate))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of the state
	  index++;
	}
	  
	  
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex-1][colindex];
      tempstate[rowindex-1][colindex]=0;
      //      if(!acheived(parent,tempstate))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of the state
	  index++;
	}
      
      
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex][colindex-1];
      tempstate[rowindex][colindex-1]=0;
      //      if(!acheived(parent,tempstate))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluating the hvalue of the state
	  index++;
	}
      
      
      copy(board,tempstate);
      tempstate[rowindex][colindex]=tempstate[rowindex+1][colindex];
      tempstate[rowindex+1][colindex]=0;
      //      if(!acheived(parent,tempstate))//avoiding the repeated insertion of the states in the list
      if(checkstate(tempstate,closed))
	{
	  copy(tempstate,queueforstates[index]);
	  calculatehval(queueforstates[index],goalstate,heuristicval,index,funchoice,algochoice);//evaluaitng the hvalue of the state
	  index++;
	}
      lastind=index;
    }
}

//function to sort the states according to the hvalues
quicksort(int arr[],int point[][puzzle][puzzle],int first,int last)
{
  if(first<last)
    {
      int i=first,j=last,pivot=first,temp;
      int temp1[puzzle][puzzle];
      while(i<j)
	{
	  while(arr[i]<=arr[pivot] && i<last)
	    i++;
	  while(arr[j]>arr[pivot])
	    j--;
	  if(i<j)
	    {
	      temp=arr[i];
	      copy(point[i],temp1);
	      arr[i]=arr[j];
	      copy(point[j],point[i]);
	      arr[j]=temp;
	      copy(temp1,point[j]);
	    }
	}
      temp=arr[pivot];
      copy(point[pivot],temp1);
      arr[pivot]=arr[j];
      copy(point[j],point[pivot]);
      arr[j]=temp;
      copy(temp1,point[j]);
      quicksort(arr,point,first,j-1);
      quicksort(arr,point,j+1,last);
    }	    
}

/***********hill climbing algorithm implemetation*********************/
int hill_climbing(int puzzle)
{
  int row,col;
  int board[puzzle][puzzle];//store the current board
  int goalstate[puzzle][puzzle];//stoer goal state
  int queueforstates[10][puzzle][puzzle];//queue for storing the states
  int heuristicval[10];//array to store the hvalues
  int parent[puzzle][puzzle];//array to store the parent 
  int iterations=0;  
  int closed[10000][puzzle][puzzle];
  copy(board,closed[closedind]);
  closedind++;
  int funchoice;
  printf("Select the heuristic function which you want to use:\n");
  printf("1.Manhattan priority function(It will simply take add the horizontal and vertical distance of the misplaced tile)\n2.Hamming priority function(It will simply count the number of misplaced tiles)\n");
  scanf("%d",&funchoice);//taking input from the user to select the heuristic function


  copy(board,parent);
  printf("Enter the initial state of the puzzle\n");
  for(row=0;row<puzzle;row++)//loop for storing the initial state of the puzzle
    {
      for(col=0;col<puzzle;col++)
	{
	  printf("Enter the tile no. at position (%d,%d) (for empty tile enter 0)\n",row+1,col+1);
	  scanf("%d",&board[row][col]);
	}
    }
  printf("Enter the goal state\n");
  for(row=0;row<puzzle;row++)//loop for storing the goal state of the puzzle
    {
      for(col=0;col<puzzle;col++)
	{
	  printf("Enter the tile no. at position (%d,%d) in goal (for empty tile enter 0)\n",row+1,col+1);
	  scanf("%d",&goalstate[row][col]);
	}
    }
  int i,j;
  
  for(i=0;i<puzzle;i++)//printing the start state
    {
      for(j=0;j<puzzle;j++)
	printf("\t%d",board[i][j]);
      printf("\n");
    }
  printf("\n****************************************\n");
      
  while(!acheived(board,goalstate))//loop till the popped state from the queue is not goal
    {
      if(iterations<3000)
      {
	generate_states(board,queueforstates,heuristicval,goalstate,0,parent,funchoice,0,closed);//calling function to generate states
	//if(lastind==0)
	//  break;
	  quicksort(heuristicval,queueforstates,0,lastind-1);//sorting the states on the basis of th ehvalue
	  copy(board,parent);
	  copy(queueforstates[0],board);//selecting the state with least heuristic value
	  copy(board,closed[closedind]);
	  closedind++;
	  for(i=0;i<puzzle;i++)//printing the newly selected state
	    {
	      for(j=0;j<puzzle;j++)
		printf("\t%d",board[i][j]);
	      printf("\n");
	    }
	  printf("\n****************************************\n");
	  iterations++;
      }
      else
	break;
    }
  if(iterations>=3000)
    printf("No possible solution\n");
}

/**********************************************************************/

/*******its just an extension of quick sort with one more argument***********/
extendquicksort(int arr[],int point[][puzzle][puzzle],int stateparent[][puzzle][puzzle],int first,int last)
{
  if(first<last)
    {
      int i=first,j=last,pivot=first,temp;
      int temp1[puzzle][puzzle];
      int temp2[puzzle][puzzle];
      while(i<j)
	{
	  while(arr[i]<=arr[pivot] && i<last)
	    i++;
	  while(arr[j]>arr[pivot])
	    j--;
	  if(i<j)
	    {
	      temp=arr[i];
	      copy(point[i],temp1);
	      copy(stateparent[i],temp2);
	      arr[i]=arr[j];
	      copy(point[j],point[i]);
	      copy(stateparent[j],stateparent[i]);
	      arr[j]=temp;
	      copy(temp1,point[j]);
	      copy(temp2,stateparent[j]);
	    }
	}
      temp=arr[pivot];
      copy(point[pivot],temp1);
      copy(stateparent[pivot],temp2);
      arr[pivot]=arr[j];
      copy(point[j],point[pivot]);
      copy(stateparent[j],stateparent[pivot]);
      arr[j]=temp;
      copy(temp1,point[j]);
      copy(temp2,stateparent[j]);
      extendquicksort(arr,point,stateparent,first,j-1);
      extendquicksort(arr,point,stateparent,j+1,last);
    }	    
}

/************implementation of best first search**********************/
bestfirst(int puzzle)
{
  int row,col;
  int startstate[puzzle][puzzle];
  int board[puzzle][puzzle];
  int goalstate[puzzle][puzzle];
  int queueforstates[10][puzzle][puzzle];
  int heuristicval[10];
  int parent[puzzle][puzzle];

  int statesqueue[10000][puzzle][puzzle];//array to store the list just as open
  int stateshval[10000];//array to store the hvalue of the state
  int stateparent[10000][puzzle][puzzle];//array to store the parent of the corresponding state
  int solution[10000][puzzle][puzzle];//array to store the solution
  int closed[10000][puzzle][puzzle];//closed list containing states which are already popped
  int closedparent[10000][puzzle][puzzle];//array to store the parents of the closed list states
  int iterations=0;

  int funchoice;
  printf("Select the heuristic function which you want to use:\n");
  printf("1.Manhattan priority function(It will simply take add the horizontal and vertical distance of the misplaced tile)\n2.Hamming priority function(It will simply count the number of misplaced tiles)\n");
  scanf("%d",&funchoice);//asking user for the choice of heuristic function


  printf("Enter the initial state of the puzzle\n");
  for(row=0;row<puzzle;row++)//loop to store the initial state of the puzzle
    {
      for(col=0;col<puzzle;col++)
	{
	  printf("Enter the tile no. at position (%d,%d) (for empty tile enter 0)\n",row+1,col+1);
	  scanf("%d",&board[row][col]);
	}
    }
  printf("Enter the goal state\n");
  for(row=0;row<puzzle;row++)//loop to store the goal state
    {
      for(col=0;col<puzzle;col++)
	{
	  printf("Enter the tile no. at position (%d,%d) in goal (for empty tile enter 0)\n",row+1,col+1);
	  scanf("%d",&goalstate[row][col]);
	}
    }
  copy(board,startstate);
  copy(board,statesqueue[0]);
  int i,j;
  int k,l;
  int startind=1;
  int ecount=0;
  int tempcount=0;
  //int closedind=0;
  while(!acheived(board,goalstate))//loop till board state is not eqaul to goal state
    {
      if(iterations<3000)
	{
	  generate_states(board,queueforstates,heuristicval,goalstate,0,stateparent[0],funchoice,0,closed);//calling function to generate state
	  //if(lastind==0)
	  // break;
	  copy(queueforstates[0],statesqueue[0]);
	  stateshval[0]=heuristicval[0];
	  copy(board,stateparent[0]);
	  for(ecount=1;ecount<lastind;ecount++)//loop to store the generated state in the open list
	    {
	      copy(queueforstates[ecount],statesqueue[startind]);
	      stateshval[startind]=heuristicval[ecount];
	      copy(board,stateparent[startind]);
	      startind++;
	    }
	  extendquicksort(stateshval,statesqueue,stateparent,0,startind-1);//sorting the states on the basis of the heuristic value
	  copy(stateparent[0],closedparent[closedind]);
	  copy(statesqueue[0],board);
	  copy(statesqueue[0],closed[closedind]);
	  closedind++;
	  iterations++;
	}
      else
	break;
    }
  if(iterations>=3000)
    {
      printf("No possible solution exist\n");
      return;
    }
  
  //  printf("Printing path:****************************************\n");
  int currentstate[puzzle][puzzle];
  int pindex=0;
  int scount=0;
  copy(goalstate,currentstate);
  copy(goalstate,solution[scount]);
  scount++;
  pindex=closedind-1;
  while(!acheived(currentstate,startstate))//loop to store the path in solution array
    {
      copy(closedparent[pindex],currentstate);
      copy(closedparent[pindex],solution[scount]);
      scount++;
      for(i=0;i<1000;i++)
	{
	  if(acheived(closed[i],currentstate))
	    {
	      pindex=i;
	      break;
	    }
	}
    }
  
  scount-=1;
  for(;scount>=0;scount--)//loop to print the path
    {
      for(i=0;i<puzzle;i++)
	{
	  for(j=0;j<puzzle;j++)
	    printf("\t%d",solution[scount][i][j]);
	  printf("\n");
	}
      printf("\n****************************************\n");
    }
}

/*********************************************************************/
/***its juxt an extension of extendquicksort with one more argument**********/
extendedquicksort(int arr[],int point[][puzzle][puzzle],int stateparent[][puzzle][puzzle],int movearr[],int first,int last)
{
  if(first<last)
    {
      int i=first,j=last,pivot=first,temp,temp3;
      int temp1[puzzle][puzzle];
      int temp2[puzzle][puzzle];
      while(i<j)
	{
	  while(arr[i]<=arr[pivot] && i<last)
	    i++;
	  while(arr[j]>arr[pivot])
	    j--;
	  if(i<j)
	    {
	      temp=arr[i];
	      temp3=movearr[i];
	      copy(point[i],temp1);
	      copy(stateparent[i],temp2);
	      arr[i]=arr[j];
	      movearr[i]=movearr[j];
	      copy(point[j],point[i]);
	      copy(stateparent[j],stateparent[i]);
	      arr[j]=temp;
	      movearr[j]=temp3;
	      copy(temp1,point[j]);
	      copy(temp2,stateparent[j]);
	    }
	}
      temp=arr[pivot];
      temp3=movearr[pivot];
      copy(point[pivot],temp1);
      copy(stateparent[pivot],temp2);
      arr[pivot]=arr[j];
      movearr[pivot]=movearr[j];
      copy(point[j],point[pivot]);
      copy(stateparent[j],stateparent[pivot]);
      arr[j]=temp;
      movearr[j]=temp3;
      copy(temp1,point[j]);
      copy(temp2,stateparent[j]);
      extendedquicksort(arr,point,stateparent,movearr,first,j-1);
      extendedquicksort(arr,point,stateparent,movearr,j+1,last);
    }	    
}
/**********implementation of A* algorithm*******************/
astar(int puzzle)
{
  int row,col;
  int startstate[puzzle][puzzle];
  int board[puzzle][puzzle];
  int goalstate[puzzle][puzzle];
  int queueforstates[10][puzzle][puzzle];
  int heuristicval[10];
  int parent[puzzle][puzzle];

  int statesqueue[10000][puzzle][puzzle];
  int stateshval[10000];
  int stateparent[10000][puzzle][puzzle];
  int solution[1000][puzzle][puzzle];
  int closed[10000][puzzle][puzzle];
  int closedparent[10000][puzzle][puzzle];
  int iterations=0;

  int funchoice;
  printf("Select the heuristic function which you want to use:\n");
  printf("1.Manhattan priority function(It will simply take add the horizontal and vertical distance of the misplaced tile)\n2.Hamming priority function(It will simply count the number of misplaced tiles)\n");
  scanf("%d",&funchoice);//asking user for heuristic function choice

  printf("Enter the initial state of the puzzle\n");
  for(row=0;row<puzzle;row++)//loop to store the initial state
    {
      for(col=0;col<puzzle;col++)
	{
	  printf("Enter the tile no. at position (%d,%d) (for empty tile enter 0)\n",row+1,col+1);
	  scanf("%d",&board[row][col]);
	}
    }
  printf("Enter the goal state\n");
  for(row=0;row<puzzle;row++)//loop to store the goal state
    {
      for(col=0;col<puzzle;col++)
	{
	  printf("Enter the tile no. at position (%d,%d) in goal (for empty tile enter 0)\n",row+1,col+1);
	  scanf("%d",&goalstate[row][col]);
	}
    }
  copy(board,startstate);
  copy(board,statesqueue[0]);
  int i,j;
  int k,l;
  int startind=1;
  int ecount=0;
  int tempcount=0;
  //  int closedind=0;
  for(k=0;k<10000;k++)
    movesarr[k]=0;//array to store the moves to reach to the current state from starting state, its initilaised zero
  int moves=0;
  while(!acheived(board,goalstate))//loop till the board state is not equal to goal state
    {
      if(iterations<3000)
	{
	  generate_states(board,queueforstates,heuristicval,goalstate,0,stateparent[0],funchoice,0,closed);//calling function to generate the states
	  //if(lastind==0)
	  //break;
	  copy(queueforstates[0],statesqueue[0]);
	  stateshval[0]=heuristicval[0];
	  copy(board,stateparent[0]);
	  movesarr[0]=moves+1;
	  for(ecount=1;ecount<lastind;ecount++)//storing the generated states
	    {
	      movesarr[startind]=moves+1;
	      copy(queueforstates[ecount],statesqueue[startind]);
	      stateshval[startind]=heuristicval[ecount];
	      stateshval[startind]=movesarr[startind];//adding moves to the heuristic value of the state
	      copy(board,stateparent[startind]);
	      startind++;
	    }
	  extendedquicksort(stateshval,statesqueue,stateparent,movesarr,0,startind-1);//sorting the states on the basis of the heuristic value
	  copy(stateparent[0],closedparent[closedind]);
	  copy(statesqueue[0],board);
	  moves=movesarr[0];
	  copy(statesqueue[0],closed[closedind]);
	  closedind++;
	  iterations++;
	}
      else
	break;
    }
  if(iterations>=3000)
    {
      printf("No possible solution\n");
      return;
    }
  
 
  int currentstate[puzzle][puzzle];
  int pindex=0;
  int scount=0;
  copy(goalstate,currentstate);
  copy(goalstate,solution[scount]);
  scount++;
  pindex=closedind-1;
  while(!acheived(currentstate,startstate))//loop to store the solution
    {
      copy(closedparent[pindex],currentstate);
      copy(closedparent[pindex],solution[scount]);
      scount++;
      for(i=0;i<1000;i++)
	{
	  if(acheived(closed[i],currentstate))
	    {
	      pindex=i;
	      break;
	    }
	}
    }
  
  scount-=1;
  for(;scount>=0;scount--)//loop to print the path
    {
      for(i=0;i<puzzle;i++)
	{
	  for(j=0;j<puzzle;j++)
	    printf("\t%d",solution[scount][i][j]);
	  printf("\n");
	}
      printf("\n****************************************\n");
    }
}


/**************************main function**************************************/
int main()
{
  int value;
  printf("Enter the puzzle type (8 block, 15 block, 24,block)\n");
  scanf("%d",&value);
  if(value==8)
    puzzle=3;
  else if(value=15)
    puzzle=4;
  else
    puzzle=5;
  int choice=0;
  printf("Enter the choice for algorithm:\n");
  printf("1.HillClimbing\n2.BestFirst\n3.A* algorithm\n");
  scanf("%d",&choice);
  switch(choice)
    {
    case 1:
      hill_climbing(puzzle);
      break;
    case 2:
      bestfirst(puzzle);
      break;
    case 3:
      astar(puzzle);
      break;
    default:
      printf("Invalid Choice\n");
      exit(0);
    }
  return 0;
}
