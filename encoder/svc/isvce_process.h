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
*  isvce_process.h
*
* @brief
*  Contains functions for codec thread
*
* @author
*  ittiam
*
* @remarks
*  None
*
*******************************************************************************
*/

#ifndef _ISVCE_PROCESS_H_
#define _ISVCE_PROCESS_H_

/*****************************************************************************/
/* Function Declarations                                                     */
/*****************************************************************************/

/**
******************************************************************************
*
*  @brief This function generates sps, pps set on request
*
*  @par   Description
*  When the encoder is set in header generation mode, the following function
*  is called. This generates sps and pps headers and returns the control back
*  to caller.
*
*  @param[in]    ps_codec
*  pointer to codec context
*
*  @return      success or failure error code
*
******************************************************************************
*/
IH264E_ERROR_T isvce_generate_sps_pps(isvce_codec_t *ps_codec, isvce_inp_buf_t *ps_inp_buf);

/**
*******************************************************************************
*
* @brief   initialize entropy context.
*
* @par Description:
*  Before invoking the call to perform to entropy coding the entropy context
*  associated with the job needs to be initialized. This involves the start
*  mb address, end mb address, slice index and the pointer to location at
*  which the mb residue info and mb header info are packed.
*
* @param[in] ps_proc
*  Pointer to the current process context
*
* @returns error status
*
* @remarks none
*
*******************************************************************************
*/
IH264E_ERROR_T isvce_init_entropy_ctxt(isvce_process_ctxt_t *ps_proc);

/**
*******************************************************************************
*
* @brief entry point for entropy coding
*
* @par Description
*  This function calls lower level functions to perform entropy coding for a
*  group (n rows) of mb's. After encoding 1 row of mb's,  the function takes
*  back the control, updates the ctxt and calls lower level functions again.
*  This process is repeated till all the rows or group of mb's (which ever is
*  minimum) are coded
*
* @param[in] ps_proc
*  process context
*
* @returns  error status
*
* @remarks
* NOTE : It is assumed that this routine is invoked at the start of a slice,
* so the slice header is generated by default.
*
*******************************************************************************
*/
IH264E_ERROR_T isvce_entropy(isvce_process_ctxt_t *ps_proc);

/**
*******************************************************************************
*
* @brief Packs header information of a mb in to a buffer
*
* @par Description:
*  After the deciding the mode info of a macroblock, the syntax elements
*  associated with the mb are packed and stored. The entropy thread unpacks
*  this buffer and generates the end bit stream.
*
* @param[in] ps_proc
*  Pointer to the current process context
*
* @returns error status
*
* @remarks none
*
*******************************************************************************
*/
IH264E_ERROR_T isvce_pack_header_data(isvce_process_ctxt_t *ps_proc);

/**
*******************************************************************************
*
* @brief   update process context after encoding an mb. This involves preserving
* the current mb information for later use, initialize the proc ctxt elements to
* encode next mb.
*
* @par Description:
*  This function performs house keeping tasks after encoding an mb.
*  After encoding an mb, various elements of the process context needs to be
*  updated to encode the next mb. For instance, the source, recon and reference
*  pointers, mb indices have to be adjusted to the next mb. The slice index of
*  the current mb needs to be updated. If mb qp modulation is enabled, then if
*  the qp changes the quant param structure needs to be updated. Also to
*encoding the next mb, the current mb info is used as part of mode prediction or
*mv prediction. Hence the current mb info has to preserved at top/top left/left
*  locations.
*
* @param[in] ps_proc
*  Pointer to the current process context
*
* @returns none
*
* @remarks none
*
*******************************************************************************
*/
WORD32 isvce_update_proc_ctxt(isvce_process_ctxt_t *ps_proc);

/**
*******************************************************************************
*
* @brief   initialize process context.
*
* @par Description:
*  Before dispatching the current job to process thread, the process context
*  associated with the job is initialized. Usually every job aims to encode one
*  row of mb's. Basing on the row indices provided by the job, the process
*  context's buffer ptrs, slice indices and other elements that are necessary
*  during core-coding are initialized.
*
* @param[in] ps_proc
*  Pointer to the current process context
*
* @returns error status
*
* @remarks none
*
*******************************************************************************
*/
IH264E_ERROR_T isvce_init_proc_ctxt(isvce_process_ctxt_t *ps_proc);

/**
*******************************************************************************
*
* @brief This function performs luma & chroma padding
*
* @par Description:
*
* @param[in] ps_proc
*  Process context corresponding to the job
*
* @param[in] pu1_curr_pic_luma
*  Pointer to luma buffer
*
* @param[in] pu1_curr_pic_chroma
*  Pointer to chroma buffer
*
* @param[in] i4_mb_x
*  mb index x
*
* @param[in] i4_mb_y
*  mb index y
*
* @param[in] i4_pad_ht
*  number of rows to be padded
*
* @returns  error status
*
* @remarks none
*
*******************************************************************************
*/
IH264E_ERROR_T isvce_pad_recon_buffer(isvce_process_ctxt_t *ps_proc, UWORD8 *pu1_curr_pic_luma,
                                      WORD32 i4_luma_stride, UWORD8 *pu1_curr_pic_chroma,
                                      WORD32 i4_chroma_stride, WORD32 i4_mb_x, WORD32 i4_mb_y,
                                      WORD32 i4_pad_ht);

/**
*******************************************************************************
*
* @brief This function performs luma half pel planes generation
*
* @par Description:
*
* @param[in] ps_proc
*  Process context corresponding to the job
*
* @returns  error status
*
* @remarks none
*
*******************************************************************************
*/
IH264E_ERROR_T isvce_halfpel_generation(isvce_process_ctxt_t *ps_proc, UWORD8 *pu1_curr_pic_luma,
                                        WORD32 i4_mb_x, WORD32 i4_mb_y);

/**
*******************************************************************************
*
* @brief This function performs luma & chroma core coding for a set of mb's.
*
* @par Description:
*  The mb to be coded is taken and is evaluated over a predefined set of modes
*  (intra (i16, i4, i8)/inter (mv, skip)) for best cost. The mode with least
*cost is selected and using intra/inter prediction filters, prediction is
*carried out. The deviation between src and pred signal constitutes error
*signal. This error signal is transformed (hierarchical transform if necessary)
*and quantized. The quantized residue is packed in to entropy buffer for entropy
*coding. This is repeated for all the mb's enlisted under the job.
*
* @param[in] ps_proc
*  Process context corresponding to the job
*
* @returns  error status
*
* @remarks none
*
*******************************************************************************
*/
WORD32 isvce_process(isvce_process_ctxt_t *ps_proc);

/**
*******************************************************************************
*
* @brief
*  entry point of a spawned encoder thread
*
* @par Description:
*  The encoder thread dequeues a proc/entropy job from the encoder queue and
*  calls necessary routines.
*
* @param[in] pv_proc
*  Process context corresponding to the thread
*
* @returns  error status
*
* @remarks
*
*******************************************************************************
*/
WORD32 isvce_process_thread(void *pv_proc);

#endif
