/******************************************************************************
 *
 * Copyright (C) 2022 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at:
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 *****************************************************************************
 * Originally developed and contributed by Ittiam Systems Pvt. Ltd, Bangalore
 */
/**
*******************************************************************************
* @file
*  isvce_globals.c
*
* @brief
*  Contains definitions of global variables used across the encoder
*
* @author
*  ittiam
*
* @par List of functions
*
*
* @remarks
*
*******************************************************************************
*/

/*****************************************************************************/
/* File Includes                                                             */
/*****************************************************************************/

#include "ih264_typedefs.h"
#include "ih264_defs.h"

/* Raster to z scan map */
const UWORD8 gau1_raster_to_zscan_map[MAX_TU_IN_MB] = {0, 1, 4,  5,  2,  3,  6,  7,
                                                       8, 9, 12, 13, 10, 11, 14, 15};
