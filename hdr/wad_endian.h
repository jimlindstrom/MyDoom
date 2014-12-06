#ifndef __WAD_ENDIAN_H
#define __WAD_ENDIAN_H

#define LITTLE_ENDIAN32_TO_BIG_ENDIAN32(num) ( ((num & 0x000000ff) << 24u) | \
                                               ((num & 0x0000ff00) <<  8u) | \
                                               ((num & 0x00ff0000) >>  8u) | \
                                               ((num & 0xff000000) >> 24u) ) 


#ifdef __BIG_ENDIAN__

#define LITTLE_ENDIAN32_TO_LOCAL_ENDIAN32(num) LITTLE_ENDIAN32_TO_BIG_ENDIAN32(num)

#else

#define LITTLE_ENDIAN32_TO_LOCAL_ENDIAN32(num) (num)

#endif

#endif // #ifndef __WAD_ENDIAN_H
