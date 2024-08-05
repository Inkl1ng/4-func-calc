#include "calc.h"

#include <stdlib.h>
#include <string.h>
#include <raylib.h>
#include "display.h"
#include "value.h"

static bool handle_number_input(struct value *v, const struct button *btns)
{
        if (check_button(&btns[ZERO])) {
                add_digit(v, '0');
                return true;
        } else if (check_button(&btns[ONE])) {
                add_digit(v, '1');
                return true;
        } else if(check_button(&btns[TWO])) {
                add_digit(v, '2');
                return true;
        } else if (check_button(&btns[THREE])) {
                add_digit(v, '3');
                return true;
        } else if (check_button(&btns[FOUR])) {
                add_digit(v, '4');
                return true;
        } else if (check_button(&btns[FIVE])) {
                add_digit(v, '5');
                return true;
        } else if (check_button(&btns[SIX])) {
                add_digit(v, '6');
                return true;
        } else if (check_button(&btns[SEVEN])) {
                add_digit(v, '7');
                return true;
        } else if (check_button(&btns[EIGHT])) {
                add_digit(v, '8');
                return true;
        } else if (check_button(&btns[NINE])) {
                add_digit(v, '9');
                return true;
        } else if (check_button(&btns[DOT])) {
                add_digit(v, '.');
                return true;
        } else if (check_button(&btns[DEL])) {
                delete_digit(v);
                return true;
        }

        return false;
}

static void handle_input(
	const struct button *btns,
	enum disp_state     *state,
	struct value        *v1,
	struct value        *v2,
	struct value        *result,
	char                *op)
{
        if (check_button(&btns[CLEAR])) {
                reset_value(v1);
                reset_value(v2);
                reset_value(result);
                *state = VAL_1;
                return;
        }
 
        if (*state == VAL_2 && check_button(&btns[EVAL])) {
                double val_1 = atof(v1->digits);
                double val_2 = atof(v2->digits);
		double new_val;

                switch (op[0]) {
                case '+':
			new_val = val_1 + val_2; 
			break;
                case '-':
			new_val = val_1 - val_2; 
			break;
                case '/':
			new_val = val_1 / val_2; 
			break;
                default: // case '*'
			new_val = val_1 * val_2; 
			break;
                }

		set_value(result, new_val);
		reset_value(v1);
		reset_value(v2);
                *state = RESULT;
        } else if (*state == RESULT) {
                if (handle_number_input(v1, btns) ||
                    check_button(&btns[CLEAR])) {
                        *state = VAL_1;
                }
        } else if (*state == VAL_1) {
                handle_number_input(v1, btns);
		
		if (check_button(&btns[ADD])) {
			*state = OP;
			op[0] = '+';
		} else if (check_button(&btns[SUB]) && v1->num_digits > 0) {
			*state = OP;
			op[0] = '-';
		} else if (check_button(&btns[SUB])) {
			negate(v1);
		} else if (check_button(&btns[DIV])) {
			*state = OP;
			op[0] = '/';
		} else if (check_button(&btns[MULT])) {
			*state = OP;
			op[0] = '*';
		}
        } else if (*state == VAL_2) {
                handle_number_input(v2, btns);

		if (check_button(&btns[SUB])) {
			negate(v2);
		}
        } else if (*state == OP) {
                if (handle_number_input(v2, btns)) {
                        *state = VAL_2;
                }
        }
}

void init_calc()
{
	SetTraceLogLevel(LOG_NONE);
	InitWindow(4 * BTN_WIDTH + 5 * SPACING,
		   (6 * BTN_HEIGHT + 5 * SPACING) - 12,
		   "4 Function Calculator");
	SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
        SetExitKey(KEY_NULL);
}

void run_calc()
{
	// setup buttons
	struct button btns[NUM_FUNCTIONS];

	/*
	 * Layout
	 *
	 * [   output    ]
	 * [C] [(] [)] [x] <- delete
	 * [7] [8] [9] [+]
	 * [4] [5] [6] [-]
	 * [1] [2] [3] [*]
	 * [0] [.] [=] [/]
	 */

	btns[ZERO].rect  = (struct Rectangle){ .x = 0, .y = 5 };
	btns[ONE].rect   = (struct Rectangle){ .x = 0, .y = 4 };
	btns[TWO].rect   = (struct Rectangle){ .x = 1, .y = 4 };
	btns[THREE].rect = (struct Rectangle){ .x = 2, .y = 4 };
	btns[FOUR].rect  = (struct Rectangle){ .x = 0, .y = 3 };
	btns[FIVE].rect  = (struct Rectangle){ .x = 1, .y = 3 };
	btns[SIX].rect   = (struct Rectangle){ .x = 2, .y = 3 };
	btns[SEVEN].rect = (struct Rectangle){ .x = 0, .y = 2 };
	btns[EIGHT].rect = (struct Rectangle){ .x = 1, .y = 2 };
	btns[NINE].rect  = (struct Rectangle){ .x = 2, .y = 2 };

	btns[DOT].rect   = (struct Rectangle){ .x = 1, .y = 5 };
	btns[ADD].rect   = (struct Rectangle){ .x = 3, .y = 2 };
	btns[SUB].rect   = (struct Rectangle){ .x = 3, .y = 3 };
	btns[DIV].rect   = (struct Rectangle){ .x = 3, .y = 4 };
	btns[MULT].rect  = (struct Rectangle){ .x = 3, .y = 5 };
	btns[EVAL].rect  = (struct Rectangle){ .x = 2, .y = 5 };
	btns[CLEAR].rect = (struct Rectangle){ .x = 0, .y = 1 };
	btns[DEL].rect   = (struct Rectangle){ .x = 2, .y = 1 };


	for (int i = 0; i < NUM_FUNCTIONS; ++i) {
		btns[i].rect.x     *= BTN_WIDTH + SPACING;
		btns[i].rect.x     += 1;
		btns[i].rect.y     *= BTN_HEIGHT + SPACING;
		// get a 1 pixel gap between the eval text and buttons
		btns[i].rect.y     -= 13;
		btns[i].rect.width  = BTN_WIDTH;
		btns[i].rect.height = BTN_HEIGHT;
		btns[i].function    = i;
	}

	btns[CLEAR].rect.width = (2 * BTN_WIDTH) + 1;
	btns[DEL].rect.width   = (2 * BTN_WIDTH) + 1;

	enum disp_state state  = VAL_1;
	char op[] = { '+', '\0' };

        struct value v1, v2, result;
        v1.digits[0]      = '\0';
        v1.num_digits     = 0;
        v2.digits[0]      = '\0';
        v2.num_digits     = 0;
        result.digits[0]  = '\0';
        result.num_digits = 0;

	while (!WindowShouldClose()) {
		handle_input(btns, &state, &v1, &v2, &result, op);

		BeginDrawing();

		ClearBackground(BLACK);

		draw_buttons(btns);
			
		draw_expression(state, &v1, &v2, &result, op);

		EndDrawing();
	}
}

void close_calc()
{
	CloseWindow();
}
