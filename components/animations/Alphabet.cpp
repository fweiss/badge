#include "Alphabet.h"

Alphabet::Alphabet() : IndexedColorAnimation(2000) {
    IndexedColorAnimation::setFrameCount(pixelIndexes);
}

void Alphabet::drawFrame(Frame &frame) {
    IndexedColorAnimation::drawFrame(frame, colorMap, pixelIndexes);
}

std::map<Alphabet::ColorIndex, uint32_t> Alphabet::colorMap{
    {back, 0x000000},
    {fore, 0xFFFFFF},
};

Alphabet::ColorIndex Alphabet::pixelIndexes[52][64] = {
//        A

        {back,back,back,fore,back,back,back,back,back,back,fore,back,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,fore,fore,fore,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,back,back,back,back,back,back},

//        B

        {back,fore,fore,fore,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,fore,fore,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,fore,fore,fore,back,back,back,back,back,back,back,back,back,back,back},

//        C

        {back,back,fore,fore,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,fore,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,back,back,back,back,back},

//        D

        {back,fore,fore,fore,back,back,back,back,back,fore,back,back,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,fore,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,back,back,back,back,back,back},


//        E

        {back,fore,fore,fore,fore,fore,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,fore,fore,fore,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,fore,fore,fore,fore,back,back,back,back,back,back,back,back,back,back},

//        F

        {back,fore,fore,fore,fore,fore,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,fore,fore,fore,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,back,back,back,back,back,back,back},

//        G

        {back,back,fore,fore,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,fore,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,back,back,back,back,back},

//        H

        {back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,fore,fore,fore,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,back,back,back,back,back,back},

//        I

        {back,back,fore,fore,fore,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,back,back,back,back,back},

//        J

        {back,back,fore,fore,fore,fore,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,fore,back,back,fore,back,back,back,back,back,fore,fore,back,back,back,back,back,back,back,back,back,back,back,back},

//        K

        {back,fore,back,back,back,fore,back,back,back,fore,back,back,fore,back,back,back,back,fore,back,fore,back,back,back,back,back,fore,fore,back,back,back,back,back,back,fore,back,fore,back,back,back,back,back,fore,back,back,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,back,back,back,back,back,back,back},

//        L

        {back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,fore,fore,fore,back,back,back,back,back,back,back,back,back,back,back},

//        M

        {back,fore,back,back,back,fore,back,back,back,fore,fore,back,fore,fore,back,back,back,fore,back,fore,back,fore,back,back,back,fore,back,fore,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,back,back,back,back,back,back},

//        N

        {back,fore,back,back,back,fore,back,back,back,fore,fore,back,back,fore,back,back,back,fore,fore,fore,back,fore,back,back,back,fore,back,fore,back,fore,back,back,back,fore,back,fore,fore,fore,back,back,back,fore,back,back,fore,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,back,back,back,back,back,back},

//        O

        {back,back,fore,fore,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,back,back,back,back,back},

//        P

        {back,fore,fore,fore,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,fore,fore,fore,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,back,back,back,back,back,back,back},

//        Q

        {back,back,fore,fore,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,fore,back,fore,back,back,back,fore,back,fore,back,fore,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,back,back,back,back,back},

//        R

        {back,fore,fore,fore,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,fore,fore,fore,back,back,back,back,fore,back,fore,back,back,back,back,back,fore,back,back,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,back,back,back,back,back,back,back},

//        S

        {back,back,fore,fore,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,back,back,back,back,back},

//        T

        {back,fore,fore,fore,fore,fore,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,back,back,back,back,back},

//        U

        {back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,back,back,back,back,back},

//        V

        {back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,fore,back,fore,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,back,back,back,back,back},

//        W

        {back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,fore,back,fore,back,back,back,fore,back,fore,back,fore,back,back,back,fore,fore,back,fore,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,back,back,back,back,back,back},

//        X

        {back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,fore,back,fore,back,back,back,back,back,back,fore,back,back,back,back,back,back,fore,back,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,back,back,back,back,back,back},

//        Y

        {back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,fore,back,fore,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,back,back,back,back,back},

//        Z

        {back,fore,fore,fore,fore,back,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,fore,back,back,back,back,back,back,fore,back,back,back,back,back,back,fore,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,back,fore,fore,fore,fore,back,back,back,back,back,back,back,back,back,back},


//        a

        {back,back,back,back,back,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,back,back,fore,back,back,back,back,back,fore,fore,fore,back,back,back,back,fore,back,back,fore,back,back,back,back,fore,back,back,fore,back,back,back,back,back,fore,fore,back,fore,back,back,back,back,back,back,back,back,back,back},

//        b

        {back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,fore,fore,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,fore,fore,fore,back,back,back,back,back,back,back,back,back,back,back},

//        c

        {back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,fore,fore,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,fore,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,back,back,back,back,back},

//        d

        {back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,fore,fore,back,fore,back,back,back,fore,back,back,fore,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,fore,fore,back,back,back,back,fore,fore,back,fore,back,back,back,back,back,back,back,back,back,back},


//        e

        {back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,fore,fore,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,fore,fore,fore,back,back,back,back,fore,back,back,back,back,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,back,back,back,back,back},

//        f

        {back,back,back,fore,fore,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,back,back,back,back,back,back},

//        g

        {back,back,back,back,back,back,back,back,back,back,back,fore,fore,back,back,back,back,back,fore,back,back,fore,back,back,back,back,fore,back,back,fore,back,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,back,fore,back,back,back,back,fore,back,back,fore,back,back,back,back,back,fore,fore,back,back,back},

//        h

        {back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,fore,fore,back,back,back,back,back,fore,back,back,fore,back,back,back,back,fore,back,back,fore,back,back,back,back,fore,back,back,fore,back,back,back,back,back,back,back,back,back,back},

//        i

        {back,back,back,back,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,back,back,back,back,back},

//        j

        {back,back,back,back,back,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,fore,back,back,fore,back,back,back,back,fore,back,back,fore,back,back,back,back,back,fore,fore,back,back,back,back},

//        k

        {back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,fore,back,back,back,back,fore,back,fore,back,back,back,back,back,fore,fore,back,back,back,back,back,back,fore,back,fore,back,back,back,back,back,fore,back,back,fore,back,back,back,back,back,back,back,back,back,back},

//        l

        {back,back,fore,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,back,back,back,back,back},

//        m

        {back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,fore,back,fore,back,back,back,back,fore,back,fore,back,fore,back,back,back,fore,back,fore,back,fore,back,back,back,fore,back,fore,back,fore,back,back,back,back,back,back,back,back,back,back},

//        n

        {back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,fore,fore,back,back,back,back,back,fore,back,back,fore,back,back,back,back,fore,back,back,fore,back,back,back,back,fore,back,back,fore,back,back,back,back,back,back,back,back,back,back},

//        o

        {back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,fore,fore,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,back,back,back,back,back},

//        p

        {back,back,back,back,back,back,back,back,back,fore,back,fore,fore,back,back,back,back,fore,fore,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,fore,back,back,fore,back,back,back,fore,back,fore,fore,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back},

//        q

        {back,back,back,back,back,back,back,back,back,back,fore,fore,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,fore,fore,fore,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back},

//        r

        {back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,fore,back,fore,fore,back,back,back,back,fore,fore,back,back,fore,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,back,back,back,back,back,back,back},

//        s

        {back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,fore,fore,fore,back,back,back,back,fore,back,back,back,back,back,back,back,back,fore,fore,back,back,back,back,back,back,back,back,fore,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,back,back,back,back,back},

//        t

        {back,back,back,back,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,fore,fore,fore,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,fore,back,fore,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,back,back,back,back},

//        u

        {back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,fore,fore,back,back,back,back,fore,fore,back,fore,back,back,back,back,back,back,back,back,back,back},

//        v

        {back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,fore,back,fore,back,back,back,back,back,back,fore,back,back,back,back,back,back,back,back,back,back,back,back},

//        w

        {back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,fore,back,fore,back,back,back,fore,fore,back,fore,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,back,back,back,back,back,back},

//        x

        {back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,fore,back,back,back,fore,back,back,back,back,fore,back,fore,back,back,back,back,back,back,fore,back,back,back,back,back,back,fore,back,fore,back,back,back,back,fore,back,back,back,fore,back,back,back,back,back,back,back,back,back,back},

//        y

        {back,back,back,back,back,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,fore,fore,fore,fore,back,back,back,back,back,back,back,fore,back,back,back,fore,back,back,back,fore,back,back,back,back,fore,fore,fore,back,back,back},

//        z

        {back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,back,fore,fore,fore,fore,fore,back,back,back,back,back,back,fore,back,back,back,back,back,back,fore,back,back,back,back,back,back,fore,back,back,back,back,back,back,fore,fore,fore,fore,fore,back,back,back,back,back,back,back,back,back,back},
};
