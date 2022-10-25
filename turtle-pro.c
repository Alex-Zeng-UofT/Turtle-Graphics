/**
 * CSC A48 - Intro to Computer Science II, Summer 2020
 * 
 * This is the program file where you will implement your solution for
 * assignment 1. Please make sure you read through this file carefully
 * and that you understand what is provided and what you need to complete.
 * 
 * You will need to have read the handout carefully. Parts where you have to 
 * implement functionality are clearly labeled TODO.
 * 
 * Be sure to test your work thoroughly, our testing will be extensive and will
 * check that your solution is *correct*, not only that it provides 
 * functionality.
 * 
 * Developed by Mustafa Quraish for CSCA48
 * (c) Mustafa Quraish 2020
 */
#include "imgUtils.c"

// This lets the driver code override the image size if it needs to. Make sure 
// you don't hard-code these values anywhere!
#ifndef SIZEX
  #define SIZEX 512
  #define SIZEY 512
#endif 

/*---------------------------------------------------------------------------*/

/**
 * This struct contains one node of the linked list, which represents a single 
 * command to the Turtle. It's field should include:
 * 
 *  - cmd   : A char array of size 10 holding the command name
 * 
 *  - val   : An integer that stores a parameter for the command (like forward,
 *            backward and colour). 
 * 
 *  - next  : A pointer to a struct of the same type, this is used for the 
 *            linked list
 * 
 * TODO: Complete this struct definition
 ****/

typedef struct cmdnode {
	char cmd[10];
	int val;
	struct cmdnode *next;
	struct cmdnode *loop_head;
} CmdNode;

/*---------------------------------------------------------------------------*/

CmdNode *newCmdNode(char cmd[10], int val) {
  /** 
   * This function allocates a new CmdNode struct and initializes it's values 
   * based on the input paramaters given. The next pointer is always 
   * initialized to NULL.
   * 
   * If the 'cmd' parameter is not a correct command, then print
   * "Invalid command.\n" and return NULL.
   * 
   * Note that we will always pass in a value here, even if the 
   * command doesn't need one. In this case, we can just ignore 
   * it. It saves us from having to make separate functions to 
   * deal with this.
   * 
   * TODO: Implement this function
   */
	if(strcmp(cmd, "penup")!=0&&strcmp(cmd, "pendown")!=0&&
	strcmp(cmd, "colour")!=0&&strcmp(cmd, "forward")!=0&&strcmp(cmd, "loop")&&
	strcmp(cmd, "backward")!=0&&strcmp(cmd, "right")!=0&&strcmp(cmd, "left")!=0){
		printf("Invalid command.\n");
		return NULL;
		}
	CmdNode *node=(CmdNode *)calloc(1, sizeof(CmdNode));
	strcpy(node->cmd,cmd);
	node->val=val;
	node->next=NULL;
	node->loop_head=NULL;
  return node;
}

void printing(char *cmd, int val, int count){
	if(strcmp(cmd, "colour")==0||strcmp(cmd, "forward")==0||
		strcmp(cmd, "backward")==0||strcmp(cmd, "loop")==0){
			printf("%3d: %s %d\n", count, cmd, val);
		}
		else{
			printf("%3d: %s\n", count, cmd);
		}
	return;
}

void printingLoop(char *cmd, int val, int count){
	if(strcmp(cmd, "colour")==0||strcmp(cmd, "forward")==0||
		strcmp(cmd, "backward")==0){
			printf("%3d:   %s %d\n", count, cmd, val);
		}
		else{
			printf("%3d:   %s\n", count, cmd);
		}
	return;
}
/*---------------------------------------------------------------------------*/

