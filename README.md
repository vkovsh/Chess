# Chess

_**Step 1: Setup, Turns, and Taking Pieces**_

**Setup:**
The board is setup as shown. There should always be a white square at the closest right-hand side for both players.
Remember that the queen must be on a square that matches her color.
<img src="https://github.com/vkovsh/Chess/blob/main/chess_view.png" width="250"/>

**Turns:**
White always moves first, and players alternate turns. Players can only move one piece at a time, except when castling (explained later).

**Taking Pieces:**
Players take pieces when they encounter an opponent in their movement path. Only pawns take differently than they move (explained later).
Players cannot take or move through their own pieces.

_**Step 2: Pawn Movement**_
<img src="https://github.com/vkovsh/Chess/blob/main/icons/white_pawn.png" width="50"/>
<img src="https://github.com/vkovsh/Chess/blob/main/icons/black_pawn.png" width="50"/>

Pawns only move forward. On the first move a pawn can move one or two spaces, every subsequent move can only be one space.
Pawns move diagonally to take opponents.

**Pawn Promotion:**
If a pawn reaches the opposite side of the board, it is promoted to a higher piece (except king).
There is no limit to how many pawns can be promoted.

_**Step 3: Rook**_
<img src="https://github.com/vkovsh/Chess/blob/main/icons/white_rook.png" width="50"/>
<img src="https://github.com/vkovsh/Chess/blob/main/icons/black_rook.png" width="50"/>

Rooks move in a continuous line forwards, backwards and side-to-side.

_**Step 4: Knight**_
<img src="https://github.com/vkovsh/Chess/blob/main/icons/white_knight.png" width="50"/>
<img src="https://github.com/vkovsh/Chess/blob/main/icons/black_knight.png" width="50"/>

Knights are the only pieces that "jump" off the board. Unlike other pieces they are not blocked if there are pieces between them and their destination square.
To make it easier to remember how a knight moves think of an L. Two spaces in a direction forward, backward or side-to-side, and one space at a right turn.

_**Step 5: Bishop**_
<img src="https://github.com/vkovsh/Chess/blob/main/icons/white_bishop.png" width="50"/>
<img src="https://github.com/vkovsh/Chess/blob/main/icons/black_bishop.png" width="50"/>

Bishops move in continuous diagonal lines in any direction.

_**Step 6: Queen**_
<img src="https://github.com/vkovsh/Chess/blob/main/icons/white_queen.png" width="50"/>
<img src="https://github.com/vkovsh/Chess/blob/main/icons/black_queen.png" width="50"/>

The queen moves in continuous diagonal and straight lines. Forward, backward and side-to-side.

_**Step 7: King**_
<img src="https://github.com/vkovsh/Chess/blob/main/icons/white_king.png" width="50"/>
<img src="https://github.com/vkovsh/Chess/blob/main/icons/black_king.png" width="50"/>

The king can move in any direction, one square at a time. A king cannot move to a square that is under attack by the opponent.

_**Step 8: Special Move: Castling**_
Castling is the only move that allows two pieces to move during the same turn.

During castling a king moves two spaces towards the rook that it will castle with, and the rook jumps to the other side. The king can castle to either side as long as:

1. The king has not moved.
2. The king is not in check.
3. The king does not move through or into check.
4. There are no pieces between the king and castling-side rook.
5. The castling-side rook has not moved.

It does not matter:

A. If the king was in check, but is no longer.
B. If the rook can be attacked by an opponent's piece before castling.

_**Step 9: Special Move: En Passant**_
En passant is a special movement for pawns attacking pawns. It only applies if your opponent moves a pawn two spaces, and its destination space is next to your pawn.
You can take the opposing piece by moving forward-diagonal to your pawn's attacked square.

_**Step 10: Check**_
A king is in check when an opponent's piece is in a position that can attack the king. A player must move their king out of check,
block the check or capture the attacking piece. A player cannot move their king into check.

_**Step 11: Checkmate**_
Putting an opponent's king in _**"checkmate"**_ is the only way to win the game.
A king is in checkmate if it is in check, the opponent's piece that has the king in check cannot be captured, the check cannot be blocked,
and the king cannot move to a square that is not under attack.

_**Step 12: Stalemate**_
Simply put, a _**"stalemate"**_ is a tie. It is achieved if there are no legal moves for a player to make.

_qmake ../src/Chess.pro && make -j4 && make clean && rm Makefile && ./chess_

| Piece Name | White | Black |
| --- | --- | --- |
| King | K | k |
| Queen | Q | q |
| Rook | R | r |
| Bishop | B | b |
| Knight | N | n |
| Pawn | P | p |