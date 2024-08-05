#ifndef VALUE_H
#define VALUE_H

#define MAX_DIGITS 13

struct value {
        char digits[MAX_DIGITS + 1];
        int  num_digits;
};

void add_digit(struct value *val, char c);

void reset_value(struct value *val);

void delete_digit(struct value *val);

void set_value(struct value *val, double d);

void negate(struct value *val);

#endif
