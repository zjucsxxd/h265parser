/*
 * utils.h
 *
 *  Created on: Dec 25, 2013
 *      Author: szhu
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>

#ifndef AVERROR
#define AVERROR(x) (-(x))
#endif

#define IO_BUFFER_SIZE       32768 // 32K = 8 * 0x1000
#define SHORT_SEEK_THRESHOLD 4096
#define FF_INPUT_BUFFER_PADDING_SIZE 8

#ifndef MKTAG
#define MKTAG(a,b,c,d) ((a) | ((b) << 8) | ((c) << 16) | ((unsigned)(d) << 24))
#endif
#ifndef MKBETAG
#define MKBETAG(a,b,c,d) ((d) | ((c) << 8) | ((b) << 16) | ((unsigned)(a) << 24))
#endif

#ifndef FFERRTAG
#define FFERRTAG(a, b, c, d) (-(int)MKTAG(a, b, c, d))
#endif

#define AVERROR_BSF_NOT_FOUND      FFERRTAG(0xF8,'B','S','F') ///< Bitstream filter not found
#define AVERROR_BUG                FFERRTAG( 'B','U','G','!') ///< Internal bug, also see AVERROR_BUG2
#define AVERROR_BUFFER_TOO_SMALL   FFERRTAG( 'B','U','F','S') ///< Buffer too small
#define AVERROR_DECODER_NOT_FOUND  FFERRTAG(0xF8,'D','E','C') ///< Decoder not found
#define AVERROR_DEMUXER_NOT_FOUND  FFERRTAG(0xF8,'D','E','M') ///< Demuxer not found
#define AVERROR_ENCODER_NOT_FOUND  FFERRTAG(0xF8,'E','N','C') ///< Encoder not found
#define AVERROR_EOF                FFERRTAG( 'E','O','F',' ') ///< End of file
#define AVERROR_EXIT               FFERRTAG( 'E','X','I','T') ///< Immediate exit was requested; the called function should not be restarted
#define AVERROR_EXTERNAL           FFERRTAG( 'E','X','T',' ') ///< Generic error in an external library
#define AVERROR_FILTER_NOT_FOUND   FFERRTAG(0xF8,'F','I','L') ///< Filter not found
#define AVERROR_INVALIDDATA        FFERRTAG( 'I','N','D','A') ///< Invalid data found when processing input
#define AVERROR_MUXER_NOT_FOUND    FFERRTAG(0xF8,'M','U','X') ///< Muxer not found
#define AVERROR_OPTION_NOT_FOUND   FFERRTAG(0xF8,'O','P','T') ///< Option not found
#define AVERROR_PATCHWELCOME       FFERRTAG( 'P','A','W','E') ///< Not yet implemented in FFmpeg, patches welcome
#define AVERROR_PROTOCOL_NOT_FOUND FFERRTAG(0xF8,'P','R','O') ///< Protocol not found

#define AVERROR_STREAM_NOT_FOUND   FFERRTAG(0xF8,'S','T','R') ///< Stream not found
/**
 * This is semantically identical to AVERROR_BUG
 * it has been introduced in Libav after our AVERROR_BUG and with a modified value.
 */
#define AVERROR_BUG2               FFERRTAG( 'B','U','G',' ')
#define AVERROR_UNKNOWN            FFERRTAG( 'U','N','K','N') ///< Unknown error, typically from an external library
#define AVERROR_EXPERIMENTAL       (-0x2bb2afa8) ///< Requested feature is flagged experimental. Set strict_std_compliance if you really want to use it.


#ifndef FFMAX
#define FFMAX(a,b) ((a) > (b) ? (a) : (b))
#endif
#ifndef FFMIN
#define FFMIN(a,b) ((a) > (b) ? (b) : (a))
#endif


void av_max_alloc(size_t max);
void *av_malloc(size_t size);
void *av_realloc(void *ptr, size_t size);
int av_reallocp(void *ptr, size_t size);
void av_free(void *ptr);
void av_freep(void *arg);
void *av_mallocz(size_t size);
void *av_calloc(size_t nmemb, size_t size);
char *av_strdup(const char *s);
void *av_memdup(const void *p, size_t size);

#endif /* UTILS_H_ */
