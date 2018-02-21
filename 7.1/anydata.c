#include <stdio.h>
#include <string.h>
#include "anydata.h"


/* 01_anydata (a)
 * Return a new AnyData object based on the given input
 */
AnyData setDouble(double value)
{
    AnyData new;
    new.type = DOUBLE;
    new.value.dval = value;
    return new;
}

AnyData setInt(int value)
{
    AnyData new;
    new.type = INT;
    new.value.ival = value;
    return new;
}

AnyData setString(char* value)
{
    AnyData new;
    new.type = STRING;
    strcpy(new.value.sval, value);
    return new;
}


void printDouble(double val)
{
    printf("D:%lf", val);
}

void printInt(int val)
{
    printf("I:%d", val);
}

void printString(char* val)
{
    printf("S:%s", val);
}

/* 01_anydata (b)
 * Print the given AnyData value, using one of the above functions
 */
void printValue(AnyData val)
{
    switch(val.type) {
    case DOUBLE:
        printDouble(val.value.dval);
        break;
    case INT:
        printInt(val.value.ival);
        break;
    case STRING:
        printString(val.value.sval);
        break;
    case UNDEF:
        break;
    }
}

