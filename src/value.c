#include "value.h"

#include <stdio.h>

void add_digit(struct value *val, char c)
{
	if (val->num_digits == MAX_DIGITS) {
		return;
	} else {
		val->digits[val->num_digits] = c;
		++val->num_digits;
		val->digits[val->num_digits] = '\0';
	}
}

void reset_value(struct value *val)
{
        if (val->num_digits == 0) {
                return;
        } else {
		val->digits[0] = '\0';
		val->num_digits = 0;
	}
}

void delete_digit(struct value *val)
{
        if (val->num_digits == 0) {
                return;
        }

        val->digits[val->num_digits - 1] = '\0';
        --val->num_digits;
}

void set_value(struct value *val, double d)
{
        snprintf(val->digits, MAX_DIGITS + 1, "%f", d);

	val->num_digits = 0;
	while (val->digits[val->num_digits] != '\0') {
		++val->num_digits;
	}
	
        // remove trailing 0's
        while (val->digits[val->num_digits - 1] == '0') {
                val->digits[val->num_digits - 1] = '\0';
                --val->num_digits;
        }

        // remove the dot if necessary
        if (val->digits[val->num_digits - 1] == '.') {
                val->digits[val->num_digits - 1] = '\0';
                --val->num_digits;
        }
}

void negate(struct value *val)
{
	val->digits[0] = '-';
        val->digits[1] = '\0';
	val->num_digits = 1;
}
