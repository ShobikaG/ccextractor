#ifndef HARDSUBX_H
#define HARDSUBX_H

#include "lib_ccx.h"
#include "utility.h"

#ifdef ENABLE_OCR
//TODO: Correct FFMpeg integration
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include "allheaders.h"


struct lib_hardsubx_ctx
{
	// The main context for hard subtitle extraction

	// Attributes common to the lib_ccx context
	int cc_to_stdout;
	LLONG subs_delay;
	LLONG last_displayed_subs_ms;
	char *basefilename;
	const char *extension;
	int current_file;
	char **inputfile;
	int num_input_files; 
	LLONG system_start_time;
	enum ccx_output_format write_format;

	// Media file context
	AVFormatContext *format_ctx;
	AVCodecContext *codec_ctx;
	AVCodec *codec;
	AVFrame *frame;
	AVFrame *rgb_frame;
	AVPacket packet;
	AVDictionary *options_dict;
	struct SwsContext *sws_ctx;
	uint8_t *rgb_buffer;
	int video_stream_id;

	// Leptonica Image Context
	PIX *im;

	// Classifier parameters

	// Subtitle text parameters
};

struct lib_hardsubx_ctx* _init_hardsubx(struct ccx_s_options *options);
void _hardsubx_params_dump(struct ccx_s_options *options, struct lib_hardsubx_ctx *ctx);
void hardsubx(struct ccx_s_options *options);

//hardsubx_decoder.c
int hardsubx_process_frames_linear(struct lib_hardsubx_ctx *ctx);

#endif

#endif