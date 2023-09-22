#include "board.h"

/* Constructor
 * @param boardScene - Qt Scene to draw the board on
*/
Board::Board(QGraphicsScene *boardScene)
    : scene(boardScene)
{
    // Initialize Data
    this->width_ = scene->width();
    this->height_ = scene->height();
    factory_ = PieceFactory(width_/7, QColor(Qt::red), QColor(Qt::blue));

    // Draw yellow backdrop
    this->scene->addRect(0, height_/7, width_, height_, QPen(QColor(255,200,0)), QBrush(QColor(255,200,0)));

    // Create 2d Array for Piece Data & Draw to Board
    for (int r = 0; r < 6; r++) {
        for (int c = 0; c < 7; c++) {
            Piece *p = factory_.get_piece(get_x(c), get_y(r));
            boardData[r][c] = p;
            scene->addItem(p);
        }
    }

    scene->update();

}

// Method for resetting the board, sets all the pieces to empty.
void Board::resetBoard() {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            this->boardData[i][j]->set_type(PieceType::Empty);
        }
    }
}

// Method that returns if the target column is full or not
bool Board::can_place(int c) {
    return this->boardData[0][c]->get_type() == PieceType::Empty;
}

// Method that places a piece into column c by player p.
void Board::place_piece(int c, int p) {
    PieceType toPiece;
    if (p == 1) {
        toPiece = PieceType::P1;
    } else {
        toPiece = PieceType::P2;
    }
    for (int i = 5; i >= 0; i--) {
        if (this->boardData[i][c]->get_type() == PieceType::Empty) {
            this->boardData[i][c]->set_type(toPiece);
            return;
        }
    }
}

// Checks to see if there is a 4-in-a-row on the board
// Return 1 for P1 Win, 2 for P2 Win, -1 for no win yet
int Board::check_for_win() {
    for (int r = 5; r >= 0; r--) {
        for (int c = 0; c < 7; c++) {
            PieceType type = this->boardData[r][c]->get_type();
            // Make sure current piece is P1 or P2 (not empty piece of neutral piece)
            if (type == PieceType::P1 || type == PieceType::P2) {
                // Check for win in all directions, if any are true return the player who won
                if (this->cfw_right(r, c+1, 1, type) || this->cfw_diag_right(r-1, c+1, 1, type)
                        || this->cfw_up(r-1, c, 1, type) || this->cfw_diag_left(r-1, c-1, 1, type)) {
                    if (type == PieceType::P1) {
                        return 1;
                    } else if (type == PieceType::P2) {
                        return 2;
                    }
                }
            }
        }
    }
    return -1;
}

// Helper method to check if row, column value is in bounds of the board
bool Board::in_bounds(int r, int c) const {
    return r >= 0 && r < 6 && c >= 0 && c < 7;
}

// Powerup Methods:
void Board::place_ColumnBomb(int c) {
    for (int i = 0; i < 6; i++) {
        this->boardData[i][c]->set_type(PieceType::Empty);
    }
}

void Board::place_RowBomb(int c) {
    int trow = this->get_row_from_col(c);
    // If at top row just delete that row
    if (trow == 0) {
        for (auto p : this->boardData[trow]) {
            p->set_type(PieceType::Empty);
        }
    } else {
    // Simple solution: Move down every row above, and delete the top row.
        for (int r = trow-1; r >= 0; r--) {
            for (int c = 0; c < 7; c++) {
                PieceType n = this->boardData[r][c]->get_type();
                this->boardData[r+1][c]->set_type(n);
            }
        }
        for (auto p : this->boardData[0]) {
            p->set_type(PieceType::Empty);
        }
    }
}

