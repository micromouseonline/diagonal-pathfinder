/*
Copyright (c) 2014 Peter Harrison

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 */

#include "commands.h"

/*
 * Generate a command sequence from a string input. The generated path will
 * allow a micromouse to move diagonally in the maze.
 * The input string is a null-terminated array of characters.
 *
 * Passing in an empty string will generate an error.
 *
 * Only characters from the set FLRS are accepted. Other characters
 * in the input array will cause an error command to be emitted.
 *
 * The output is performed by the function emitCommand() which adds a single
 * command to the command list. Modify emitCommand() to do something else
 * with the generated results.
 *
 * If there is an error during conversion, the output command list will
 * still contain valid output up to the point where the error is detected.
 *
 * A single pass is taken through the input string and commands are
 * generated as soon as there is an unambiguous state for the command.
 *
 * The input string will typically be generated form the maze solver data
 * and each valid character in that string has the following meaning:
 *   F : move forward one cell orthogonally
 *   R : perform an in-place right turn of 90 degrees
 *   L : perform an in-place left turn of 90 degrees
 *   S : Stop moving in this cell. This is the goal.
 *
 * Refer to the associated state chart for a view of how the states are
 * related to each other.
 *
 * NOTE that the output command list will be limited in size. The function
 * will continue to generate output values as long as there is valid input.
 * It knows nothing about the size of available output.
 *
 * The states have simple numbers rather than an enum since I could not
 * think of good names to use. Since then, I have but this version
 * maintains compatibility with the MINOS 2014 slides. Possible names are
 * shown as a comment for each state.
 */

typedef enum {
  PathStart,
  PathOrtho_F,
  PathOrtho_R,
  PathOrtho_L,
  PathOrtho_RR,
  PathOrtho_LL,
  PathDiag_RL,
  PathDiag_LR,
  PathDiag_RR,
  PathDiag_LL,
  PathStop,
  PathExit,
  PathError
} state_t;

void makeDiagonalPath(const char * s) {
  int x; // a counter for the number of cells to be crossed
  state_t state;
  char c;
  clearCommands();
  state = PathStart;
  x = 0;
  while (state != PathExit) {
    c = *s++;
    switch (state) {
      case PathStart:
        if (c == 'F') {
          x = 1;
          state = PathOrtho_F;
        } else if (c == 'R') {
          emitCommand(CMD_ERROR_00);
          state = PathStop;
        } else if (c == 'L') {
          emitCommand(CMD_ERROR_00);
          state = PathStop;
        } else if (c == 'S') {
          state = PathStop;
        } else {
          emitCommand(CMD_ERROR_00);
          state = PathStop;
        }
        break;
      case PathOrtho_F:
        if (c == 'F') {
          x++;
        } else if (c == 'R') {
          emitCommand(FWD0 + x);
          state = PathOrtho_R;
        } else if (c == 'L') {
          emitCommand(FWD0 + x);
          state = PathOrtho_L;
        } else if (c == 'S') {
          emitCommand(FWD0 + x);
          state = PathStop;
        } else {
          emitCommand(CMD_ERROR_01);
          state = PathStop;
        }
        break;
      case PathOrtho_R:
        if (c == 'F') {
          emitCommand(SS90SR);
          x = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          state = PathOrtho_RR;
        } else if (c == 'L') {
          emitCommand(SD45R);
          x = 2;
          state = PathDiag_RL;
        } else if (c == 'S') {
          emitCommand(SS90ER);
          emitCommand(FWD1);
          state = PathStop;
        } else {
          emitCommand(CMD_ERROR_02);
          state = PathStop;
        }
        break;
      case PathOrtho_L:
        if (c == 'F') {
          emitCommand(SS90SL);
          x = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          emitCommand(SD45L);
          x = 2;
          state = PathDiag_LR;
        } else if (c == 'L') {
          state = PathOrtho_LL;
        } else if (c == 'S') {
          emitCommand(SS90EL);
          emitCommand(FWD1);
          state = PathStop;
        } else {
          emitCommand(CMD_ERROR_03);
          state = PathStop;
        }
        break;
      case PathOrtho_RR:
        if (c == 'F') {
          emitCommand(SS180R);
          x = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          emitCommand(CMD_ERROR_04);
          state = PathStop;
        } else if (c == 'L') {
          emitCommand(SD135R);
          x = 2;
          state = PathDiag_RL;
        } else if (c == 'S') {
          emitCommand(SS180R);
          emitCommand(FWD1);
          state = PathStop;
        } else {
          emitCommand(CMD_ERROR_04);
          state = PathStop;
        }
        break;
      case PathDiag_RL:
        if (c == 'F') {
          emitCommand(DIA0 + x);
          emitCommand(DS45L);
          x = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          x += 1;
          state = PathDiag_LR;
        } else if (c == 'L') {
          state = PathDiag_LL;
        } else if (c == 'S') {
          emitCommand(DIA0 + x);
          emitCommand(DS45L);
          emitCommand(FWD1);
          state = PathStop;
        } else {
          emitCommand(CMD_ERROR_05);
          state = PathStop;
        }
        break;
      case PathDiag_LR:
        if (c == 'F') {
          emitCommand(DIA0 + x);
          emitCommand(DS45R);
          x = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          state = PathDiag_RR;
        } else if (c == 'L') {
          x += 1;
          state = PathDiag_RL;
        } else if (c == 'S') {
          emitCommand(DIA0 + x);
          emitCommand(DS45R);
          emitCommand(FWD1);
          state = PathStop;
        } else {
          emitCommand(CMD_ERROR_06);
          state = PathStop;
        }
        break;
      case PathOrtho_LL:
        if (c == 'F') {
          emitCommand(SS180L);
          x = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          emitCommand(SD135L);
          x = 2;
          state = PathDiag_LR;
        } else if (c == 'L') {
          emitCommand(CMD_ERROR_07);
          state = PathStop;
        } else if (c == 'S') {
          emitCommand(SS180L);
          emitCommand(FWD1);
          state = PathStop;
        } else {
          emitCommand(CMD_ERROR_07);
          state = PathStop;
        }
        break;
      case PathDiag_LL:
        if (c == 'F') {
          emitCommand(DIA0 + x);
          emitCommand(DS135L);
          x = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          emitCommand(DIA0 + x);
          emitCommand(DD90L);
          x = 2;
          state = PathDiag_LR;
        } else if (c == 'L') {
          emitCommand(CMD_ERROR_08);
          state = PathStop;
        } else if (c == 'S') {
          emitCommand(DIA0 + x);
          emitCommand(DS135L);
          emitCommand(FWD1);
          state = PathStop;
        } else {
          emitCommand(CMD_ERROR_08);
          state = PathStop;
        }
        break;
      case PathDiag_RR:
        if (c == 'F') {
          emitCommand(DIA0 + x);
          emitCommand(DS135R);
          x = 2;
          state = PathOrtho_F;
        } else if (c == 'R') {
          state = 8;
        } else if (c == 'L') {
          emitCommand(DIA0 + x);
          emitCommand(DD90R);
          x = 2;
          state = PathDiag_RL;
        } else if (c == 'S') {
          emitCommand(DIA0 + x);
          emitCommand(DS135R);
          emitCommand(FWD1);
          state = PathStop;
        } else {
          emitCommand(CMD_ERROR_09);
          state = PathStop;
        }
        break;
      case PathStop:
        emitCommand(CMD_STOP); // make sure the command list gets terminated
        state = PathExit;
        break;
      default:
        emitCommand(CMD_ERROR_15);
        state = PathExit;
        break;
    }
  }
}

