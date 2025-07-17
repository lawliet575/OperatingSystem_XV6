#ifndef SHA_H
#define SHA_H

// Define unsigned types used in SHA-256
typedef unsigned char uchar;


// SHA-256 context structure
typedef struct {
    uchar data[64];
    uint datalen;
    uint bitlen[2];
    uint state[8];
} SHA256_CTX;


// Function prototypes for SHA-256 operations
void SHA256Init(SHA256_CTX *ctx);
void SHA256Update(SHA256_CTX *ctx, uchar data[], uint len);
void SHA256Final(SHA256_CTX *ctx, uchar hash[]);
void SHA256Transform(SHA256_CTX *ctx, uchar data[]);

// Utility functions
void toHex(char byteValue, char hexString[3]);
void convertToUCharArray(const char *str, uchar *ucharArray);
char* myStrcat(char* dest, const char* src);
char* SHA256(char *data);


#endif // SHA_H

