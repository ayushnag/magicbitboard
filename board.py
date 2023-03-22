__author__ = "Ayush Nag"
# Keeps track of the chess board data

class Board:   
    WHITE: int = 0
    BLACK: int = 1

    # moves available to each piece
    # (0, 'k') is white king, (1, 'r') is black rook, etc.
    moves: dict = {}

    def move(self, color: int, fro: int, to: int):
        # moves piece
        raise NotImplementedError

    def validate(self, color: int, square: int) -> tuple:
        return self.moves[(color, square)]

    def checkmate(self) -> bool:
        # returns if the current state is in checkmate
        # avail(color, king_square) is empty
        raise NotImplementedError


# what should the board be able to do
# b.checkmate()
# b.current_player
# b.current_player_moves - {p: }
# b = Board(fen)
# 

# chessboard.js for JS element
# show live hover moves
# next to that the bitboard masks applied to get that moveset
# (queen) would show rook and bishop bitboard and



# need something that keeps track of the location and piece type
# needs to be two valued thing
# for pieces in board:
    # switch case based on type of thing
    # first get all possible moves for each piece
    # does attacksets take care of if the king is in check?
    