#ifndef DISPLAY_H 
#define DISPLAY_H

#include <stdbool.h>
#include <raylib.h>
#include "value.h"

#define BTN_WIDTH  80
#define BTN_HEIGHT 50
#define TEXT_SIZE  40
#define SPACING    1

enum button_function {
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE,

	DOT,
	ADD,
	SUB,
	DIV,
	MULT,
	EVAL,

	CLEAR,
	DEL,

	NUM_FUNCTIONS
};

enum disp_state {
        VAL_1,
        VAL_2,
        RESULT,
        OP
};

struct button {
	Rectangle rect;
	int function;
};

void draw_buttons(const struct button btn[]);

bool check_button(const struct button *btn);

void draw_expression(enum disp_state state,
                     struct value   *v1,
                     struct value   *v2,
                     struct value   *result,
                     char           *op);

#endif
