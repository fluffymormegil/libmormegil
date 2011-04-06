// libmormegil/serial.hh - serialization primitives
// 
// In jurisdictions where this file would be adjuged to contain copyrightable
// material, it is copyright 2011 Martin Read, and released to the public
// under the terms of the Creative Commons Public Domain Dedication (cc-0).

#ifndef libmormegil_serial_hh
#define libmormegil_serial_hh

#include <stdint.h>
#include <stdio.h>

#include <libmormegil/Coord.hh>

namespace libmormegil
{

    inline int serialize(FILE *fp, const int64_t *data)
    {
        unsigned char buf[8];
        for (int i = 0; i < 8; ++i)
        {
            buf[i] = data >> ((7 - i) << 3);
        }
        return fwrite(buf, 8, 1, fp);
    }

    inline int serialize(FILE *fp, const int32_t *data)
    {
        unsigned char buf[4];
        for (int i = 0; i < 4; ++i)
        {
            buf[i] = data >> ((3 - i) << 3);
        }
        return fwrite(buf, 4, 1, fp);
    }

    inline int serialize(FILE *fp, const int16_t *data)
    {
        unsigned char buf[2];
        for (int i = 0; i < 2; ++i)
        {
            buf[i] = data >> ((1 - i) << 3);
        }
        return fwrite(buf, 2, 1, fp);
    }

    inline int serialize(FILE *fp, const uint64_t *data)
    {
        unsigned char buf[8];
        for (int i = 0; i < 8; ++i)
        {
            buf[i] = data >> ((7 - i) << 3);
        }
        return fwrite(buf, 8, 1, fp);
    }

    inline int serialize(FILE *fp, const uint32_t *data)
    {
        unsigned char buf[4];
        for (int i = 0; i < 4; ++i)
        {
            buf[i] = data >> ((3 - i) << 3);
        }
        return fwrite(buf, 4, 1, fp);
    }

    inline int serialize(FILE *fp, const uint16_t *data)
    {
        unsigned char buf[2];
        for (int i = 0; i < 2; ++i)
        {
            buf[i] = data >> ((1 - i) << 3);
        }
        return fwrite(buf, 2, 1, fp);
    }

    inline int serialize(FILE *fp, Coord const *data)
    {
        int i1, i2;
        i1 = serialize(fp, &data->y);
        i2 = serialize(fp, &data->x);
        return (i1 > 0) && (i2 > 0) ? 0 : -1;
    }

    inline int serialize(FILE *fp, Coord64 const *data)
    {
        int i1, i2;
        i1 = serialize(fp, &data->y);
        i2 = serialize(fp, &data->x);
        return (i1 > 0) && (i2 > 0) ? 0 : -1;
    }

    inline int serialize(FILE *fp, Offset64 const *data)
    {
        int i1, i2;
        i1 = serialize(fp, &data->y);
        i2 = serialize(fp, &data->x);
        return (i1 > 0) && (i2 > 0) ? 0 : -1;
    }

    inline int serialize(FILE *fp, Offset const *data)
    {
        int i1, i2;
        i1 = serialize(fp, &data->y);
        i2 = serialize(fp, &data->x);
        return (i1 > 0) && (i2 > 0) ? 0 : -1;
    }

    inline int deserialize(FILE *fp, int64_t *data)
    {
        unsigned char buf[8];
        int64_t tmp;
        int r = fread(buf, 8, 1, fp);
        if (r > 0)
        {
            tmp = 0;
            for (int i = 0; i < 8; ++i)
            {
                tmp <<= 8;
                tmp |= buf[i];
            }
            *data = tmp;
        }
        return r;
    }

    inline int deserialize(FILE *fp, int32_t *data)
    {
        unsigned char buf[4];
        int32_t tmp;
        int r = fread(buf, 4, 1, fp);
        if (r > 0)
        {
            for (int i = 0; i < 4; ++i)
            {
                tmp <<= 8;
                tmp |= buf[i];
            }
            *data = tmp;
        }
        return r;
    }

    inline int deserialize(FILE *fp, int16_t *data)
    {
        unsigned char buf[2];
        int32_t tmp;
        int r = fread(buf, 2, 1, fp);
        if (r > 0)
        {
            for (int i = 0; i < 2; ++i)
            {
                tmp <<= 8;
                tmp |= buf[i];
            }
            *data = tmp;
        }
        return r;
    }

    inline int deserialize(FILE *fp, uint64_t *data)
    {
        unsigned char buf[8];
        uint64_t tmp;
        int r = fread(buf, 8, 1, fp);
        if (r > 0)
        {
            tmp = 0;
            for (int i = 0; i < 8; ++i)
            {
                tmp <<= 8;
                tmp |= buf[i];
            }
            *data = tmp;
        }
        return r;
    }

    inline int deserialize(FILE *fp, uint32_t *data)
    {
        unsigned char buf[4];
        uint32_t tmp;
        int r = fread(buf, 4, 1, fp);
        if (r > 0)
        {
            for (int i = 0; i < 4; ++i)
            {
                tmp <<= 8;
                tmp |= buf[i];
            }
            *data = tmp;
        }
        return r;
    }

    inline int deserialize(FILE *fp, uint16_t *data)
    {
        unsigned char buf[2];
        uint32_t tmp;
        int r = fread(buf, 2, 1, fp);
        if (r > 0)
        {
            for (int i = 0; i < 2; ++i)
            {
                tmp <<= 8;
                tmp |= buf[i];
            }
            *data = tmp;
        }
        return r;
    }

    inline int deserialize(FILE *fp, Coord *data)
    {
        int i1, i2;
        i1 = deserialize(fp, &data->y);
        i2 = deserialize(fp, &data->x);
        return (i1 > 0) && (i2 > 0) ? 0 : -1;
    }

    inline int deserialize(FILE *fp, Coord64 *data)
    {
        int i1, i2;
        i1 = deserialize(fp, &data->y);
        i2 = deserialize(fp, &data->x);
        return (i1 > 0) && (i2 > 0) ? 0 : -1;
    }

    inline int deserialize(FILE *fp, Offset *data)
    {
        int i1, i2;
        i1 = deserialize(fp, &data->y);
        i2 = deserialize(fp, &data->x);
        return (i1 > 0) && (i2 > 0) ? 0 : -1;
    }

    inline int deserialize(FILE *fp, Offset64 *data)
    {
        int i1, i2;
        i1 = deserialize(fp, &data->y);
        i2 = deserialize(fp, &data->x);
        return (i1 > 0) && (i2 > 0) ? 0 : -1;
    }

}

#endif

// vim:ts=8:sw=4:expandtab:fo=c
// libmormegil/serial.hh
