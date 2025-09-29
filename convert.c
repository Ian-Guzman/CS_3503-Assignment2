#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>


void oct_to_bin(const char *oct, char *out)
{
    int pos = 0;
    // for empty input
    if (oct == NULL || *oct == '\0')
    {
        strcpy(out, "ERROR_EMPTY_INPUT");
        return;
    }

    for (int i = 0; oct[i] != '\0'; i++)
    {
        char c = oct[i];
        // Validation: must be 0-7
        if (!isdigit((unsigned char)c) || c < '0' || c > '7')
        {
            strcpy(out, "ERROR_INVALID_OCTAL");
            return;
        }
        
        int digit = c - '0';
        out[pos++] = (digit & 4) ? '1' : '0';
        out[pos++] = (digit & 2) ? '1' : '0';
        out[pos++] = (digit & 1) ? '1' : '0';
    }
    out[pos] = '\0';
}

void oct_to_hex(const char *oct, char *out) 
{
    // for empty input
    if (oct == NULL || *oct == '\0') 
    {
        strcpy(out, "ERROR_EMPTY_INPUT");
        return;
    }
    //converting octal -> binary string
    char bin[256];
    int pos = 0;
    for (int i = 0; oct[i] != '\0'; i++) 
    {
        char c = oct[i];
        //validate octal digit
        if (!isdigit((unsigned char)c) || c < '0' || c > '7') 
        {
            strcpy(out, "ERROR_INVALID_OCTAL");
            return;
        }

        int digit = c - '0';
        bin[pos++] = (digit & 4) ? '1' : '0';
        bin[pos++] = (digit & 2) ? '1' : '0';
        bin[pos++] = (digit & 1) ? '1' : '0';
    }
    bin[pos] = '\0';

    int len = strlen(bin);
    int pad = (4 - (len % 4)) % 4;
    char padded[260];
    for (int i = 0; i < pad; i++) 
    {
        padded[i] = '0';
    }
    strcpy(padded + pad, bin);

    // convert binary to -> hex
    int outpos = 0;
    for (int i = 0; i < strlen(padded); i += 4) {
        int nibble = (padded[i] - '0') * 8 +
                     (padded[i+1] - '0') * 4 +
                     (padded[i+2] - '0') * 2 +
                     (padded[i+3] - '0') * 1;
        if (nibble < 10) {
            out[outpos++] = '0' + nibble;
        } else {
            out[outpos++] = 'A' + (nibble - 10);
        }
    }
    out[outpos] = '\0';

    //strip leading 0's unless the number is '0'
    int start = 0;
    while (out[start] == '0' && out[start+1] != '\0') 
    {
        start++;
    }
    if (start > 0) 
    {
        memmove(out, out + start, strlen(out + start) + 1);
    }
}

void hex_to_bin(const char *hex, char *out) 
{
    if (hex == NULL || *hex == '\0') {
        strcpy(out, "ERROR_EMPTY_INPUT");
        return;
    }

    int pos = 0;
    for (int i = 0; hex[i] != '\0'; i++) 
    {
        char c = hex[i];
        int digit;

        //Validation: must be 0-9, A-F, or a-f
        if (isdigit((unsigned char)c)) {
            digit = c - '0';
        } else if (c >= 'A' && c <= 'F') {
            digit = 10 + (c - 'A');
        } else if (c >= 'a' && c <= 'f') {
            digit = 10 + (c - 'a');
        } 
        else 
        {
            strcpy(out, "ERROR_INVALID_HEX");
            return;
        }

        // Each hex digit -> 4 binary bits
        out[pos++] = (digit & 8) ? '1' : '0';
        out[pos++] = (digit & 4) ? '1' : '0';
        out[pos++] = (digit & 2) ? '1' : '0';
        out[pos++] = (digit & 1) ? '1' : '0';
    }
    out[pos] = '\0';
}

// Function that converts 32-bit unasigned value to 32- bit string.
// Used for the final 3 functions
void uint32_to_bin(uint32_t value, char *out)
{
    for (int i =31; i >= 0; i--)
    {
        out[31 - i] = (value & (1u << i)) ? '1' : '0';
    }
    out[32] = '\0';
}

void to_sign_magnitude(int32_t n, char *out) 
{
    uint32_t magnitude;
    if (n >= 0)
    {
        // If positive convert like normal
        uint32_to_bin((uint32_t)n, out);
    }
    else
    {
        // If negative set most significant bit to 1, rest = magnitude
        uint32_t magnitude = (uint32_t)(-n);
        char temp[33];
        uint32_to_bin(magnitude, temp);
        // copy and force sign bit to 1
        strcpy(out, temp);
        out[0] = '1';
    }
}

void to_ones_complement(int32_t n, char *out) 
{
    if (n >= 0)
    {
        uint32_to_bin((uint32_t)n, out);
    }
    else
    {
        // For negative numbers: Flip all bits of the magnitude
        uint32_t magnitude = (uint32_t)(-n);
        u_int32_t ones = ~magnitude;//one's compliment
        uint32_to_bin(ones, out);
    }
}

void to_twos_complement(int32_t n, char *out) 
{
    if (n >= 0)
    {
        uint32_to_bin((uint32_t)n, out);
    }
    else
    {
        // For negative numbers: one's compliment +1
        uint32_t magnitude = (uint32_t)(-n);
        uint32_t twos = (~magnitude) + 1; // flip bits, add 1
        uint32_to_bin(twos, out);
    }
}

