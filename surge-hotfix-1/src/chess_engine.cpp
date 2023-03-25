#include <iostream>
#include <chrono>
#include "tables.h"
#include "position.h"
#include "types.h"
#include "magic_enum.hpp"

// Computes the perft of the position for a given depth, using bulk-counting
// According to the https://www.chessprogramming.org/Perft site:
// Perft is a debugging function to walk the move generation tree of strictly legal moves to count
// all the leaf nodes of a certain depth, which can be compared to predetermined values and used to isolate bugs
template <Color Us>
unsigned long long perft(Position &p, unsigned int depth)
{
  // gk int nmoves;
  unsigned long long nodes = 0;

  MoveList<Us> list(p);

  if (depth == 1)
    return (unsigned long long)list.size();

  for (Move move : list)
  {
    p.play<Us>(move);
    nodes += perft<~Us>(p, depth - 1);
    p.undo<Us>(move);
  }

  return nodes;
}

// A variant of perft, listing all moves and for each move, the perft of the decremented depth
// It is used solely for debugging
template <Color Us>
void perftdiv(Position &p, unsigned int depth)
{
  unsigned long long nodes = 0, pf;

  MoveList<Us> list(p);

  for (Move move : list)
  {
    std::cout << move;

    p.play<Us>(move);
    pf = perft<~Us>(p, depth - 1);
    std::cout << ": " << pf << " moves\n";
    nodes += pf;
    p.undo<Us>(move);
  }

  std::cout << "\nTotal: " << nodes << " moves\n";
}

void test_perft()
{
  Position p;
  Position::set("rnbqkbnr/pppppppp/8/8/8/8/PPPP1PPP/RNBQKBNR w KQkq -", p);
  std::cout << p;

  std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
  auto n = perft<WHITE>(p, 6);
  std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
  auto diff = end - begin;

  std::cout << "Nodes: " << n << "\n";
  std::cout << "NPS: "
            << int(n * 1000000.0 / std::chrono::duration_cast<std::chrono::microseconds>(diff).count())
            << "\n";
  std::cout << "Time difference = "
            << std::chrono::duration_cast<std::chrono::microseconds>(diff).count() << " [microseconds]\n";
}

template <Color color>
Move get_valid_move(Position &p)
{
  MoveList<color> list(p);
  for (Move move : list)
  {
    std::cout << move << " ";
  }
  std::cout << std::endl;
  std::string user_move_str;
  while (true)
  {
    std::cout << "Enter move: ";
    std::cin >> user_move_str;

    if (user_move_str == "exit")
      return Move();
    if (user_move_str.length() != 4)
    {
      std::cout << "Incorrect move format!" << std::endl;
      continue;
    }

    auto from = (Square)magic_enum::enum_cast<Square>(user_move_str.substr(0, 2)).value();
    auto to = (Square)magic_enum::enum_cast<Square>(user_move_str.substr(2, 4)).value();
    Move user_move = Move(from, to);

    for (Move move : list)
    {
      if (move.to() == user_move.to() && move.from() == user_move.from())
      {
        return move;
      }
    }
    std::cout << "Invalid move!\n";
  }
}

void play_game()
{
  Position p;
  Color color = WHITE;
  Position::set("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq -", p);
  std::cout << p;

  std::string user_move;
  while (true)
  {
    std::cout << p;
    std::cout << "Color to move: " << (color == WHITE ? "WHITE" : "BLACK") << std::endl;

    Move valid_move = (color == WHITE ? get_valid_move<WHITE>(p) : get_valid_move<BLACK>(p));
    if (valid_move == Move())
      break;

    color == WHITE ? p.play<WHITE>(valid_move) : p.play<BLACK>(valid_move);
    color = ~color;
  }
}

int main()
{
  // Make sure to initialise all databases before using the library!
  initialise_all_databases();
  zobrist::initialise_zobrist_keys();

  // test_perft();

  play_game();

  return EXIT_SUCCESS;
}