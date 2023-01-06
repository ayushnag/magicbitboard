__author__ = "Ayush Nag"
from board import Board
# Plays chess game
checkmate, quit = False, False
side: int = 0 # 0 = white, 1 = black   side ^= 1 to toggle

white_start: int = 0xffff
black_start: int = 0xffff000000000000

# Lookup tables of square names in algebraic chess notation
SQSTR = [
	"a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1",
	"a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
	"a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
	"a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
	"a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
	"a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
	"a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
	"a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
	"None"
]

b = Board()

while not b.checkmate() and not quit:
    print()
    

class board:
	# all white pieces
	wking: int
	wknights: int
	wpawns: int
	wrooks: int
	wbishops: int
	wqueen: int
	# all black pieces
	bking: int
	bknights: int
	bpawns: int
	brooks: int
	bbishops: int
	bqueen: int

	def full(self):
 		# self.wking | .... | self.bqueen

# visualizes state
# runs game
# make sure to print table generation times, moves validation times (ns)
# need an easy way for 2d array <---> int 
# keep r, b, n, k, q, p
# DRAW OUT THE INPUTS AND OUTPUTS FOR ENGINE TO UNDERSTAND HOW CHESS.PY CAN VISUALIZE
# for now just work on the board logic
# it can take in a position and output the valid moves for each piece
# 1) figure out a number layout
# 2) start figuring out equation for king and knight 
# - convert position (int), piece (int), and type --> valid moveset (int)