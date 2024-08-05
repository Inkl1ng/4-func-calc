#include "display.h"

#include <raylib.h>

static bool check_button_click(const struct button *btn)
{
	return CheckCollisionPointRec(GetMousePosition(), btn->rect)
		&& IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

static bool check_button_key(const struct button *btn)
{
	bool shift_pressed = IsKeyDown(KEY_LEFT_SHIFT)
		|| IsKeyDown(KEY_RIGHT_SHIFT);
	
	switch (btn->function) {
	case ZERO:
	case ONE:
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
		return IsKeyPressed(KEY_ZERO + btn->function)
			|| IsKeyPressed(KEY_KP_0 + btn->function);
        case DOT:
                return IsKeyPressed(KEY_PERIOD)
                        || IsKeyPressed(KEY_KP_DECIMAL);
	case ADD:
		return (shift_pressed && IsKeyPressed(KEY_EQUAL))
			|| IsKeyPressed(KEY_KP_EQUAL);	
	case SUB:
		return IsKeyPressed(KEY_MINUS)
			|| IsKeyPressed(KEY_KP_SUBTRACT);
	case DIV:
		return IsKeyPressed(KEY_SLASH)
			|| IsKeyPressed(KEY_KP_DIVIDE);
	case MULT:
		return (shift_pressed && IsKeyPressed(KEY_EIGHT))
			|| IsKeyPressed(KEY_KP_MULTIPLY);
	case EVAL:
		return IsKeyPressed(KEY_ENTER)
			|| IsKeyPressed(KEY_KP_EQUAL);
	case CLEAR:
		return IsKeyPressed(KEY_ESCAPE);
	}

	return false;
}

static void draw_button(const struct button *btn)
{
        Color clr = BLUE;
        // change the color of the button a bit if the cursor hovers over it
        if (CheckCollisionPointRec(GetMousePosition(), btn->rect)) {
                clr.r *= 0.9;
                clr.g *= 0.9;
                clr.b *= 0.9;
        }
	DrawRectangleRec(btn->rect, clr);

	char symbol[2];
	switch (btn->function) {
	case ZERO:
		symbol[0] = '0';
		break;
	case ONE:
		symbol[0] = '1';
		break;
	case TWO:
		symbol[0] = '2';
		break;
	case THREE:
		symbol[0] = '3';
		break;
	case FOUR:
		symbol[0] = '4';
		break;
	case FIVE:
		symbol[0] = '5';
		break;
	case SIX:
		symbol[0] = '6';
		break;
	case SEVEN:
		symbol[0] = '7';
		break;
	case EIGHT:
		symbol[0] = '8';
		break;
	case NINE:
		symbol[0] = '9';
		break;
        case DOT:
                symbol[0] = '.';
                break;
	case ADD:
		symbol[0] = '+';
		break;
	case SUB:
		symbol[0] = '-';
		break;
	case DIV:
		symbol[0] = '/';
		break;
	case MULT:
		symbol[0] = '*';
		break;
	case EVAL:
		symbol[0] = '=';
		break;
        case CLEAR:
                symbol[0] = 'C';
                break;
        case DEL:
                symbol[0] = 'X';
                break;
	}

	symbol[1] = '\0';
	// center symbol text in the button
	Vector2 size = MeasureTextEx(GetFontDefault(), symbol, TEXT_SIZE,
		TEXT_SIZE / 10.0);
	int x = btn->rect.x + ((btn->rect.width - size.x) / 2);
	int y = btn->rect.y + ((btn->rect.height - size.y) / 2);

	DrawText(symbol, x, y, TEXT_SIZE, WHITE);
}

void draw_buttons(const struct button *btn)
{
	for (int i = 0; i < NUM_FUNCTIONS; ++i) {
		draw_button(&btn[i]);
	}
}

bool check_button(const struct button *btn)
{
	return check_button_click(btn) || check_button_key(btn);
}

void draw_expression(enum disp_state state,
                     struct value   *v1,
                     struct value   *v2,
                     struct value   *result,
                     char           *op)
{
        char *text;
        switch (state) {
		case VAL_1:
			text = v1->digits;
			break;
		case VAL_2:
			text = v2->digits;
			break;
		case RESULT:
			text = result->digits;
			break;
		default: // case OP
			text = op;
			break;
        }

	Vector2 size = MeasureTextEx(GetFontDefault(), text, TEXT_SIZE,
		TEXT_SIZE / 10.0);
        int x = GetScreenWidth() - 5 - (int)size.x;
        DrawText(text, x, SPACING, TEXT_SIZE, WHITE);
}