void printCommandList(CmdNode *head) {
  /**
   * This function prints out each command in the linked list one after the 
   * other. Each command MUST also have a line number printed before it, this 
   * is what you will be using to modify / delete them. To do this, initialize 
   * a counter and then increment it for each command.
   * 
   * Depending on whether or not the command needs an additional value 
   * (like forward, backward and colour), use one of the following statements 
   * to print out the information for each node: 
   *            [ The format is "linenumber: command value" ]
   * 
   * printf("%3d: %s %d\n", ... );     [With a value]
   * 
   * printf("%3d: %s\n", ... );        [Without a value]
   * 
   * Obviously, you also need to pass in the correct parameters to the print 
   * function yourself, this is just so you have the correct format.
   * 
   * TODO: Implement this function
   */
	int count=0;
	CmdNode *p=head;
	while(p!=NULL){
		CmdNode *h=p->loop_head;
		if(strcmp(p->cmd, "loop")==0){
			printing(p->cmd, p->val, count);
			count++;
			while(h!=NULL){
				printingLoop(h->cmd,h->val, count);
				count++;
				h=h->next;
			}
		}
		else{
			printing(p->cmd, p->val, count);
		}
		count++;
		p=p->next;
	}
  return;
}

/*---------------------------------------------------------------------------*/

void queryByCommand(CmdNode *head, char cmd[10]) {
  /**
   * This function looks for commands in the linked list that match the input 
   * query. It prints them out in the same format as the printCommandList() 
   * function.
   * 
   * Make sure that the line number of the commands that match is the same as 
   * the line number that would be printed by the printCommandList() function.
   * 
   * --------------------------------------------------------------------------
   * 
   * For instance, if your printCommandList function outputs
   * 
   *    0: penup
   *    1: forward 200
   *    2: right
   *    3: forward 50
   * 
   * Then, if this function is called with the same list and cmd = "forward", 
   * then your output here should be
   * 
   *    1: forward 200
   *    3: forward 50
   * 
   * TODO: Implement this function
   */
	int count=0;
	CmdNode *p=head;
	while(p!=NULL){
		CmdNode *h=p->loop_head;
		if(strcmp(p->cmd, cmd)==0){
			printing(p->cmd, p->val, count);
		}
		count++;
		if(strcmp(p->cmd, "loop")==0){
			while(h!=NULL){
				if(strcmp(h->cmd, cmd)==0){
					printing(h->cmd, h->val, count);
				}
				count++;
				h=h->next;
			}
		}
		p=p->next;
	}
  return;
}

/*---------------------------------------------------------------------------*/

int countCommands(CmdNode *head) {
  /**
   * This function counts and returns the length of the linked list. It 
   * requires list traversal.
   * 
   * TODO: Implement this function
   */
	int count=0;
	CmdNode *p=head;
	while(p!=NULL){
		CmdNode *h=p->loop_head;
		while(h!=NULL){
			h=h->next;
			count++;
		}
		p=p->next;
		count++;
	}
  return count;
}

/*---------------------------------------------------------------------------*/

CmdNode *insertCommand(CmdNode *head, CmdNode *new_CmdNode) {
  /**
   * This function inserts the node new_CmdNode *at the tail* of the linked 
   * list. (You are adding a command at the end).
   * 
   * If head == NULL, then the linked list is still empty.
   * 
   * It returns a pointer to the head of the linked list with the new node 
   * added into it.
   * 
   * TODO: Implement this function
   */
	CmdNode *p=head;
	if(p==NULL){
		head=new_CmdNode;
		return head;
	}
	while(p->next!=NULL){
		p=p->next;
	}
	p->next=new_CmdNode;
  return head;
}

/*---------------------------------------------------------------------------*/


CmdNode *deleteCommandList(CmdNode *head) {
  /**
   * This function deletes the linked list of commands, releasing all the 
   * memory allocated to the nodes in the linked list.
   * 
   * Returns a NULL pointer so that the head of the list can be set to NULL
   * after deletion.
   * 
   * TODO: Implement this function
   */
	CmdNode *q=NULL;
	CmdNode *p=head;
	while(p!=NULL){
		CmdNode *h=p->loop_head;
		while(h!=NULL){
			q=h->next;
			free(h);
			h=q;
		}
		q=p->next;
		free(p);
		p=q;
	}
  return NULL;
}

/*---------------------------------------------------------------------------*/

