# Chess

**Step 1: Setup, Turns, and Taking Pieces**

**Setup:**
The board is setup as shown. There should always be a white square at the closest right-hand side for both players.
Remember that the queen must be on a square that matches her color.
<img src="https://github.com/vkovsh/Chess/blob/main/chess_view.png" width="250"/>

**Turns:**
White always moves first, and players alternate turns. Players can only move one piece at a time, except when castling (explained later).

**Taking Pieces:**
Players take pieces when they encounter an opponent in their movement path. Only pawns take differently than they move (explained later).
Players cannot take or move through their own pieces.

**Step 2: Pawn Movement**
<img src="https://github.com/vkovsh/Chess/blob/main/icons/white_pawn.png" width="50"/>

Pawns only move forward. On the first move a pawn can move one or two spaces, every subsequent move can only be one space.
Pawns move diagonally to take opponents.

**Pawn Promotion:**


qmake ../src/Chess.pro && make -j4 && make clean && rm Makefile && ./chess

| Piece Name | White | Black |
| --- | --- | --- |
| King | K | k |
| Queen | Q | q |
| Rook | R | r |
| Bishop | B | b |
| Knight | N | n |
| Pawn | P | p |