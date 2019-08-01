#include <iostream>
#include <fstream>

using namespace std;

// define directions N=1, E=2, S=3, W=4;
#define N 1
#define E 2
#define S 3
#define W 4

int is_block(int *maze_arry,int nRow, int nCol, int j, int i, int dir)
{   
    
    // check the direction is open or blocked
    
    switch(dir)
    {
        case N: 
            if(i==0)
                return 1;
            return *(maze_arry+nCol*(i-1)+j);

        case E: 
            if(j== (nCol-1))
                return 1;
            return *(maze_arry+nCol*i+j+1);
            
        case S: 
            if(i==(nRow-1))
                return 1;
            return *(maze_arry+nCol*(i+1)+j);
        case W: 
            if(j==0)
                return 1;
            return *(maze_arry+nCol*i+j-1);
    }
    return 0;
    
}

int left_turn(int current_dir)
{
    // Left turn
    switch(current_dir)
    {
        case N: return W;
        case E: return N;
        case S: return E;
        case W: return S;
    }
    return 0;
}


int right_turn(int current_dir)
{
    // Right turn
    switch(current_dir)
    {
        case N: return E;
        case E: return S;
        case S: return W;
        case W: return N;
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        cout << "Usage:" << endl;
        cout << " " << argv[0] << " <maze file> <solution file>" << endl;
        return 0;
    }
    string file_input  = argv[1];
    string file_output = argv[2];

    int nRow, nCol;     // the number of row and column
    int i, j;           // i, j for interation

    int Row=0;
    int Col=0;
    
    int dir;

    int x_current, y_current;
    int* maze_arry;


    ifstream f;
    f.open(file_input);
    
    // initialize maze array
    f >> nRow >> nCol;
    maze_arry = new int[nRow*nCol];

    // read data from input file
    while(f >> Row >> Col)
    {
        maze_arry[Row*nCol+Col]=1;
    }
    f.close();



    // print maze shape
    // comment out if unnecessary
    //cout << "Print maze" << endl;
    for(i=0;i<nRow;i++)
    {
        for(j=0;j<nCol;j++)
        {   
            if(*(maze_arry+i*nCol+j)==1)
            {   
                // printf("*");
            } else {
                *(maze_arry+i*nCol+j)=0;
                // printf(" ");
            }
        }
        // printf("\n");
    }


    // find starting point and direction
    for(j=0;j<nCol;j++)
    {
        if(*(maze_arry+j)==0)
        {
            x_current=j;
        }
    }
    y_current = 0;
    dir=S;


    // open outpuf file
    ofstream output(file_output);

    // cout << nRow << "," << nCol << endl;
    // cout << y_current << "," << x_current << endl;

    output << y_current << " " << x_current << endl;
    // while(in_Maze(nRow,nCol,x_current,y_current))
    while(y_current < (nRow-1))
    {
        // find which direction is open 
        // starting from the right of the location
        dir=right_turn(dir);
        while(is_block(maze_arry,nRow,nCol,x_current,y_current,dir))
        {
            dir=left_turn(dir);
        }
        // move the point to open direction
        switch(dir)
        {
            case N: 
                y_current--;
                break;
            case E: 
                x_current++;
                break;
            case S: 
                y_current++;
                break;
            case W: 
                x_current--;
                break;
        }
        // cout << y_current << "," << x_current << endl;
        output << y_current << " " << x_current << endl;

    }
    // cout << "\nEnd\n" << endl;
    output.close();
    delete [] maze_arry;
  
    return 0;
}

