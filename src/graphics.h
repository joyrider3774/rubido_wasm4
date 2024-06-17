#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>

#define imgmiddleWidth 80
#define imgmiddleHeight 80
#define imgmiddleFlags BLIT_2BPP

#define imganywhereWidth 80
#define imganywhereHeight 80
#define imganywhereFlags BLIT_2BPP

#define imghorzvertdiagWidth 80
#define imghorzvertdiagHeight 80
#define imghorzvertdiagFlags BLIT_2BPP

#define imghorzvertWidth 80
#define imghorzvertHeight 80
#define imghorzvertFlags BLIT_2BPP

#define options1Width 64
#define options1Height 14
#define options1Flags BLIT_1BPP

#define veryhard1Width 144
#define veryhard1Height 13
#define veryhard1Flags BLIT_1BPP

#define veryeasy1Width 144
#define veryeasy1Height 13
#define veryeasy1Flags BLIT_1BPP

#define rubidoWidth 120
#define rubidoHeight 26
#define rubidoFlags BLIT_1BPP

#define willemssoftWidth 144
#define willemssoftHeight 10
#define willemssoftFlags BLIT_1BPP

#define creditstextWidth 152
#define creditstextHeight 106
#define creditstextFlags BLIT_1BPP

#define pegsWidth 112
#define pegsHeight 16
#define pegsFlags BLIT_2BPP

#define middleWidth 32
#define middleHeight 6
#define middleFlags BLIT_1BPP

#define movementWidth 64
#define movementHeight 8
#define movementFlags BLIT_1BPP

#define newgame1Width 88
#define newgame1Height 11
#define newgame1Flags BLIT_1BPP

#define diagonalWidth 40
#define diagonalHeight 8
#define diagonalFlags BLIT_1BPP

#define anywhereWidth 40
#define anywhereHeight 8
#define anywhereFlags BLIT_1BPP

#define endpositionWidth 80
#define endpositionHeight 8
#define endpositionFlags BLIT_1BPP

#define horzvertWidth 72
#define horzvertHeight 7
#define horzvertFlags BLIT_1BPP

#define leftrightWidth 136
#define leftrightHeight 8
#define leftrightFlags BLIT_1BPP

#define hard1Width 104
#define hard1Height 13
#define hard1Flags BLIT_1BPP

#define easy1Width 104
#define easy1Height 13
#define easy1Flags BLIT_1BPP

#define credits1Width 56
#define credits1Height 11
#define credits1Flags BLIT_1BPP

extern const uint8_t imgmiddle[];
extern const uint8_t imganywhere[];
extern const uint8_t imghorzvertdiag[];
extern const uint8_t imghorzvert[];
extern const uint8_t options1[];
extern const uint8_t veryhard1[];
extern const uint8_t veryeasy1[];
extern const uint8_t rubido[];
extern const uint8_t willemssoft[];
extern const uint8_t creditstext[];
extern const uint8_t pegs[];
extern const uint8_t middle[];
extern const uint8_t movement[];
extern const uint8_t newgame1[];
extern const uint8_t diagonal[];
extern const uint8_t anywhere[];
extern const uint8_t endposition[];
extern const uint8_t horzvert[];
extern const uint8_t leftright[];
extern const uint8_t hard1[];
extern const uint8_t easy1[];
extern const uint8_t credits1[];

#endif