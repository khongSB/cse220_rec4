New! Keyboard shortcuts … 
Drive keyboard shortcuts have been updated to give you first-letters navigation

#include <stdio.h>

unsigned short DOS_REPR_Of(unsigned char year, unsigned char month, unsigned char day)
{
    // Note: no input validation is done to enforce these limits
    // The range for n bits is [0, (2^n)-1]
    // bits [15-9] represents year; can represent a max of 127 years
    // bits [8-5] represents month; can represents a max of 15 months
    // bits [0-4] represents day; can represent a max of 31 days

    unsigned short result = 0;

    result |= year << 9;
    result |= month << 5;
    result |= day;

    return result;
}

unsigned char DOS_Year(unsigned short repr)
{
    // 11111100...0
    return (repr & 0xFC00) >> 9;
}

unsigned char DOS_Month(unsigned short repr)
{
    // 0...111100000
    return (repr & 0x1E0) >> 5;
}

unsigned char DOS_Day(unsigned short repr)
{
    // 0...11111
    return repr & 0x1F;
}

unsigned char DOS_Str_Year(const unsigned char *repr)
{
    // We need first 7 bits
    // 11111100...0

    // repr[0] is first 8 bits
    printf("%02x\n", repr[0]);

    // first hex digit
    // printf("%02x\n", repr[0] & 0xF0);
    // second hex digit
    // printf("%02x\n", repr[0] & 0x0F);

    // shift 1 here because 2^0 starts at the 1th bit of the first 8 bits
    return (repr[0] & 0xFE) >> 1;
}

unsigned char DOS_Str_Month(const unsigned char *repr)
{
    // 0...111100000

    // bits [8-5] overlaps repr[0] and repr[1]

    // from repr[0]
    // 00000001
    // from repr[1]
    // 11100000

    // Visualizing the shifting
    // ((repr[0] & 0x1) << 3)
    // 00001000

    unsigned char part1 = ((repr[0] & 0x1) << 3);

    // ((repr[1] & 0xE0) >> 5)
    // 00000111

    unsigned char part2 = ((repr[1] & 0xE0) >> 5);

    // OR
    // 00001000 | 00000111
    // 00001111

    return part1 | part2;
}

unsigned char DOS_Str_Day(const unsigned char *repr)
{
    // 0...11111
    return repr[1] & 0x1F;
}

int main()
{
    printf("%04x\n", DOS_REPR_Of(127, 15, 31));
    // short
    // printf("%d\n", DOS_Year(DOS_REPR_Of(100, 2, 5)));
    // printf("%d\n", DOS_Month(DOS_REPR_Of(100, 2, 5)));
    // printf("%d\n", DOS_Day(DOS_REPR_Of(100, 2, 5)));

    // string
    printf("Year from STR: %d\n", DOS_Str_Year("\xff\xff"));
    printf("Month from STR: %d\n", DOS_Str_Month("\xff\xff"));
    printf("Day from STR: %d\n", DOS_Str_Day("\xff\xff"));

    return 0;
}
