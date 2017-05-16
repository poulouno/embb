#ifndef _INPUT_VIDEO_HANDLER_H_
#define _INPUT_VIDEO_HANDLER_H_

struct AVCodecContext;
struct AVFormatContext;
struct AVPacket;
struct AVCodec;
struct AVFrame;

/**
 * This class takes care of the input file (opening and closing
 * the file, extracting frames, ...). The handler cannot be created
 * without an input file (whose name is provided at construction
 * time). If during construction problems occur (file not found,
 * file cannot be opened, ...) an exception is thrown.
 *
 */
class InputVideoHandler {
public:
  InputVideoHandler(char* name);
  ~InputVideoHandler();

  /**
   * Returns the pointer to AVCodecContext that is set at construction.
   */
  AVCodecContext* getCodecContext();

  /**
   * Reads next (or first) frame from the input file. Note that the
   * frame must be allocated before being passed to the function
   * using av_frame_alloc().
   *
   * @param frame pointer to frame that is extracted from input file
   * @param success integer code that tells us if a complete 
            frame was extracted. success == 1 if the frame is valid
   * @return true there are still frames to process, false otherwise
   */
  bool readFrame(AVFrame* frame, int* success);

private:
  InputVideoHandler();
  void init(char* name);

  AVFormatContext* formatCtx_;
  AVCodec* codec_;
  AVCodecContext* codecCtx_;
  AVPacket* packet_;
  int streamIndex_;
};

#endif  // _INPUT_VIDEO_HANDLER_H_

