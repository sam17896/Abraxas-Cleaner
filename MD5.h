#ifndef MD5_H
#define MD5_H
#include "md5Header.h"
#include "Header.h"
typedef unsigned char md5_byte_t; 
typedef unsigned int md5_word_t;
typedef struct md5_state_s {
    md5_word_t count[2];
	md5_word_t abcd[4];		
    md5_byte_t buf[64];	
} 	md5_state_t;
class MD5
{
	public:
		void md5_process(md5_state_t *pms, const md5_byte_t *data);
		void md5_init(md5_state_t *pms);
		void md5_finish(md5_state_t *pms, md5_byte_t digest[16]);
		void md5_append(md5_state_t *pms, const md5_byte_t *data, int nbytes);		
};
#endif
