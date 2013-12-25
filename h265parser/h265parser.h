#ifndef H265PARSER_H
#define H265PARSER_H

#include <stdio.h>
#include <QList>

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

private:
    char *m_filename;
    FILE* m_fp;
    QList<H265NAL_t> m_nals;
};

#endif // H265PARSER_H
