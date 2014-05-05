
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

#include "stdio.h"
#include "commands.h"

COMMAND commandList[256];

static const char *turnNames[] = {
  "IP45R",    // In Place 45 degree Right
  "IP45L",    // In Place 45 degree Left
  "IP90R",
  "IP90L",
  "IP135R",
  "IP135L",
  "IP180R",
  "IP180L",
  "SS90SR",
  "SS90SL",
  "SS90FR",
  "SS90FL",
  "SS180R",
  "SS180L",
  "SD45R",
  "SD45L",
  "SD135R",
  "SD135L",
  "DS45R",
  "DS45L",
  "DS135R",
  "DS135L",
  "DD90R",
  "DD90L",
  "SS90ER",
  "SS90EL"
};

static int cmdIndex = 0;

/*
 * The command list is null-terminated so it should only be necessary
 * to place a single zero at the start of the command list to clear it.
 * CMD_STOP has the value zero.
 */
void clearCommands(void) {
  cmdIndex = 0;
  commandList[0] = CMD_STOP;
}

/*
 * No error will be generated if an attempt is made to add more commands
 * than there is space for. This may not be the best behaviour but at
 * least there will be no overflow
 */
void emitCommand(COMMAND cmd) {
  if (cmdIndex >= sizeof (commandList)) {
    return; // TODO: fails silently. Think of a better solution
  }
  commandList[cmdIndex++] = cmd;
}

/*
 * Even though the command list should be terminated with a zero, the
 * listCommands function lists as many commands as there are in the list
 * (as determined by cmdIndex) so that any disparity should be visible.
 */
void listCommands(void) {
  int p = 0;
  COMMAND command;
  while ((p < cmdIndex) ) {
    command = commandList[p++];
    if (command == CMD_END) {
      printf("Finished\n");
    } else if (command == CMD_STOP) {
      printf("STOP");
    } else if (command < FWD16) {
      printf("FWD%d, ", command - FWD0);
    } else if (command < DIA31) {
      printf("DIA%d, ", command - DIA0);
    } else if (command < CMD_END) {
      printf("%s, ", turnNames[command - IP45R]);
    } else if (command >= CMD_ERROR_00) {
      printf("ERR_%02d, ", command - CMD_ERROR_00);
    } else {
      printf("UNKNOWN ERROR");
    }
  }
  printf("\n");
}

/*
 * Compares two command lists, command by command. At most n commands
 * will be compared.
 * Returns -1 if the lists match (including the terminating zeros.
 * If the lists do not match, returns the index of the first command
 * that fails the comparison.
 */
int compareCommands(COMMAND *s1, COMMAND *s2, unsigned int n) {
  int i = 0;
  while (n-- != 0) {
    if (*s1 != *s2) {
      return i;
    }
    if (*s2 == CMD_STOP) {
      return -1;
    }
    s1++;
    s2++;
    i++;
  }
  return -1;
}