class TicTacToe:
    def __init__(self):
        self.board = [[' ' for _ in range(3)] for _ in range(3)]
        self.current_player = 'X'
    
    def print_board(self):
        for row in self.board:
            print('|'.join(row))
            print('-' * 5)
    
    def is_valid_move(self, row, col):
        return self.board[row][col] == ' '
    
    def make_move(self, row, col):
        if self.is_valid_move(row, col):
            self.board[row][col] = self.current_player
            return True
        return False
    
    def check_winner(self):
        # Check rows
        for row in self.board:
            if row[0] == row[1] == row[2] != ' ':
                return row[0]
        
        # Check columns
        for col in range(3):
            if self.board[0][col] == self.board[1][col] == self.board[2][col] != ' ':
                return self.board[0][col]
        
        # Check diagonals
        if self.board[0][0] == self.board[1][1] == self.board[2][2] != ' ':
            return self.board[0][0]
        if self.board[0][2] == self.board[1][1] == self.board[2][0] != ' ':
            return self.board[0][2]
        
        return None
    
    def is_draw(self):
        for row in self.board:
            if ' ' in row:
                return False
        return True
    
    def switch_player(self):
        self.current_player = 'O' if self.current_player == 'X' else 'X'
    
    def play_game(self):
        while True:
            self.print_board()
            row = int(input(f"Player {self.current_player}, enter row (0-3): "))
            col = int(input(f"Player {self.current_player}, enter column (0-3): "))
            
            if self.make_move(row, col):
                winner = self.check_winner()
                if winner:
                    self.print_board()
                    print(f"Player {winner} wins!")
                    break
                elif self.is_draw():
                    self.print_board()
                    print("It's a draw!")
                    break
                self.switch_player()
            else:
                print("Invalid move, try again.")
