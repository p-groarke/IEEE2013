// Code for IEEEXtreme problem 3, computer society
// Copyright 2013 TeamFullOfLove
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

#define llong long long

using namespace std;

// Incrementing a direction value will result in a clockwise turn
enum Direction {NORTH = 0, EAST, SOUTH, WEST, NB_DIRECTIONS};
enum CellType {CORNER = 0, BORDER, INNER, START, EXIT, NB_CELL_TYPES};

// Linear Congruential Generator, pseudo-random generator.
class LCG
{
public:
    static const llong m = 281474976710656; // modulus, 2^48
    static const int a = 1664525; // multiplier
    static const int c = 1013904223; // increment

    LCG(int seed) : _seed(seed), _previousX(seed)
    {
    }

    int generate()
    {
        int _currentX = a * _previousX + (c % m);
        _previousX = _currentX;
        return _currentX;
    }
    
    int generate(int min, int max)
    {
        generate();
        return abs((_previousX % max) + min);
    }
    
private:
    int _seed;
    int _previousX;
};

class Cell
{
public:
    Cell(CellType cellType)
    : _cellType(cellType)
    {
        // Initially all cells have walls on four directions
        for(int i = 0; i < NB_DIRECTIONS; ++i)
            _wall[i] = true;
    }

    bool hasWall(Direction dir)
    {
        return _wall[dir];
    }

    CellType getCellType() const
    {
        return _cellType;
    }

    void setCellType(CellType newType)
    {
        _cellType = newType;
    }

    void addWall(Direction direction)
    {
        _wall[direction] = true;
    }

    void removeWall(Direction direction)
    {
        _wall[direction] = false;
    }

private:
    bool _wall[NB_DIRECTIONS];
    CellType _cellType;
};

class Maze
{
public:
    Maze(int rows, int columns, int pWall, LCG* generator)
        : _rows(rows), _columns(columns), _pWall(pWall), _generator(generator)
    {
        for(int i = 0; i < _rows; ++i)
        {
            vector<Cell> currentRow;
            
            for(int j = 0; j < _columns; ++j)
            {
                CellType currentType = computeCellType(i, j);
                Cell currentCell(currentType);
                currentRow.push_back(currentType);
            }

            _maze.push_back(currentRow);
        }

        setStartingPosition();
        setExitPosition();
        generateOpenings();
    }

    CellType getCellType(int row, int column)
    {
        return _maze[row][column].getCellType();
    }

    bool hasWall(int row, int column, Direction direction)
    {
        return _maze[row][column].hasWall(direction);
    }

    int getStartRow()
    {
        return _startRow;
    }

    int getStartColumn()
    {
        return _startColumn;
    }

    void updateAfterMove()
    {
        // Update inner cells only
        for(int i = 1; i < _rows - 1; ++i)
        {
            for(int j = 1; j < _columns - 1; ++j)
            {
                int random;
                
                // North
                random = _generator->generate(1, 100);
                if(random < _pWall)
                {
                    _maze[i][j].addWall(NORTH);
                    _maze[i - 1][j].addWall(SOUTH);
                }
                else
                {
                    _maze[i][j].removeWall(NORTH);
                    _maze[i - 1][j].removeWall(SOUTH);
                }
                // South
                random = _generator->generate(1, 100);
                if(random < _pWall)
                {
                    _maze[i][j].addWall(SOUTH);
                    _maze[i + 1][j].addWall(NORTH);
                }
                else
                {
                    _maze[i][j].removeWall(SOUTH);
                    _maze[i + 1][j].removeWall(NORTH);
                }
                // West
                random = _generator->generate(1, 100);
                if(random < _pWall)
                {
                    _maze[i][j].addWall(WEST);
                    _maze[i][j - 1].addWall(EAST);
                }
                else
                {
                    _maze[i][j].removeWall(WEST);
                    _maze[i][j - 1].removeWall(EAST);
                }
                // East
                random = _generator->generate(1, 100);
                if(random < _pWall)
                {
                    _maze[i][j].addWall(EAST);
                    _maze[i][j + 1].addWall(WEST);
                }
                else
                {
                    _maze[i][j].removeWall(EAST);
                    _maze[i][j + 1].removeWall(WEST);
                }
            }
        }
    }
    
private:
    CellType computeCellType(int row, int column)
    {
        if(row == 0 || row == _rows - 1)
        {
            if(column == 0 || column == _columns - 1)
                return CORNER;
            else
                return BORDER;
        }
        else if(column == 0 || column == _columns - 1)
        {
            //All corners will have been treated in previous if
            return BORDER;
        }
        else
        {
            return INNER;
        }
    }

    void setStartingPosition()
    {
        int numberBorderCells = 2 * ((_rows - 2) + (_columns - 2));
        
        int cellNumber = _generator->generate(1, numberBorderCells);
        int currentCellNumber = 0;

        for(int i = 0; i < _rows; ++i)
        {
            if(i == 0 || i == _rows -1) //For top and bottom rows, exclude corners
            {
                for(int j = 1; j < _columns - 1; ++j)
                {
                    ++currentCellNumber;
                    if(currentCellNumber == cellNumber)
                    {
                        _startRow = i;
                        _startColumn = j;
                        _maze[i][j].setCellType(START);
                        return;
                    }
                }
            }
            else // For middle rows, exclude inner cells
            {
                int j = 0;
                ++currentCellNumber;
                if(currentCellNumber == cellNumber)
                {
                    _startRow = i;
                    _startColumn = j;
                    _maze[i][j].setCellType(START);
                    return;
                }
                
                // I hope you like duplicated code
                j = _columns - 1;
                ++currentCellNumber;
                if(currentCellNumber == cellNumber)
                {
                    _startRow = i;
                    _startColumn = j;
                    _maze[i][j].setCellType(START);
                    return;
                }
            }
        }
    }

