
#include <iostream>
#include "geesespotter_lib.h"

void clean_board(char *board);
void print_board(char *board, std::size_t x_dim, std::size_t y_dim);
char *create_board(std::size_t x_dim, std::size_t y_dim);
void hide_board(char *board, std::size_t x_dim, std::size_t y_dim);
int mark(char *board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc,
         std::size_t y_loc);
bool is_game_won(char *board, std::size_t x_dim, std::size_t y_dim);
void compute_neighbours(char *board, std::size_t x_dim, std::size_t y_dim);
int reveal(char *board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc,
           std::size_t y_loc);
bool isnt_marked(char*board,int n)
{
    if((board[n]&marked_mask())==0)
    {
        return true;
    }
    return false;
}

char *create_board(std::size_t x_dim, std::size_t y_dim)
{
    char *board{new char[x_dim * y_dim]{0}};

    return board;
}

void clean_board(char *board)
{
    // std::cout<<"test1";
    delete[] board;
    board = nullptr;
}
void print_board(char *board, std::size_t x_dim, std::size_t y_dim)
{
    std::size_t b{0};
    // std::cout<<"test";

    for (int y{0}; y < y_dim; y++)
    {
        for (int x{0}; x < x_dim; x++)
        {
            // std::cout<<board[b]+'0';
            if ((board[b] & marked_mask()) == marked_mask())
            {
                std::cout << 'M';
            }
            else if ((board[b] & hidden_mask()) == hidden_mask())
            {
                std::cout << "*";
            }
            else
            {
                int test{board[b]};
                int mask{value_mask()};
                int display{test & mask};
                std::cout << display;
            }
            b++;
        }
        std::cout << std::endl;
    }
}
void hide_board(char *board, std::size_t x_dim, std::size_t y_dim)
{
    for (int index{0}; index < (x_dim * y_dim); index++)
    {
        board[index] = board[index] | hidden_mask();
    }
}
int mark(char *board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc,
         std::size_t y_loc)
{
    int b{0};
    for (int y{0}; y < y_dim; y++)
    {
        for (int x{0}; x < x_dim; x++)
        {
            if ((x == x_loc) && (y == y_loc))
            {
                if ((board[b] & hidden_mask()) == 0)
                {
                    return 2;
                }
                else
                {
                    board[b] = board[b] ^ marked_mask();
                }
            }
            b++;
        }
    }
    return 0;
}
void compute_neighbours(char *board, std::size_t x_dim, std::size_t y_dim)
{
    int b{0};
    for (int y{0}; y < y_dim; y++)
    {
        for (int x{0}; x < x_dim; x++)
        {
            if ((board[b] & value_mask()) != 9)
            {
                int next{0};
                if ((x - 1) >= 0)
                {
                    if ((board[b - 1] & value_mask()) == 9)
                    {
                        next++;
                    }
                }
                if (((x + 1) < x_dim))
                {
                    if ((board[b + 1] & value_mask()) == 9)
                    {
                        next++;
                    }
                }
                if (((y + 1) < y_dim)&&isnt_marked(board,b + x_dim))
                {
                    if ((board[b + x_dim] & value_mask()) == 9)
                    {
                        next++;
                    }
                }
                if (((y - 1) >= 0)&&isnt_marked(board,b - x_dim))
                {
                    if ((board[b - x_dim] & value_mask()) == 9)
                    {
                        next++;
                    }
                }
                if (((x - 1 >= 0) && (y - 1 >= 0))&&isnt_marked(board,b - x_dim - 1))
                {
                    if ((board[b - x_dim - 1] & value_mask()) == 9)
                    {
                        next++;
                    }
                }
                if (((x + 1 < x_dim) && (y - 1 >= 0))&&isnt_marked(board,b - x_dim + 1))
                {
                    if ((board[b - x_dim + 1] & value_mask()) == 9)
                    {
                        next++;
                    }
                }
                if (((x - 1 >= 0) && (y + 1 < y_dim))&&isnt_marked(board,b + x_dim - 1))
                {
                    if ((board[b + x_dim - 1] & value_mask()) == 9)
                    {
                        next++;
                    }
                }
                if (((x + 1 < x_dim) && (y + 1 < y_dim))&&isnt_marked(board,b + x_dim + 1))
                {
                    if ((board[b + x_dim + 1] & value_mask()) == 9)
                    {
                        next++;
                    }
                }
                board[b] = next;
            }
            b++;
        }
    }
}
bool is_game_won(char *board, std::size_t x_dim, std::size_t y_dim)
{
    int b{};
    int c{};
    for (int y{0}; y < y_dim; y++)
    {
        for (int x{0}; x < x_dim; x++)
        {
            if ((board[b] & value_mask()) != 9)
            {
                if ((board[b] & hidden_mask()) == 0)
                {
                    c++;
                }
            }
            else
            {
                c++;
            }
            b++;
        }
    }
    if(c==(x_dim*y_dim))
    {
        return true;
    }
    return false;
}
int reveal(char *board, std::size_t x_dim, std::size_t y_dim, std::size_t x_loc,std::size_t y_loc)
{
    for (int b{0};b<x_dim*y_dim;b++)
    {

        if (b==(y_loc*x_dim+x_loc))
        {
            if (((board[b] & marked_mask()) != 0))
                {
                    return 1;
                }
                else if (((board[b] & hidden_mask()) == 0)&&(board[b] & value_mask())!=0)
                {
                    return 2;
                }
                else if ((board[b] & value_mask()) == 9)
                {
                    board[b] = board[b] ^ hidden_mask();
                    return 9;
                }
                else if ((board[b] & value_mask()) != 0)
                {

                    board[b] = board[b] ^ hidden_mask();
                }
                else
                {
                    char text{board[b]};
                    for(int y{0};y<3;y++)
                    {
                        for(int x{0};x<3;x++)
                        {
                            if((x_loc+(-1+x)>=0)&&(x_loc+(-1+x)<x_dim)&&(y_loc+(-1+y)>=0)&&(x_loc+(-1+x)<x_dim))
                            {
                                if((board[(b+(-1+y)*x_dim)+(-1+x)]&marked_mask())==0)
                                {
                                    board[(b+(-1+y)*x_dim)+(-1+x)]=board[(b+(-1+y)*x_dim)+(-1+x)] & (~hidden_mask());
                                }
                            }
                        }
                    }
                    if(((text & hidden_mask()) == 0)&&(text & value_mask())==0)
                    {
                        return 2;
                    }
                }
                // else
                // {
                //     board[b] = board[b] & (~hidden_mask());
                    

                //     if (((x - 1) >= 0)&&isnt_marked(board,b-1))
                //     {

                //         board[b - 1] = board[b - 1] & (~hidden_mask());
                //     }
                //     if (((x + 1) < x_dim)&&isnt_marked(board,b + 1))
                //     {

                //         board[b + 1] = board[b + 1] & (~hidden_mask());
                //     }
                //     if ((y + 1) < y_dim)
                //     {

                //         board[b + x_dim] = board[b + x_dim] & (~hidden_mask());
                //     }
                //     if ((y - 1) >= 0)
                //     {

                //         board[b - x_dim] = board[b - x_dim] & (~hidden_mask());
                //     }
                //     if ((x - 1 >= 0) && (y - 1 >= 0))
                //     {

                //         board[b - x_dim - 1] = board[b - x_dim - 1] & (~hidden_mask());
                //     }
                //     if ((x + 1 < x_dim) && (y - 1 >= 0))
                //     {

                //         board[b - x_dim + 1] = board[b - x_dim + 1] & (~hidden_mask());
                //     }
                //     if ((x - 1 >= 0) && (y + 1 < y_dim))
                //     {

                //         board[b + x_dim - 1] = board[b + x_dim - 1] & (~hidden_mask());
                //     }
                //     if ((x + 1 < x_dim) && (y + 1 < y_dim))
                //     {

                //         board[b + x_dim + 1] = board[b + x_dim + 1] & (~hidden_mask());
                //     }
                //     std::bitset<8> p (board[b]);
                //     std::cout << p<<std::endl;
                //     return 0;
                // }
            }
            
        }
    return 0;
}