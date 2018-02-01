#include <vector>
#include <stdlib.h>
#include <time.h>
#include <iostream>

class square {
  public:
    bool naked;
    bool bomb;
    int adj;
    int i;
    int j;
    square(int, int, int, bool, bool);
};

square::square(int a,int b, int adj_ = 0, bool bomb_ = false, bool naked_ = false) {
  i = a;
  j = b;
  adj = adj_;
  bomb = bomb_;
  naked = naked_;
}

class minesweeper {
  private:
    std::vector<std::vector<square> > board;
    int row;
    int col;
    int bombs;
  public:
    void breadth_first_search(square);
    bool in_bounds(int, int);
    void print(bool);
    void get_adj(int, int);
    int guess(int, int);
    int if_neg(int, int);
    std::vector<square> get_children(square);
    void create_board(int row_, int col_, int bombs_);
};

void minesweeper::breadth_first_search(square root) {
  std::vector<square> Q;
  Q.push_back(root);
  while(!Q.empty()) {
    std::vector<std::vector<square> > new_Q;
    for (int i = 0; i < Q.size(); i++) {
      square q = Q.back();
      Q.pop_back();
      std::vector<square> children = get_children(q); 
    }
  }
}

std::vector<square> minesweeper::get_children(square q) {
  std::vector<square> children;
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if (i != 0 or j != 0) {
        if (in_bounds(i, j)) {
          if (board[i][j].naked and board[i][j].adj == 0) {
            children.push_back(board[i][j]);
          }
          board[i][j].naked = false;
        }
      }
    }
  }
  return children;
}

bool minesweeper::in_bounds(int i, int j) {
  if (i > -1 and i < row and j > -1 and j < col) {
    return true;
  }
  else {
    return false;
  }
}

void minesweeper::create_board(int row_, int col_, int bombs_) {
  row = row_;
  col = col_;
  bombs = bombs_;
  for (int i = 0; i < row; i++) {
    std::vector<square> vec;
    for (int j = 0; j < col; j++) {
      square a(i, j); 
      vec.push_back(a);
    }
    board.push_back(vec);   
  }
  int counter = bombs;
  while(counter) {
    int i = rand() % row;
    int j = rand() % row;
    if (!board[i][j].bomb) {
      board[i][j].bomb = true;
      counter = counter - 1;
    }
  }
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      get_adj(i, j);
    }
  } 
}

void minesweeper::print(bool debugger = false) {
  if (debugger) {
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        int result;
        if (board[i][j].bomb) {
          result = -1;
        }
        else {
          result = board[i][j].adj;
        }
        std::cout << "[" << result << "]";
      }
      std::cout << std::endl;
    }
  }
  return ;
}

void minesweeper::get_adj(int x, int y) {
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {
      if (x or y) {
        board[x][y].adj += if_neg(x+i, y+j);
      }
    }
  }   
}

int minesweeper::if_neg(int i, int j) {
  if (i > -1 and i < row and j > -1 and j < col) {
    return (board[i][j].bomb == true ? 1: 0); 
  }
  else {
    return 0;
  }
}

int minesweeper::guess(int i, int j) {
  if (board[i][j].bomb) {
    return(1);
  }
  else if (board[i][j].naked) {
    board[i][j].naked = true;
    square root = board[i][j];
    breadth_first_search(root);
  }
  return(0);
}

int main() {
  srand(time(0));
  minesweeper game;
  game.create_board(5, 5, 2);
  int guess = game.guess(1, 1);
  std::cout << guess << std::endl;
  game.print(true);
  return 0;
}
