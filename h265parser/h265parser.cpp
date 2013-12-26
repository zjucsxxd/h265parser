#include <string.h>
#include <QDebug>

#include "h265parser.h"
#include "gdef.h"


/////////////////////////////////////////////////////////////////
/// stataic funtions declare
///
static int ffurl_read(void *h, uint8_t *buf, int size);
static int ffurl_write(void *h, const uint8_t *buf, int size);
static int64_t ffurl_seek(void *h, int64_t pos, int whence);


/////////////////////////////////////////////////////////////////
/// funcions implement
///
H265Parser::H265Parser(const char* filename)
{
    this->m_filename = strdup(filename);
    this->m_fp = fopen(this->m_filename, "rb");
    if(this->m_fp == NULL){
        av_print("*** ERROR: Open %s FAILED !!!\n", this->m_filename);
    }else{
        av_print(" Open %s Successful.\n", this->m_filename);
    }

    ffio_init_context(&mPb,
                      (unsigned char*)malloc(BUFFER_SIZE),
                      BUFFER_SIZE,
                      0,
                      this->m_fp,
                      ffurl_read,
                      NULL,
                      ffurl_seek);
}

H265Parser::~H265Parser()
{
    SAFE_FREE(this->m_filename);
    SAFE_FCLOSE(this->m_fp);
    SAFE_FREE(mPb.buffer);
}

QList<H265NAL_t>&
H265Parser::getH265Nals()
{
    int nal_size = 0;
    int sync = 0;
    H265NAL_t nal;

    m_nals.clear();

    while(!mPb.eof_reached){
        uint8_t ch = avio_r8(&mPb);
        sync = (sync << 8) | ch;

        nal_size ++;

        if((sync & 0x00FFFFFF) == 0x01){
            if(m_nals.size()){
                m_nals.last().size = nal_size;
                nal_size = 0;
            }
            memset(&nal, 0, sizeof(H265NAL_t));
            uint16_t nal_hd = avio_rb16(&mPb);
            sync = (sync << 16) | nal_hd;

            nal.nal_type = (nal_hd >> 9) & 0x3F;
            m_nals.append(nal);
        }
    }

    m_nals.last().size = nal_size;
    nal_size = 0;

    return m_nals;
}

const char*
getNaltypeDesc(int nal_type)
{
    static const struct {
        int nal_type;
        const char* name;
        const char* desc;
    } nal_desc_table[] = {
        {0, "TRAIL_N", "Coded slice segment of a non-TSA, non-STSA trailing picture."},
        {1, "TRAIL_R", "Coded slice segment of a non-TSA, non-STSA trailing picture."},
        {19, "IDR_W_RADL", "Coded slice segment of an IDR picture"},
        {20, "IDR_N_LP", "Coded slice segment of an IDR picture"},
        {21, "CRA_NUT", "Coded slice segment of a CRA picture"},
        {32, "VPS_NUT", "Video parameter set"},
        {33, "SPS_NUT", "Sequence parameter set"},
        {34, "PPS_NUT", "Picture parameter set"},
        {35, "AUD_NUT", "Access unit delimiter"},
        {36, "EOS_NUT", "End of sequence"},
        {37, "EOB_NUT", "End of bitstream"},
        {38, "FD_NUT", "Filler data"},
        {39, "PREFIX_SEI_NUT", "Supplemental enhancement information"},
        {40, "SUFFIX_SEI_NUT", "Supplemental enhancement information"},
        {0, NULL, NULL}
    };

    const char* name = "null";
    for(int i = 0; nal_desc_table[i].desc != NULL; i++){
        if(nal_desc_table[i].nal_type == nal_type){
            name = nal_desc_table[i].name;
            break;
        }
    }
    return name;
}


static int
ffurl_read(void *h, uint8_t *buf, int size)
{
    return fread(buf, 1, size, (FILE *)h);
}

static int
ffurl_write(void *h, const uint8_t *buf, int size)
{
    return fwrite(buf, 1, size, (FILE *)h);
}

static int64_t
ffurl_seek(void *h, int64_t pos, int whence)
{
    return fseeko((FILE *)h, pos, whence);
}