void insertCommandLoop(CmdNode *loopNode, CmdNode *new_CmdNode){
	CmdNode *p=loopNode;
	CmdNode *h=p->loop_head;
	loopNode->loop_head=insertCommand(h, new_CmdNode);
	return;
}

int penPosition(CmdNode *c){
	if(strcmp(c->cmd, "penup")==0)
		return -1;
	if(strcmp(c->cmd, "pendown")==0)
		return 1;
	return -1;
}

int getDirection(CmdNode *c, int current){
	if(strcmp(c->cmd, "left")==0)
		current -= 1;
	else if(strcmp(c->cmd, "right")==0)
		current += 1;
	if(current>4)
		current = 1;
	if(current<1)
		current = 4;
	return current;
}


int forwardsH(int x, int val, int direction){
	if(direction==1)
		x += val;
	if(direction==3)
		x -= val;
	if(x>SIZEX-1)
		x=SIZEX-1;
	if(x<0)
		x=0;
	return x;
}

int forwardsV(int y, int val, int direction){
	if(direction==2)
		y += val;
	if(direction==4)
		y -= val;
	if(y>SIZEY-1)
		y=SIZEY-1;
	if(y<0)
		y=0;
	return y;
}

int backwardsH(int x, int val, int direction){
	if(direction==1)
		x -= val;
	if(direction==3)
		x += val;
	if(x>SIZEX-1)
		x=SIZEX-1;
	if(x<0)
		x=0;
	return x;
}

int backwardsV(int y, int val, int direction){
	if(direction==2)
		y -= val;
	if(direction==4)
		y += val;
	if(y>SIZEY-1)
		y=SIZEY-1;
	if(y<0)
		y=0;
	return y;
}

