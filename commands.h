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


#ifndef COMMANDS_H
#define	COMMANDS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

  /*
   * This is effectively the instruction set of the movement controller
   * of the mouse. Commands are held in an array and executed sequentially.
   * There is a structure to each command that makes it easy to extract
   * information like distance and direction.
   *
   * B7:5
   * 000 => Ortho straight B4:0 hold number of cells
   * 001 => Diagonal straight. B4:0 hold number of cells
   * 010 => turns
   *        B0    = direction.  0 => right, 1 => left
   *        B2:B1 = angle.      00 => 45  deg
   *                            01 => 90  deg
   *                            10 => 135 deg
   *                            11 => 180 deg
   *        B5:B3 = turn type   00 => in-place
   *
   * 1xx => error
   *
   *
   */
typedef uint8_t COMMAND;

#define CMD_STOP       (0x00)
#define CMD_STRAIGHT   (0x00)
#define CMD_DIAGONAL   (0x20)
#define CMD_SQUARES    (0x1F)
#define CMD_TURN       (0x40)
#define CMD_INTEGRATED (0x60)
#define CMD_RIGHT      (0x00)
#define CMD_LEFT       (0x01)
#define CMD_END        (0x7F)
#define CMD_ERROR_00   (0xF0)
#define CMD_ERROR_01   (0xF1)
#define CMD_ERROR_02   (0xF2)
#define CMD_ERROR_03   (0xF3)
#define CMD_ERROR_04   (0xF4)
#define CMD_ERROR_05   (0xF5)
#define CMD_ERROR_06   (0xF6)
#define CMD_ERROR_07   (0xF7)
#define CMD_ERROR_08   (0xF8)
#define CMD_ERROR_09   (0xF9)
#define CMD_ERROR_10   (0xFA)
#define CMD_ERROR_11   (0xFB)
#define CMD_ERROR_12   (0xFC)
#define CMD_ERROR_13   (0xFD)
#define CMD_ERROR_14   (0xFE)
#define CMD_ERROR_15   (0xFF)


#define FWD0    (CMD_STRAIGHT+ 0)   //00
#define FWD1    (CMD_STRAIGHT+ 1)   //01
#define FWD2    (CMD_STRAIGHT+ 2)   //02
#define FWD3    (CMD_STRAIGHT+ 3)   //03
#define FWD4    (CMD_STRAIGHT+ 4)   //04
#define FWD5    (CMD_STRAIGHT+ 5)   //05
#define FWD6    (CMD_STRAIGHT+ 6)   //06
#define FWD7    (CMD_STRAIGHT+ 7)   //07
#define FWD8    (CMD_STRAIGHT+ 8)   //08
#define FWD9    (CMD_STRAIGHT+ 9)   //09
#define FWD10   (CMD_STRAIGHT+ 10)  //10
#define FWD11   (CMD_STRAIGHT+ 11)  //11
#define FWD12   (CMD_STRAIGHT+ 12)  //12
#define FWD13   (CMD_STRAIGHT+ 13)  //13
#define FWD14   (CMD_STRAIGHT+ 14)  //14
#define FWD15   (CMD_STRAIGHT+ 15)  //15
#define FWD16   (CMD_STRAIGHT+ 16)  //17

#define DIA0    (CMD_DIAGONAL +  0) //32
#define DIA1    (CMD_DIAGONAL +  1) //33
#define DIA2    (CMD_DIAGONAL +  2) //34
#define DIA3    (CMD_DIAGONAL +  3) //35
#define DIA4    (CMD_DIAGONAL +  4) //36
#define DIA5    (CMD_DIAGONAL +  5) //37
#define DIA6    (CMD_DIAGONAL +  6) //38
#define DIA7    (CMD_DIAGONAL +  7) //39
#define DIA8    (CMD_DIAGONAL +  8) //40
#define DIA9    (CMD_DIAGONAL +  9) //41
#define DIA10   (CMD_DIAGONAL + 10) //42
#define DIA11   (CMD_DIAGONAL + 11) //43
#define DIA12   (CMD_DIAGONAL + 12) //44
#define DIA13   (CMD_DIAGONAL + 13) //45
#define DIA14   (CMD_DIAGONAL + 14) //46
#define DIA15   (CMD_DIAGONAL + 15) //47
#define DIA16   (CMD_DIAGONAL + 16) //48
#define DIA17   (CMD_DIAGONAL + 17) //49
#define DIA18   (CMD_DIAGONAL + 18) //50
#define DIA19   (CMD_DIAGONAL + 19) //51
#define DIA20   (CMD_DIAGONAL + 20) //52
#define DIA21   (CMD_DIAGONAL + 21) //53
#define DIA22   (CMD_DIAGONAL + 22) //54
#define DIA23   (CMD_DIAGONAL + 23) //55
#define DIA24   (CMD_DIAGONAL + 24) //56
#define DIA25   (CMD_DIAGONAL + 25) //57
#define DIA26   (CMD_DIAGONAL + 26) //58
#define DIA27   (CMD_DIAGONAL + 27) //59
#define DIA28   (CMD_DIAGONAL + 28) //60
#define DIA29   (CMD_DIAGONAL + 29) //61
#define DIA30   (CMD_DIAGONAL + 30) //62
#define DIA31   (CMD_DIAGONAL + 31) //63


#define IP45R   (CMD_TURN +  0)     //64
#define IP45L   (CMD_TURN +  1)     //65
#define IP90R   (CMD_TURN +  2)     //66
#define IP90L   (CMD_TURN +  3)     //67
#define IP135R  (CMD_TURN +  4)     //68
#define IP135L  (CMD_TURN +  5)     //69
#define IP180R  (CMD_TURN +  6)     //70
#define IP180L  (CMD_TURN +  7)     //71

#define SS90SR  (CMD_TURN +  8)     //72
#define SS90SL  (CMD_TURN +  9)     //73
#define SS90FR  (CMD_TURN + 10)     //74
#define SS90FL  (CMD_TURN + 11)     //75
#define SS180R  (CMD_TURN + 12)     //76
#define SS180L  (CMD_TURN + 13)     //77
#define SD45R   (CMD_TURN + 14)     //78
#define SD45L   (CMD_TURN + 15)     //79
#define SD135R  (CMD_TURN + 16)     //80
#define SD135L  (CMD_TURN + 17)     //81
#define DS45R   (CMD_TURN + 18)     //82
#define DS45L   (CMD_TURN + 19)     //83
#define DS135R  (CMD_TURN + 20)     //84
#define DS135L  (CMD_TURN + 21)     //85
#define DD90R   (CMD_TURN + 22)     //86
#define DD90L   (CMD_TURN + 23)     //87
#define SS90ER  (CMD_TURN + 24)     //88
#define SS90EL  (CMD_TURN + 25)     //89



  extern COMMAND commandList[];

  void listCommands (void);
  void clearCommands (void);
  void emitCommand (COMMAND cmd);
  int compareCommands(COMMAND *s1, COMMAND *s2, unsigned int n) ;

#ifdef	__cplusplus
}
#endif

#endif	/* COMMANDS_H */

