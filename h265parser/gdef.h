#ifndef GDEF_H
#define GDEF_H

/*
 * gdef.h
 *
 *  Created on: Apr 2, 2013
 *      Author: szhu
 */

#ifndef GDEF_H_
#define GDEF_H_

#ifdef DEBUqDebug
#undef DEBUqDebug
#endif
#define DEBUqDebug 0

#ifndef MMIN
#define MMIN(a,b) ((a)>(b)?(b):(a))
#endif

#ifndef MMAX
#define MMAX(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef MMID
#define MMID(a,m,b) (MMIN(MMAX(a,m),b))
#endif

#ifndef SAFE_FREE
#define SAFE_FREE(x) \
        do{\
            if((x) != NULL){\
                if(DEBUqDebug) qDebug("SAFE_FREE " #x "\n");\
                free((x));\
                (x) = NULL;\
            }\
        }while(0)
#endif

#ifndef SAFE_CLOSE
#define SAFE_CLOSE(x) \
        do{\
            if((x) != -1){\
                if(DEBUqDebug) qDebug("SAFE_CLOSE " #x "\n");\
                close((x));\
                (x) = -1;\
            }\
        }while(0)
#endif

#ifndef SAFE_FCLOSE
#define SAFE_FCLOSE(x) \
        do{\
            if(DEBUqDebug) qDebug("SAFE_FCLOSE " #x "\n");\
            if((x) != NULL){\
                fclose((x));\
                (x) = NULL;\
            }\
        }while(0)
#endif

#ifndef SAFE_GQUEUE_FREE
#define SAFE_GQUEUE_FREE(x) \
    do{\
    if((x)){\
        if(DEBUqDebug) qDebug("SAFE_GQUEUE_FREE "#x "[%p]\n", (x));\
        g_queue_free((x));\
        (x) = NULL;\
    }}while(0)
#endif

#ifndef SAFE_GMUTEX_FREE
#define SAFE_GMUTEX_FREE(x) \
    do{\
    if((x)){\
        if(DEBUqDebug) qDebug("SAFE_GMUTEX_FREE " #x "[%p]\n", (x));\
        g_mutex_free((x));\
        (x) = NULL;\
    }}while(0)
#endif

#ifndef SAFE_GCOND_FREE
#define SAFE_GCOND_FREE(x) \
    do{\
    if((x)){\
        if(DEBUqDebug) qDebug("SAFE_GCOND_FREE " #x "[%p]\n", (x));\
        g_cond_free((x));\
        (x) = NULL;\
    }}while(0)
#endif






//#ifndef av_printf
//#define av_printf(...) \
//    do{\
//        printf("[%s::%s::%d]" __VA_ARGS__, __FILE__, __func__, __LINE__);\
//    }while(0)
//#endif

#ifndef av_print
#define av_print(fmt, ...) \
    do{\
        qDebug("[%s::%s::%d]" fmt, __FILE__, __func__, __LINE__, ##__VA_ARGS__);\
    }while(0)
#endif

#ifndef av_printl
#define av_printl(fmt, ...) \
    do{\
        qDebug("[%s::%s::%d]" fmt"\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__);\
    }while(0)
#endif

#ifndef av_gst_info
#define av_gst_info(obj, fmt, ...) \
    do{\
        GST_INFO_OBJECT(obj, "[%s::%s::%d]" fmt, __FILE__, __func__, __LINE__, __VA_ARGS__);\
    }while(0)
#endif

#ifndef av_gst_warning
#define av_gst_warning(obj, fmt, ...) \
    do{\
        GST_WARNING_OBJECT(obj, "[%s::%s::%d]" fmt, __FILE__, __func__, __LINE__, __VA_ARGS__);\
    }while(0)
#endif

#endif /* GDEF_H_ */


#endif // GDEF_H
