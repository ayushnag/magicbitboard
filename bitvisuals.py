# import attacksets

white = 0xffff
black = 0xffff000000000000
sample_knight = 0x508800885000
sample_white_pawn = 0x5000000000000


def grid(n: int):
    print("\n+---+---+---+---+---+---+---+---+")
    for i in reversed(range(8)):
        rank = n >> (i * 8) & 0xff
        for j in range(8):
            print('| X ' if (rank >> j & 0x1) else '|   ', end='')
        print("|\n+---+---+---+---+---+---+---+---+")

grid(sample_white_pawn)