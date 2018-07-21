#include<iostream>
using namespace std;

char board[3][3] =
    {
        { '_', '_', '_' },
        { '_', '_', '_' },
        { '_', '_', '_' }
    };

 
char player = 'X', opponent = 'O';


void draw() {
    cout<<"  "<<board[0][0]<<" |"<<" "<<board[0][1]<<" |"<<" "<<board[0][2]<<endl;
    cout<<"----+---+----\n";
    cout<<"  "<<board[1][0]<<" |"<<" "<<board[1][1]<<" |"<<" "<<board[1][2]<<endl;
    cout<<"----+---+----\n";
    cout<<"  "<<board[2][0]<<" |"<<" "<<board[2][1]<<" |"<<" "<<board[2][2]<<endl;
    cout<<endl;
}


const int alpha = -1000;
const int beta = 1000;

bool isMovesLeft(char board[3][3])
{
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (board[i][j]=='_')
                return true;
    return false;
}


int evaluate(char b[3][3])
{
    
	for (int row = 0; row<3; row++)
    {
        if (b[row][0]==b[row][1] &&
            b[row][1]==b[row][2])
        {
            if (b[row][0]==player)
                return -10;
            else if (b[row][0]==opponent)
                return 10;
        }
    }
 
    
    for (int col = 0; col<3; col++)
    {
        if (b[0][col]==b[1][col] &&
            b[1][col]==b[2][col])
        {
            if (b[0][col]==player)
                return -10;
 
            else if (b[0][col]==opponent)
                return +10;
        }
    }
 
    
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
    {
        if (b[0][0]==player)
            return -10;
        else if (b[0][0]==opponent)
            return +10;
    }
 
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
    {
        if (b[0][2]==player)
            return -10;
        else if (b[0][2]==opponent)
            return +10;
    }
 
    return 0;
}


int minimax(int depth, bool isMax, int alpha, int beta)
{
    int score = evaluate(board);
 
    if (score == 10)
        return score;
 
    if (score == -10)
        return score;
 
    if (isMovesLeft(board)==false)
        return 0;
 
    if (isMax)
    {
        int best = -1000;
 
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                if (board[i][j]=='_')
                {
                    board[i][j] = opponent;
 
                    best = max( best,
                        minimax( depth+1, !isMax, alpha, beta) );
                    alpha = max(best,alpha);
 
                    board[i][j] = '_';
                    if (beta <= alpha)
                        break;
                }
            }
            if (beta <= alpha)
                    break;
        }
        return best;
    }
 
    else
    {
        int best = 1000;
 
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                if (board[i][j]=='_')
                {
                    board[i][j] = player;
 
                    best = min(best,
                           minimax( depth+1, !isMax, alpha, beta));
 					beta = min(beta, best);
 					
                    board[i][j] = '_';
                    
                    if (beta <= alpha)
                        break;
                }
            }
            if (beta <= alpha)
                break;
        }
        return best;
    }
}


void computerMove() {
    
    int bestVal = -1000;
    int r = -1;
    int c = -1;
 
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            
            if (board[i][j]=='_')
            {
                board[i][j] = opponent;
 
                int moveVal = minimax( 0, false, alpha, beta);
 
                board[i][j] = '_';
 
                if (moveVal > bestVal)
                {
                    r = i;
                    c = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    
    board[r][c]=opponent;
    
}


void playerMove() {
    int move = 0;
    int r,c;
    do {
        cout<<"\nInput move ([1..9]): ";
        cin>>move;
        r = (move-1)/3;
        c = (move-1)%3;
        } while (move > 9 || move < 1 || board[r][c]=='X' || board[r][c]=='O');
    board[r][c]= player;
}

int main()
{
	cout<<"Let's play Tic-Tac-Toe Game !\n";
	draw();
	int play;
	cout<<"Computer : O  You : X"<<endl;
	cout<<"Play 1st or 2nd ?";
	cin>>play;
	for(int i=0;i<9 && evaluate(board)==0;i++ )
	{
		if((i+play) % 2 == 0)
            computerMove();
        else {
            draw();
            playerMove();
        }
	}
	
	switch(evaluate(board)) {
        case 0:
            printf("It's a draw !!!\n");
            break;
        case 10:
        	draw();
            printf("You lose !. Better luck next time :p\n");
            break;
        case -10:
            printf("It's just next to Impossible ! You've won the game :D \n");
            break;
    }
    cout<<"The final state of the board is :\n";
    draw();
	return 0;
}
