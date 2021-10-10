//
//  vector.h
//  Blasteroids
//
//  Created by Marcelo Camargo on 11/22/18.
//  Copyright © 2018 Marcelo Camargo. All rights reserved.
//

#ifndef vector_h
#define vector_h

#include <stdio.h>

typedef struct Vector2D Vector2D;
struct Vector2D
{
    float angle;        /* direction */
    float dx, dy;       /* incremental change in y for an incremental change in x */
    float magnitude;    /* magnitude: speed or aceleration */
};

#endif /* vector_h */