    void setExitPosition()
    {
        // Minus one because starting position is excluded
        int numberBorderCells = 2 * ((_rows - 2) + (_columns - 2)) - 1;

        int cellNumber = _generator->generate(1, numberBorderCells);
        int currentCellNumber = 0;

        for(int i = 0; i < _rows; ++i)
        {
            if(i == 0 || i == _rows -1) //For top and bottom rows, exclude corners
            {
                for(int j = 1; j < _columns - 1; ++j)
                {
                    if(i != _startRow || j != _startColumn)
                        ++currentCellNumber;
                    if(currentCellNumber == cellNumber)
                    {
                        _maze[i][j].setCellType(EXIT);
                        // Make opening for exit
                        if(i == 0)
                            _maze[i][j].removeWall(NORTH);
                        else
                            _maze[i][j].removeWall(SOUTH);
                        return;
                    }
                }
            }
            else // For middle rows, exclude inner cells
            {
                int j = 0;
                if(i != _startRow || j != _startColumn)
                    ++currentCellNumber;
                if(currentCellNumber == cellNumber)
                {
                    _maze[i][j].setCellType(EXIT);
                    _maze[i][j].removeWall(WEST);
                    return;
                }
                
                // I hope you like duplicated code
                j = _columns - 1;
                if(i != _startRow || j != _startColumn)
                    ++currentCellNumber;
                if(currentCellNumber == cellNumber)
                {
                    _maze[i][j].setCellType(EXIT);
                    _maze[i][j].removeWall(WEST);
                    return;
                }
            }
        }
    }

    void generateOpenings()
    {
        for(int i = 1; i < _rows - 1; ++i)
        {
            for(int j = 1; j < _columns - 1; ++j)
            {
                switch(_generator->generate(1, 4))
                {
                case 1:
                    _maze[i][j].removeWall(NORTH);
                    _maze[i - 1][j].removeWall(SOUTH);
                    break;
                case 2:
                    _maze[i][j].removeWall(SOUTH);
                    _maze[i + 1][j].removeWall(NORTH);
                    break;
                case 3:
                    _maze[i][j].removeWall(WEST);
                    _maze[i][j - 1].removeWall(EAST);
                    break;
                case 4:
                    _maze[i][j].removeWall(EAST);
                    _maze[i][j + 1].removeWall(WEST);
                    break;
                default:
                    break;
                }
            }
        }
    }
    
    int _rows;
    int _columns;

    // Store the position of starting cell to facilitate robot construction
    int _startRow;
    int _startColumn;

    int _pWall; // Probability of generating a wall in percent
    vector< vector<Cell> > _maze;

    LCG* _generator; // Pointer to random number generator instantiated in main()
};

class Robot
{
public:
    Robot(int maxMoves, int row, int column, Maze* maze)
        : _facing(EAST), _moves(0), _maxMoves(maxMoves), _row(row), _column(column), _maze(maze)
    {
    }

    void move()
    {
        if(!_maze->hasWall(_row, _column, _facing)
           && _maze->hasWall(_row, _column, (Direction)((_facing + 1) % NB_DIRECTIONS)))
            moveForward();
        else
            turnClockWise();

        ++_moves;

        _maze->updateAfterMove();
    }

    bool hasExited()
    {
        return _maze->getCellType(_row, _column) == EXIT;
    }

    bool hasReachedMaxMoves()
    {
        return _moves >= _maxMoves;
    }

    int getMoves()
    {
        return _moves;
    }

private:
    void turnClockWise()
    {
        _facing = (Direction)((_facing + 1) % NB_DIRECTIONS);
    }
    
    void moveForward()
    {
        switch(_facing)
        {
        case NORTH:
            --_row;
            break;
        case EAST:
            ++_column;
            break;
        case SOUTH:
            ++_row;
            break;
        case WEST:
            --_column;
            break;
        default:
            break;
        }
    }
    
    Direction _facing;
    int _moves;
    int _maxMoves;
    int _row;
    int _column;
    Maze* _maze; // Pointer to Maze declared in main
};

int main()
{
    int seed;
    int rows;
    int columns;
    int pWall;
    int maxMoves;

    cin >> seed >> rows >> columns >> pWall >> maxMoves;
    
    LCG generator(seed);
    Maze maze(rows, columns, pWall, &generator);
    Robot robbie(maxMoves, maze.getStartRow(), maze.getStartColumn(), &maze);

    while(!robbie.hasExited() && !robbie.hasReachedMaxMoves())
        robbie.move();

    if(robbie.hasExited())
        cout << "Robbie got out of the maze in " << robbie.getMoves() << " moves." << endl;
    else
        cout << "Robbie was trapped in the maze." << endl;
    
    return 0;
}
