#ifndef H265PARSER_H
#define H265PARSER_H

#include <stdio.h>
#include <QList>

extern "C"{
#include "avio.h"
#include "utils.h"
}

typedef struct _H265NAL_t{
    int nal_type;
    int size;
}H265NAL_t;


class H265Parser
{
public:
    H265Parser(const char* filename);
    virtual ~H265Parser();

    QList<H265NAL_t>& getH265Nals();

    static const int BUFFER_SIZE = 0x100000;

private:
    char *m_filename;
    FILE* m_fp;
    QList<H265NAL_t> m_nals;

    AVIOContext mPb;
};


const char* getNaltypeDesc(int nal_type);

#endif // H265PARSER_H