void run(Image *im, CmdNode *head, int *endX, int *endY) {
  /**
   * This function runs the list of commands to move the turtle around and draw 
   * the image, and returns the final position of the turtle in the variables 
   * endX and endY.
   * 
   * --------------------------------------------------------------------------
   * 
   * NOTE: In the image we work with, the top-left pixel is (0,0),
   *       - x increases as you go right, up till SIZEX-1
   *       - y increases as you go down, up till SIZEY-1
   * 
   *                 (0,0)                 (SIZEX-1, 0)
   *                   x------------------------x
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |          IMAGE         |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   x------------------------x
   *             (0, SIZEY-1)            (SIZEX-1, SIZEY-1)
   * 
   * The image is in grayscale (black and white), so the colours are numbers 
   * from [0-255] where 0 is black, 255 is white, and the values in between 
   * are varying levels of gray.
   * 
   * You need to understand how the (x,y) values are stored so you know how 
   * they should be updated when you move (down means y increases, etc). You do 
   * not need to use the 'im' variable for anything other than passing it into 
   * the drawLine() function described below.
   * 
   * --------------------------------------------------------------------------
   * 
   * Here's the setup - There is a turtle (with a pen) that walks along the 
   * image. When the pen is down (on the paper), it draws a line along the path 
   * that it walks on. (If you want to play around with this, consider looking 
   * at the `turtle` library in python!)
   * 
   * The turtle initially starts at pixel (0, 0) [at the top left], 
   * facing right (in the positive x direction). The pen starts off
   * as `down`, with the default colour being black (0).
   * 
   * You need to go through the linked list and 'run' the commands to keep 
   * track of the turtles position, and draw the appropriate lines. Here is 
   * what each command should do:
   * 
   *  - penup          : Put the pen up (stop drawing)
   *  - pendown        : Put the pen down (start / continue drawing)
   *  - colour <val>   : Draw lines in colour <val> from now on
   *  - forward <val>  : Move the turtle forward <val> steps (pixels) 
   *                     in the direction it is facing.
   *  - backward <val> : Same as above, except move backwards
   *  - right          : Turn the turtle to the right by 90 degrees
   *  - left           : Turn the turtle to the left by 90 degrees
   * 
   * NOTE: Make sure that you do *not* go outside the image. For this, set the 
   * maximum and minimum values of x and y to be 0 and SIZEX-1 / SIZEY-1 
   * respectively.
   * 
   * For instance, if the turtle is at (0,0) facing right, and your command is
   * `forward 100000`, it will only go forward till (SIZEX-1, 0), and end 
   * up at the rightmost pixel in that row.
   * 
   * IMPORTANT: Once you are done with all the commands, make sure you save the 
   * final (x,y) location of the turtle into the variables endX and endY.
   * 
   * --------------------------------------------------------------------------
   * 
   * We have already implemented a drawLine() function (in imgUtils.c) which 
   * you should use to actually draw the lines. It takes in the following:
   * 
   *      - a pointer to an image struct (use 'im')
   *      - (x,y) location of start point
   *      - (x,y) location of end point
   *      - a colour to draw the line in [0-255]
   *          
   * Note that this function only draws horizontal and vertical lines, so 
   * either the x values or the y values of both points must be the same. 
   * Both these points *must* also be within the image. 
   *          [ 0 <= x < SIZEX,  0 <= y < SIZEY ]
   * 
   * 
   * TODO: Implement this function
   */
	CmdNode *p=head;
	int pen=1;
	int direction=1;
	int x1=0;
	int y1=0;
	int x2=0;
    int	y2=0;
	int colour=0;
	while(p!=NULL){
		if(strcmp(p->cmd, "loop")==0){
			for(int i=0;i<p->val;i++){
				CmdNode *h=p->loop_head;
				while(h!=NULL){
					if(strcmp(h->cmd, "penup")==0||strcmp(h->cmd, "pendown")==0){
						pen=penPosition(h);
					}
					else if(strcmp(h->cmd, "left")==0||strcmp(h->cmd, "right")==0){
						direction=getDirection(h, direction);
					}
					else if(strcmp(h->cmd, "colour")==0){
						if(p->val>255){
							p->val=255;
						}
						if(p->val<0){
							p->val=0;
						}
						colour = h->val;
					}
					else if(strcmp(h->cmd, "forward")==0){
						if(direction==1||direction==3){
							x2=(forwardsH(x1, h->val, direction));
						}
						if(direction==2||direction==4){
							y2=(forwardsV(y1, h->val, direction));
						}
						if(pen==1){
							drawLine(im, x1, y1, x2, y2, colour);
						}
						x1=x2;
						y1=y2;
					}
					if(strcmp(h->cmd, "backward")==0){
						if(direction==1||direction==3){
							x2=backwardsH(x1, h->val, direction);
						}
						if(direction==2||direction==4){
							y2=backwardsV(y1, h->val, direction);
						}
						if(pen==1){
							drawLine(im, x1, y1, x2, y2, colour);
						}
						x1=x2;
						y1=y2;
					}
					h=h->next;
				}
			}
		}
		if(strcmp(p->cmd, "penup")==0||strcmp(p->cmd, "pendown")==0){
			pen=penPosition(p);
	    }
		else if(strcmp(p->cmd, "left")==0||strcmp(p->cmd, "right")==0){
			direction=getDirection(p, direction);
	    }
		else if(strcmp(p->cmd, "colour")==0){
			if(p->val>255){
				p->val=255;
			}
			if(p->val<0){
				p->val=0;
			}
			colour = p->val;
		}
		else if(strcmp(p->cmd, "forward")==0){
			if(direction==1||direction==3){
				x2=(forwardsH(x1, p->val, direction));
			}
			if(direction==2||direction==4){
				y2=(forwardsV(y1, p->val, direction));
			}
			if(pen==1){
				drawLine(im, x1, y1, x2, y2, colour);
			}
			x1=x2;
			y1=y2;
		}
		if(strcmp(p->cmd, "backward")==0){
			if(direction==1||direction==3){
				x2=backwardsH(x1, p->val, direction);
			}
			if(direction==2||direction==4){
				y2=backwardsV(y1, p->val, direction);
			}
			if(pen==1){
			drawLine(im, x1, y1, x2, y2, colour);
			}
			x1=x2;
			y1=y2;
		}

		p=p->next;
	}
	*endX=x2;
	*endY=y2;
  return;
}

/*---------------------------------------------------------------------------*/
// All done!