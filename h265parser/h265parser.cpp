#include <string.h>
#include <QDebug>

#include "h265parser.h"
#include "gdef.h"

H265Parser::H265Parser(const char* filename)
{
    this->m_filename = strdup(filename);
    this->m_fp = fopen(this->m_filename, "rb");
    if(this->m_fp == NULL){
        av_print("*** ERROR: Open %s FAILED !!!\n", this->m_filename);
    }else{
        av_print(" Open %s Successful.\n", this->m_filename);
    }
}

H265Parser::~H265Parser()
{
    SAFE_FREE(this->m_filename);
    SAFE_FCLOSE(this->m_fp);
}

QList<H265NAL_t>&
H265Parser::getH265Nals()
{
    m_nals.clear();

    H265NAL_t nal;

    nal.nal_type = 15;
    nal.size = 100;
    m_nals.append(nal);

    nal.nal_type = 16;
    nal.size = 200;
    m_nals.append(nal);

    nal.nal_type = 17;
    nal.size = 300;
    m_nals.append(nal);

    return m_nals;
}