void Board::place_SquareBomb(int c) {
    bool leftc = this->in_bounds(0, c-1);
    bool rightc = this->in_bounds(0, c+1);
    int trow = this->get_row_from_col(c);
    // If top row delete the expected pieces
    if (trow == 0) {
        if (leftc) {
            this->boardData[trow][c-1]->set_type(PieceType::Empty);
            this->boardData[trow+1][c-1]->set_type(PieceType::Empty);
        }
        this->boardData[trow+1][c]->set_type(PieceType::Empty);
        if (rightc) {
            this->boardData[trow][c+1]->set_type(PieceType::Empty);
            this->boardData[trow+1][c+1]->set_type(PieceType::Empty);
        }
    }
    // If second to top row just delete the expected pieces
    else if (trow == 1) {
        if (leftc) {
            this->boardData[trow+1][c-1]->set_type(PieceType::Empty);
            this->boardData[trow][c-1]->set_type(PieceType::Empty);
            this->boardData[trow-1][c-1]->set_type(PieceType::Empty);
        }
        this->boardData[trow+1][c]->set_type(PieceType::Empty);
        if (rightc) {
            this->boardData[trow+1][c+1]->set_type(PieceType::Empty);
            this->boardData[trow][c+1]->set_type(PieceType::Empty);
            this->boardData[trow-1][c+1]->set_type(PieceType::Empty);
        }
    }
    // If bottom row, move the rows above the square 2 units down
    else if (trow == 5) {
        for (int r = 3; r >= 0; r--) {
            if (leftc) {
                this->boardData[r+2][c-1]->set_type(this->boardData[r][c-1]->get_type());
            }
            this->boardData[r+2][c]->set_type(this->boardData[r][c]->get_type());
            if (rightc) {
                this->boardData[r+2][c+1]->set_type(this->boardData[r][c+1]->get_type());
            }
        }
        // Clear top 2 rows
        for (int c = 0; c < 7; c++) {
            this->boardData[0][c]->set_type(PieceType::Empty);
            this->boardData[1][c]->set_type(PieceType::Empty);
        }
    }
    // Otherwise do the same but 3 units down
    else {
        for (int r = trow-2; r >= 0; r--) {
            if (leftc) {
                this->boardData[r+3][c-1]->set_type(this->boardData[r][c-1]->get_type());
            }
            this->boardData[r+3][c]->set_type(this->boardData[r][c]->get_type());
            if (rightc) {
                this->boardData[r+3][c+1]->set_type(this->boardData[r][c+1]->get_type());
            }
        }
        // Clear top 3 rows
        for (int c = 0; c < 7; c++) {
            this->boardData[0][c]->set_type(PieceType::Empty);
            this->boardData[1][c]->set_type(PieceType::Empty);
            this->boardData[2][c]->set_type(PieceType::Empty);
        }
    }
}

// Recursive Helper Methods for Checking For Win in the 4 different directions:
// Up/Down, Left/Right, BottomLeft/TopRight, BottomRight/TopLeft
bool Board::cfw_right(int r, int c, int streak, const PieceType &t) {
    // Check in bounds
    if (!this->in_bounds(r, c)) {
        return false;
    }
    // Check if streak continues, if we hit 4 return true
    if (this->boardData[r][c]->get_type() == t) {
        streak += 1;
        if (streak == 4) {
            return true;
            qDebug() << "Left/Right win detected.";
        } else {
            return this->cfw_right(r, c+1, streak, t);
        }
    } else {
        return false;
    }
}

bool Board::cfw_diag_right(int r, int c, int streak, const PieceType &t) {
    if (!this->in_bounds(r, c)) {
        return false;
    }
    if (this->boardData[r][c]->get_type() == t) {
        streak += 1;
        if (streak == 4) {
            qDebug() << "Diagonal Right win detected.";
            return true;
        } else {
            return this->cfw_diag_right(r-1, c+1, streak, t);
        }
    } else {
        return false;
    }
}

bool Board::cfw_up(int r, int c, int streak, const PieceType &t) {
    if (!this->in_bounds(r, c)) {
        return false;
    }
    if (this->boardData[r][c]->get_type() == t) {
        streak += 1;
        if (streak == 4) {
            qDebug() << "Up/Down win detected.";
            return true;
        } else {
            return this->cfw_up(r-1, c, streak, t);
        }
    } else {
        return false;
    }
}

bool Board::cfw_diag_left(int r, int c, int streak, const PieceType &t) {
    if (!this->in_bounds(r, c)) {
        return false;
    }
    if (this->boardData[r][c]->get_type() == t) {
        streak += 1;
        if (streak == 4) {
            qDebug() << "Diagonal Left win detected.";
            return true;
        } else {
            return this->cfw_diag_left(r-1, c-1, streak, t);
        }
    } else {
        return false;
    }
}

// Private Helper Methods for converting 2d array position to pixel coordinates:
int Board::get_x(int c) const {
    return (this->width_ / 7) * c;
}

int Board::get_y(int r) const {
    int space = this->height_ / 7;
    return space + (space * r);
}

// Private helper method for getting the top row of a column
// for placing a piece:
int Board::get_row_from_col(int c) const {
    for (int r = 5; r >= 0; r--) {
        if (this->boardData[r][c]->get_type() == PieceType::Empty) {
            return r;
        }
    }
    return -1;
}
