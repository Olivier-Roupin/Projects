#include "libjackc.h"

// Arguments and their default values
static bool program_ended_with_return = false;

// Jack connecting thread.

enum ThreadType{
  UNINITIALIZED_THREAD_TYPE,
  OTHER_THREAD,
  REALTIME_THREAD,
  MAIN_THREAD
};

static __thread enum ThreadType g_thread_type = UNINITIALIZED_THREAD_TYPE;

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
using namespace cv;

/////////////////////////////////////////////////////////////////////
//////////////////////// OpenCV thread //////////////////////////////
/////////////////////////////////////////////////////////////////////
#if 1
static pthread_t opencv_thread={0};

static volatile int opencv_thread_running=0;

static bool is_opencv_running=true;

static void msleep(int n){
  usleep(n*1000);
}

#define WIDTH     12// 12// 24//25
#define HEIGHT   313//312//156
#define OFFSET_W  30// 29// 17 (34++)
#define OFFSET_H  11//  1
#define OFFSET     0//  1

static void *video_field_thread(void *arg) {
  (void)arg; //OLIVIER no warning

  int cv_image_pos = 0;
  int image_w = WIDTH;
  int image_h = HEIGHT;
  int offset_w = OFFSET_W;
  int offset_h = OFFSET_H;
  int offset = OFFSET;
  int preview_w = 640;
  int preview_h = 625;
  bool mode = true;
  bool field = false;
  bool waited = true;
  int v_blank[2];
  int h_blank[2];
  double contrast = 0.65;
  double im_black = 0.0;
  //double im_std[1];
  double im_max = 0.0;
  double im_min = 0.0;

  opencv_thread_running = 1;

  VideoWriter video("out/out.avi",CV_FOURCC('X','2','6','4'),50, Size(preview_w,preview_h), false);
  char window[] = "Image";
  Mat cv_image = Mat::zeros(image_h, image_w, CV_32FC1);
  Mat preview;
  float* image_data = (float*) cv_image.data;
  int k{0};
  do {
    if (cv_image_pos >= image_h*image_w-offset_h) { //Completed field
      //meanStdDev(cv_image, im_avg, im_std);
      minMaxIdx(cv_image, &im_min, &im_max, v_blank, NULL, cv_image > 0);
      im_black = contrast*mean(cv_image)[0]+(1.0-contrast)*im_min;

      //Mat cv_col;
      //reduce(cv_image, cv_col, 1, REDUCE_AVG);
      //minMaxIdx(cv_col, NULL, NULL, h_blank, NULL, cv_col > 0);
      //Mat cv_row;
      //reduce(cv_image, cv_row, 0, REDUCE_AVG);
      //minMaxIdx(cv_row, NULL, NULL, h_blank, NULL, cv_row > 0);
      if (mode) {
        //line(cv_image, Point(0,v_blank[0]), Point(image_w,v_blank[0]), Scalar(1.0));
        //line(cv_image, Point(h_blank[1],0), Point(h_blank[1],image_h), Scalar(1.0));
        resize(cv_image, preview, Size(preview_w, preview_h), INTER_NEAREST);
        Mat cv_row2;
        reduce(preview, cv_row2, 0, REDUCE_AVG);
        minMaxIdx(cv_row2, NULL, NULL, h_blank, NULL, cv_row2 > 0);
        preview = (preview-im_black)/(im_max-im_black);

        Mat centered = Mat::zeros(preview_h, preview_w, CV_32FC1);
        centered(     Rect(         0,0,preview_w-h_blank[1],preview_h)) =
          255*preview(Rect(h_blank[1],0,preview_w-h_blank[1],preview_h));
        // centered(    Rect(         0,0,preview_w-h_blank[1],preview_h)) = 255*(
        //   preview(Rect(h_blank[1],0,preview_w-h_blank[1],preview_h))
        //   -im_black)/(im_max-im_black);
        if (h_blank[1] > 0)
          centered(     Rect(preview_w-h_blank[1],0,h_blank[1]-1,preview_h-2)) =
            255*preview(Rect(                   0,2,h_blank[1]-1,preview_h-2));
          // centered(    Rect(preview_w-h_blank[1],0,h_blank[1]-1,preview_h-2)) = 255*(
          //   preview(Rect(                   0,2,h_blank[1]-1,preview_h-2))
          //   -im_black)/(im_max-im_black);
        centered.convertTo(centered, CV_8UC1);
        //video.write(centered);
        imshow(window, centered);
        char window_title[64];
        sprintf(window_title, "W:%03d H:%03d OW:%03d OH:%03d VB:%03d HB:%03d",
          image_w, image_h, offset_w, offset_h, v_blank[0], h_blank[1]);
        setWindowTitle(window, window_title);
      } else {
        resize(cv_image, preview, Size(2*image_w, 2*image_h), INTER_NEAREST);
        imshow(window, preview); //cv_image
      }
      const char key = waitKey(1);
      if (key == 'p')                      image_w++;
      else if (key == 'm' && image_w > 1)  image_w--;
      else if (key == '!')                 image_w = WIDTH;
      if (key == 'o')                      image_h++;
      else if (key == 'l' && image_h > 1)  image_h--;
      else if (key == ':')                 image_h = HEIGHT;
      if (key == 'i')                      offset_w++;
      else if (key == 'k' && offset_w > -image_w) offset_w--;
      else if (key == ';')                 offset_w = OFFSET_W;
      if (key == 'u')                      offset_h++;
      else if (key == 'j' && offset_h > 0) offset_h--;
      else if (key == ',')                 offset_h = OFFSET_H;
      if (key == 'y')                      offset++;
      else if (key == 'h' && offset > 0)   offset--;
      else if (key == 'n')                 offset = OFFSET;
      if (key == ' ')                      mode = !mode;
      if (key == 27)                       break;
      //cv_image.release();
      if (key) {
        cv_image.create(image_h, image_w, CV_32FC1);// = Mat::zeros(image_h, image_w, CV_32FC1);//0;     //blank image
        image_data = (float*)cv_image.data;
      }
      cv_image = 0;
      cv_image_pos = offset-v_blank[0]*image_w;//-v_blank[0]*image_w-h_blank[1];
      field = !field;
    }
    if (k < vu_vec_len()) {
      if (cv_image_pos >= 0) //Don't draw oustide the image, useful for vsync
        image_data[cv_image_pos] = vu_vec()[k]+0.5;
      ++k;
      ++cv_image_pos;
      if (offset_w > 0 && cv_image_pos % (image_w+offset_w) == 0 && waited) {
        //  ++cv_image_pos;
        --cv_image_pos;
        waited = false;
      } else
        waited = true;
    } else if (vu_new()) //we have a new sample!
      k = 0;
  } while (is_opencv_running);

  opencv_thread_running = 0;
  //msleep(4);
  video.release();
  destroyAllWindows();

  return NULL;
}

#define PAL 0
#define NTSC 1
#define MODE PAL
#define SAVE_PNG    false
#define LINEAR_LINE false
#define SET_TITLE   false

#define SAMPLERATE 192000
#if MODE == PAL
  #define FRAME_RATE    25
  #define FRAME_SAMPLES 7680 // SAMPLERATE/FRAME_RATE
  #define FRAME_LINES   625  //USED_LINES 576
  //#define LINE_SAMPLES  12.288 //FRAME_SAMPLES/FRAME_LINES
  #define OVER_STRETCH  125
  #define OVER_WEIGHT   0.008 // 1/OVER_STRETCH
  #define OVER_WIDTH    1536 // OVER_STRETCH*LINE_SAMPLES
  #define OVER_PIXELS   960000 // OVER_WIDTH*FRAME_LINES
  #define FIELD_RATE    50
  #define FIELD_SAMPLES 3840 // SAMPLERATE/FRAME_RATE
  #define FIELD_LINES   312
#else //MODE==NTSC
  #define FRAME_RATE    30
  #define FRAME_SAMPLES 6400 // SAMPLERATE/FRAME_RATE
  #define FRAME_LINES   480
  //#define LINE_SAMPLES  13.333... //FRAME_SAMPLES/FRAME_LINES
  #define OVER_STRETCH  3
  #define OVER_WIDTH    40   // OVER_STRETCH*LINE_SAMPLES
  #define OVER_PIXELS   19200 // OVER_WIDTH*FRAME_LINES
  #define FIELD_RATE    60
  #define FIELD_SAMPLES 3200 // SAMPLERATE/FRAME_RATE
  #define FIELD_LINES   240
#endif //MODE

#define DISPLAY_WIDTH 320

static void *video_frame_thread(void *arg) {
  (void)arg; //OLIVIER no warning

  opencv_thread_running = 1;

  bool mode{true};
  char window[] = "Image";
  Mat frame = Mat::zeros(FRAME_LINES, OVER_WIDTH, CV_32FC1);
  Mat preview;
  float* buffer = vu_vec();
  float* buffer2 = buffer_pointer();
  float* frame_data = (float*) frame.data;
  int k{0};
  int frame_pos{0};
  int v_offset{0};
  int v_blank[2];
  int h_blank[2];
  double contrast{0.65}, im_black{0.0}, im_max{0.0}, im_min{0.0};
  #if SAVE_PNG
  int frame_num{0};
  char frame_name[32];
  #endif //SAVE_PNG
  #if LINEAR_LINE
  float previous{0};
  #endif //LINEAR_LINE
  do {
    //if (OVER_STRETCH*frame_pos >= FRAME_LINES*OVER_WIDTH) { //Completed field
    if (frame_pos >= OVER_PIXELS) { //Completed field
      minMaxIdx(frame, &im_min, &im_max, v_blank, NULL, frame > 0);
      im_black = contrast*mean(frame)[0]+(1.0-contrast)*im_min;
      if (v_blank[0]+FIELD_LINES >= FRAME_LINES) { //get a full field
        v_blank[1] = v_blank[0];
        v_blank[0] = v_blank[0]-FIELD_LINES;
      } else {
        v_blank[1] = v_blank[0]+FIELD_LINES;
      }
      v_offset = (v_offset+v_blank[0])/2;

      if (mode) {
        resize(frame, preview, Size(DISPLAY_WIDTH, FRAME_LINES), INTER_NEAREST);
        Mat avg_line;
        reduce(preview, avg_line, 0, REDUCE_AVG);
        minMaxIdx(avg_line, NULL, NULL, h_blank, NULL, avg_line > 0);
        preview = (preview-im_black)/(im_max-im_black);

        Mat centered = Mat::zeros(FIELD_LINES, DISPLAY_WIDTH, CV_32FC1);
        centered(
          Rect(         0,         0, DISPLAY_WIDTH-h_blank[1],FIELD_LINES)) =
          1.0*preview(
          Rect(h_blank[1],v_offset, DISPLAY_WIDTH-h_blank[1],FIELD_LINES));
        if (h_blank[1] > 0)
          centered(
            Rect(DISPLAY_WIDTH-h_blank[1],0, h_blank[1]-1,FIELD_LINES-1)) =
            1.0*preview(
            Rect(            0,v_offset+1, h_blank[1]-1,FIELD_LINES-1));
        imshow(window, centered);
        #if SAVE_PNG
        sprintf(frame_name, "out/%06d.png", ++frame_num);
        imwrite(frame_name, 255*centered);
        #endif //SAVE_PNG
        #if SET_TITLE
        char window_title[64];
        sprintf(window_title, "VB1:%03d VB2:%03d HB1:%03d", v_blank[0], v_blank[1], h_blank[1]);
        setWindowTitle(window, window_title);
        #endif //SET_TITLE
      } else {
        resize(frame, preview, Size(DISPLAY_WIDTH, FRAME_LINES), INTER_NEAREST);
        imshow(window, preview);
      }
      const char key = waitKey(1);
      if (key == ' ') mode = !mode;
      if (key == 27)  break;
      frame = 0; //blank image
      frame_pos = 0;
    }
    if (k < vu_vec_len()) {
      #if LINEAR_LINE
      for (int stretch = 0; stretch < OVER_STRETCH; ++stretch)
        //if (stretch+frame_pos*OVER_STRETCH >= 0 && stretch+frame_pos*OVER_STRETCH <= OVER_PIXELS)
        //  frame_data[stretch+frame_pos*OVER_STRETCH] = (stretch*OVER_WEIGHT)*buffer[k]+(1.0-stretch*OVER_WEIGHT)*previous+0.5;
        if (stretch+frame_pos >= 0 && stretch+frame_pos <= OVER_PIXELS)
          frame_data[stretch+frame_pos] = (stretch*OVER_WEIGHT)*buffer[k]+(1.0-stretch*OVER_WEIGHT)*previous+0.5;
      previous = buffer[k];
      #else //LINEAR_LINE
      //for (int stretch = OVER_STRETCH*frame_pos; stretch < OVER_STRETCH*(frame_pos+1); ++stretch)
      if (frame_pos >= 0 && frame_pos <= OVER_PIXELS)
        frame_data[frame_pos] = buffer[k]+0.5;
      for (int stretch = frame_pos+1; stretch < OVER_STRETCH+frame_pos; ++stretch)
        if (stretch >= 0 && stretch <= OVER_PIXELS)
          frame_data[stretch] = frame_data[stretch-1];//buffer[k]+0.5;
      #endif //LINEAR_LINE
      //++frame_pos;
      frame_pos += OVER_STRETCH;
      ++k;
    } else if (vu_new()) //we have a new sample!
      k = 0;
  } while (is_opencv_running);

  opencv_thread_running = 0;
  destroyAllWindows();

  return NULL;
}

static void *video_buffer_thread(void *arg) {
  (void)arg; //OLIVIER no warning

  opencv_thread_running = 1;

  bool mode{false};
  char window[] = "Image";
  Mat frame        = Mat::zeros(FRAME_LINES,   OVER_WIDTH, CV_32FC1);
  Mat preview      = Mat::zeros(FRAME_LINES, DISPLAY_WIDTH, CV_32FC1);
  Mat avg_line     = Mat::zeros(          1, DISPLAY_WIDTH, CV_32FC1);
  Mat centered     = Mat::zeros(FRAME_LINES, DISPLAY_WIDTH, CV_32FC1);
  Mat deinterlaced = Mat::zeros(FIELD_LINES, DISPLAY_WIDTH, CV_32FC1);
  float* buffer = buffer_pointer();
  float* frame_data = (float*) frame.data;
  int k{0};
  //float val_min{2.0f};
  float avg{0.0f}, avg_min{10.0f};
  int k_min{0};
  int frame_pos{0};
  int h_blank[2];
  double contrast{0.65f}, im_black{0.0f}, im_max{-10.0f}, im_min{10.0f}, im_avg{0.5f};
  #if SAVE_PNG
  int frame_num{0};
  char frame_name[32];
  #endif //SAVE_PNG
  #if LINEAR_LINE
  float previous{0};
  #endif //LINEAR_LINE
  do {
    if (frame_pos >= OVER_PIXELS) { //Completed field

      //Buffer-based vertical blanking
      k_min = (OVER_STRETCH*k_min-((OVER_STRETCH*k_min)%OVER_WIDTH))/OVER_STRETCH;
      if (k_min < FRAME_SAMPLES)
        k_min += FRAME_SAMPLES;
      if (k_min - FRAME_SAMPLES < FRAME_SAMPLES/2)
        k_min += FRAME_SAMPLES/2;
      k = k_min+12;
      k_min = k+FRAME_SAMPLES;
      avg = 1.01f*avg_min;
      avg_min = 10.0f;

      if (mode) {
        minMaxIdx(frame, &im_min, &im_max, NULL, NULL, frame > 0);
        im_black = contrast*mean(frame)[0]+(1.0-contrast)*im_min;

        resize(frame, preview, Size(DISPLAY_WIDTH, FRAME_LINES), INTER_NEAREST);
        reduce(preview, avg_line, 0, REDUCE_AVG);
        minMaxIdx(avg_line, NULL, NULL, h_blank, NULL, avg_line > 0);
        preview = (preview-im_black)/(im_max-im_black);
        deinterlaced(
          Rect(         0,         0, DISPLAY_WIDTH-h_blank[1],FIELD_LINES)) =
          1.0*preview(
          Rect(h_blank[1],0, DISPLAY_WIDTH-h_blank[1],FIELD_LINES));
        if (h_blank[1] > 0)
          deinterlaced(
            Rect(DISPLAY_WIDTH-h_blank[1],0, h_blank[1]-1,FIELD_LINES-1)) =
            1.0*preview(
            Rect(            0,1, h_blank[1]-1,FIELD_LINES-1));
        imshow(window, deinterlaced);
        #if SAVE_PNG
        sprintf(frame_name, "out/%06d.png", ++frame_num);
        imwrite(frame_name, 255*deinterlaced);
        #endif //SAVE_PNG
        #if SET_TITLE
        char window_title[64];
        sprintf(window_title, "HB1:%03d", h_blank[1]);
        setWindowTitle(window, window_title);
        #endif //SET_TITLE
      } else {
        //minMaxIdx(frame, &im_min, &im_max, NULL, NULL, frame > 0);
        //im_black = contrast*mean(frame)[0]+(1.0-contrast)*im_min;
        im_black = contrast*(im_avg/FRAME_SAMPLES)+(1.0-contrast)*im_min;
        resize(frame, preview, Size(DISPLAY_WIDTH, FRAME_LINES), INTER_NEAREST);

        reduce(preview, avg_line, 0, REDUCE_AVG);
        minMaxIdx(avg_line, NULL, NULL, h_blank, NULL, avg_line > 0);
        //preview = (preview-im_black)/(im_max-im_black);

        centered(
          Rect(         0,0, DISPLAY_WIDTH-h_blank[1],FRAME_LINES)) =
          0.5*preview(
          Rect(h_blank[1],0, DISPLAY_WIDTH-h_blank[1],FRAME_LINES));
        if (h_blank[1] > 0)
          centered(
            Rect(DISPLAY_WIDTH-h_blank[1],0, h_blank[1]-1,FRAME_LINES-1)) =
            0.5*preview(
            Rect(                       0,1, h_blank[1]-1,FRAME_LINES-1));
        deinterlaced = centered(Rect(0,0,DISPLAY_WIDTH,FIELD_LINES))+
                       centered(Rect(0,FIELD_LINES,DISPLAY_WIDTH,FIELD_LINES));
        imshow(window, deinterlaced);

        #if SAVE_PNG
        sprintf(frame_name, "out/%06d.png", ++frame_num);
        imwrite(frame_name, 255*deinterlaced);
        #endif //SAVE_PNG
        im_avg = 0;
        im_min = 10.0f;
        im_max = -10.0f;
      }
      const char key = waitKey(1);
      if (key == ' ') mode = !mode;
      if (key == 27)  break;
      //frame = 0; //blank image
      frame_pos = 0;
    }
    int l{buffer_pos()};
    if ((l >= FRAME_SAMPLES && k <= l && k >= l-FRAME_SAMPLES) ||
        (l < FRAME_SAMPLES && (k <= l || k >= l+FRAME_SAMPLES))) {
      const float val(buffer[k]+0.5f);
      if (val < im_min) im_min = val;
      if (val > im_max) im_max = val;
      im_avg += val;
      avg = (23.576f*avg+val)/24.576f;//avg = (11.288f*avg+val)/12.288f;
      if (avg_min >= avg) {
        avg_min = avg;
        k_min = k;
      }
      #if LINEAR_LINE
      for (int stretch = 0; stretch < OVER_STRETCH; ++stretch)
        if (stretch+frame_pos >= 0 && stretch+frame_pos <= OVER_PIXELS)
          frame_data[stretch+frame_pos] = (stretch*OVER_WEIGHT)*val+(1.0-stretch*OVER_WEIGHT)*previous;
      previous = val;
      #else //LINEAR_LINE
      for (int stretch = frame_pos; stretch < OVER_STRETCH+frame_pos; ++stretch)
        if (stretch >= 0 && stretch <= OVER_PIXELS)
          frame_data[stretch] = val;//buffer[k]+0.5;
      #endif //LINEAR_LINE
      frame_pos += OVER_STRETCH;
      ++k;
    }
    if (k >= 2*FRAME_SAMPLES) {
      k = 0;
    }
  } while (is_opencv_running);

  opencv_thread_running = 0;
  destroyAllWindows();

  return NULL;
}

#if MODE == PAL
  #define UNDER_STRETCH 26
  #define UNDER_PAD     24
  #define UNDER_WEIGHT  0.0384 // 1/(UNDER_STRETCH+1/UNDER_PAD)
  #define PAD_CENTER    12
  #define UNDER_WIDTH   320 // (UNDER_STRETCH+1/UNDER_PAD)*LINE_SAMPLES==DISPLAY_WIDTH
  #define UNDER_PIXELS  200000 // UNDER_WIDTH*FRAME_LINES
#else //MODE==NTSC
  #define UNDER_STRETCH 24
  //#define UNDER_PAD     inf
  //#define PAD_CENTER    0
  #define UNDER_WIDTH   320 // (UNDER_STRETCH+1/UNDER_PAD)*LINE_SAMPLES==DISPLAY_WIDTH
  #define UNDER_PIXELS  153600 // UNDER_WIDTH*FRAME_LINES
#endif //MODE

#define DEINTERLACED_COUNT  3
#define DEINTERLACED_OFF    0
#define DEINTERLACED_FIELD  1
#define DEINTERLACED_FRAME  2
#define DEINTERLACED_BUFFER 3 //Try deinterlacing by "reshaping" the buffer (two fields side by side)

#define CONTRAST_COUNT   3
#define CONTRAST_OFF     0
#define CONTRAST_PREVIEW 1
#define CONTRAST_BUFFER  2

#define H_BLANK_COUNT   2
#define H_BLANK_OFF     0
#define H_BLANK_PREVIEW 1
#define H_BLANK_MANUAL  2 //useless

#define V_BLANK_COUNT   2
#define V_BLANK_OFF     0
#define V_BLANK_BUFFER  1
#define V_BLANK_PREVIEW 2 //unstable

static void *video_padded_thread(void *arg) {
  (void)arg; //OLIVIER no warning

  opencv_thread_running = 1;

  bool mode{false};
  char d_mode{DEINTERLACED_FRAME};
  char c_mode{CONTRAST_BUFFER};
  char h_mode{H_BLANK_PREVIEW};
  char v_mode{V_BLANK_BUFFER};

  char window[] = "Image";
  Mat frame        = Mat::zeros(FRAME_LINES, UNDER_WIDTH, CV_32FC1);
  Mat avg_line     = Mat::zeros(          1, UNDER_WIDTH, CV_32FC1);
  Mat avg_col      = Mat::zeros(FRAME_LINES,           1, CV_32FC1);
  Mat centered     = Mat::zeros(FRAME_LINES, UNDER_WIDTH, CV_32FC1);
  Mat deinterlaced = Mat::zeros(FIELD_LINES, UNDER_WIDTH, CV_32FC1);
  float* buffer     = buffer_pointer();
  float* frame_data = (float*) frame.data;
  //float val_min{2.0f};
  int   b_w_prev{0};
  int   b_r{0},    b_r_min{0};
  float avg{0.0f}, avg_min{10.0f};
  int frame_pos{0};
  int v_blank[2], v_safe{0};
  int h_blank[2], h_blank_prev{0};
  double contrast{0.65f}, im_black{0.0f}, im_max{-10.0f}, im_min{10.0f}, im_avg{0.5f};
  #if SAVE_PNG
  int frame_num{0};
  char frame_name[32];
  #endif //SAVE_PNG
  #if LINEAR_LINE
  float previous{0};
  #endif //LINEAR_LINE
  do {
    if (frame_pos >= UNDER_PIXELS) { //Completed field
      //Buffer-based vertical blanking
      if (v_mode == V_BLANK_BUFFER) {
        b_r_min = (OVER_STRETCH*b_r_min-((OVER_STRETCH*b_r_min)%OVER_WIDTH))/OVER_STRETCH;
        b_r     = b_r_min+UNDER_STRETCH;//+12;
        avg     = im_avg;//1.01f*avg_min;
        avg_min = 10.0f;
        //Make sure we don't wait for/skip frames
        const int b_w{buffer_pos()};
        if (b_w >= FRAME_SAMPLES) {
          if (b_r < b_w-FRAME_SAMPLES) //b_r is in the negatives
            b_r += FRAME_SAMPLES/2;
          if (b_r >= b_w) //b_r may overshoot b_w
            b_r -= FRAME_SAMPLES/2;
        } else { //b_w < FRAME_SAMPLES
            if (b_r < b_w+FRAME_SAMPLES && b_r >= b_w)
              b_r += FRAME_SAMPLES/2;
            if (b_r < b_w+FRAME_SAMPLES && b_r >= b_w)
              b_r -= FRAME_SAMPLES/2;
        }
        b_r_min = b_r+FRAME_SAMPLES;

      } else if (v_mode == V_BLANK_PREVIEW) {
        reduce(frame, avg_col, 1, REDUCE_AVG);
        minMaxIdx(avg_col, NULL, NULL, v_blank, NULL);
        //minMaxIdx(frame, &im_min, &im_max, v_blank, NULL, frame > 0);
        if (v_blank[0]+FIELD_LINES >= FRAME_LINES) { //get a full field
          v_blank[1] = v_blank[0];
          v_blank[0] = v_blank[0]-FIELD_LINES;
        } else {
          v_blank[1] = v_blank[0]+FIELD_LINES;
        }
        //v_offset = (v_offset+v_blank[0])/2;
        b_r = (v_blank[1]*UNDER_WIDTH*UNDER_PAD)/(1+UNDER_PAD*UNDER_STRETCH);
      }

      if (h_mode == H_BLANK_OFF) {
        #if SET_TITLE
        h_blank[0] = h_blank[1];
        #endif //SET_TITLE
        h_blank[1] = 0;
      } else if (h_mode == H_BLANK_MANUAL) {
        #if SET_TITLE
        h_blank[0] = h_blank[1];
        #endif //SET_TITLE
        h_blank[1] = (h_blank[1]+8)%UNDER_WIDTH;
        if (h_blank[1] % 5 == 0) //one more for padding
          h_blank[1] = (h_blank[1]+1)%UNDER_WIDTH;
      } else {
        //Preview-based horizontal blanking
        reduce(frame, avg_line, 0, REDUCE_AVG);
        minMaxIdx(avg_line, NULL, NULL, h_blank, NULL);
        #if SET_TITLE
        h_blank[0] = h_blank_prev;
        #endif //SET_TITLE
        //check if the h_blank is moving in the correct direction
        // if (h_blank_prev > h_blank[1] && h_blank_prev-h_blank[1] < UNDER_WIDTH/2)
        //   h_blank[1] = h_blank_prev;
        // else
          h_blank_prev = h_blank[1];
      }

      if (c_mode != CONTRAST_OFF) {
        if (c_mode == CONTRAST_PREVIEW) {
          //Preview-based contrast estimation
          minMaxIdx(frame, &im_min, &im_max, NULL, NULL, frame > 0);
          im_black = contrast*mean(frame)[0]+(1.0-contrast)*im_min;
        } else {
          //Buffer-based contrast estimation
          im_black = contrast*(im_avg/FRAME_SAMPLES)+(1.0-contrast)*im_min;
        }
        frame = (frame-im_black)/(im_max-im_black);
      } else {
        frame /= im_max;
      }

      if (d_mode == DEINTERLACED_FIELD) {
        //Deinterlacing by only showing one field
        deinterlaced(
          Rect(         0,0, UNDER_WIDTH-h_blank[1],FIELD_LINES)) =
          1.0*frame(
          Rect(h_blank[1],0, UNDER_WIDTH-h_blank[1],FIELD_LINES));
        if (h_blank[1] > 0)
          deinterlaced(
            Rect(UNDER_WIDTH-h_blank[1],0, h_blank[1],FIELD_LINES-1)) =
            1.0*frame(
            Rect(                       0,1, h_blank[1],FIELD_LINES-1));
      } else {
        //Deinterlacing by averaging both fields
        centered(
          Rect(         0,0, UNDER_WIDTH-h_blank[1],FRAME_LINES)) =
          0.5*frame(
          Rect(h_blank[1],0, UNDER_WIDTH-h_blank[1],FRAME_LINES));
        if (h_blank[1] > 0)
          centered(
            Rect(UNDER_WIDTH-h_blank[1],0, h_blank[1],FRAME_LINES-1)) =
            0.5*frame(
            Rect(                       0,1, h_blank[1],FRAME_LINES-1));
        if (d_mode == DEINTERLACED_FRAME)
          deinterlaced = centered(Rect(0,0,          UNDER_WIDTH,FIELD_LINES))+
                         centered(Rect(0,FIELD_LINES+1,UNDER_WIDTH,FIELD_LINES));
      }

      //Output
      imshow(window, d_mode == DEINTERLACED_OFF ? 2.0*centered : deinterlaced);
      #if SAVE_PNG
      sprintf(frame_name, "out/%06d.png", ++frame_num);
      imwrite(frame_name, 255*deinterlaced);
      #endif //SAVE_PNG
      #if SET_TITLE
      char window_title[64];
      sprintf(window_title, "DM:%01d HM:%01d VM:%01d",
        (int)d_mode, (int)h_mode, (int)v_mode);
      setWindowTitle(window, window_title);
      #endif //SET_TITLE

      const char key = waitKey(1);
      if (key >= 0) {
        if (key == ' ') mode = !mode;
        if (key == 'c') c_mode = (c_mode+1) %     CONTRAST_COUNT;
        if (key == 'd') d_mode = (d_mode+1) % DEINTERLACED_COUNT;
        if (key == 'h') h_mode = (h_mode+1) %      H_BLANK_COUNT;
        if (key == 'v') v_mode = (v_mode+1) %      V_BLANK_COUNT;
        if (key == 'p') b_r = (b_r*OVER_STRETCH+OVER_WIDTH)/OVER_STRETCH;
        if (key == 'm') b_r = (b_r*OVER_STRETCH-OVER_WIDTH)/OVER_STRETCH;
        //if (key == 'p') v_safe = (v_safe*OVER_STRETCH+OVER_WIDTH)/OVER_STRETCH;
        //if (key == 'm') v_safe = (v_safe*OVER_STRETCH-OVER_WIDTH)/OVER_STRETCH;

        if (key == 'j') h_blank[1] = (h_blank[1]+3)%UNDER_WIDTH;
        if (key == 'k') h_blank[1] = (h_blank[1]+UNDER_WIDTH-1)%UNDER_WIDTH;

        if (key == 27)  break;
      }
      frame_pos = 0;
      im_avg =   0.0f;
      im_min =  10.0f;
      im_max = -10.0f;
      //b_w_prev = buffer_pos();
    }
    //Check if the pen in inside the current frame
    const int b_w{buffer_pos()};
    //if (true) {
    //if ((b_w-v_safe >= FRAME_SAMPLES &&  b_r <= b_w-v_safe && b_r >= b_w-v_safe-FRAME_SAMPLES) ||
    //    (b_w-v_safe <  FRAME_SAMPLES && (b_r <= b_w-v_safe || b_r >= b_w-v_safe+FRAME_SAMPLES))) {
    //if ((b_w_prev >= FRAME_SAMPLES &&  b_w <= b_w_prev && b_w >= b_w_prev-FRAME_SAMPLES) ||
    //    (b_w_prev <  FRAME_SAMPLES && (b_w <= b_w_prev || b_w >= b_w_prev+FRAME_SAMPLES))) {
    if ((b_w >= FRAME_SAMPLES &&  b_r <= b_w && b_r >= b_w-FRAME_SAMPLES) ||
        (b_w <  FRAME_SAMPLES && (b_r <= b_w || b_r >= b_w+FRAME_SAMPLES))) {
      const float val{buffer[b_r]+0.5f};
      if (val < im_min) im_min = val;
      if (val > im_max) im_max = val;
      im_avg += val;
      avg = (23.576f*avg+val)/24.576f;//avg = (11.288f*avg+val)/12.288f;
      if (avg_min >= avg) {
        avg_min = avg;
        b_r_min = b_r;
      }
      #if LINEAR_LINE
      for (int stretch = 0; stretch < UNDER_STRETCH; ++stretch)
        if (stretch+frame_pos >= 0 && stretch+frame_pos <= UNDER_PIXELS)
          frame_data[stretch+frame_pos] = (stretch*UNDER_WEIGHT)*val+(1.0-stretch*UNDER_WEIGHT)*previous;
      previous = val;
      #else //LINEAR_LINE
      for (int stretch = frame_pos; stretch < UNDER_STRETCH+frame_pos; ++stretch)
        if (stretch >= 0 && stretch <= UNDER_PIXELS)
          frame_data[stretch] = val;
      #endif //LINEAR_LINE
      frame_pos += UNDER_STRETCH;
      if ((b_r-PAD_CENTER) % UNDER_PAD == 0) //one more for padding
        frame_data[frame_pos++] = val;
      ++b_r;
    }
    if (b_r >= 2*FRAME_SAMPLES)
      b_r = 0;
  } while (is_opencv_running);

  opencv_thread_running = 0;
  destroyAllWindows();

  return NULL;
}

static void *video_direct_thread(void *arg) {
  (void)arg; //OLIVIER no warning

  opencv_thread_running = 1;

  char d_mode{DEINTERLACED_OFF};
  char c_mode{    CONTRAST_OFF};
  char h_mode{     H_BLANK_OFF};
  char v_mode{     V_BLANK_OFF};

  char window[] = "Image";
  Mat frame        = Mat::zeros(FRAME_LINES, UNDER_WIDTH, CV_32FC1);
  Mat avg_line     = Mat::zeros(          1, UNDER_WIDTH, CV_32FC1);
  Mat avg_col      = Mat::zeros(FRAME_LINES,           1, CV_32FC1);
  Mat centered     = Mat::zeros(FRAME_LINES, UNDER_WIDTH, CV_32FC1);
  Mat deinterlaced = Mat::zeros(FIELD_LINES, UNDER_WIDTH, CV_32FC1);
  float* buffer    = buffer_pointer();
  //float* frame_data = (float*) frame.data;
  //float val_min{2.0f};
  int   b_w_prev{0};
  int   b_r{0},    b_r_min{0};
  float avg{0.0f}, avg_min{10.0f};
  int previous_pos{buffer_pos()};
  int frame_pos{0};
  int v_blank[2], v_safe{0};
  int h_blank[2], h_blank_prev{0};
  double contrast{0.65f}, im_black{0.0f}, im_max{-10.0f}, im_min{10.0f}, im_avg{0.5f};
  do {
    const int current_pos{buffer_pos()}; //Completed frame?
    if (vu_new() &&
        (previous_pos >= UNDER_PIXELS && current_pos <  UNDER_PIXELS) ||
        (previous_pos <  UNDER_PIXELS && current_pos >= UNDER_PIXELS)) {

      if (current_pos >= UNDER_PIXELS) {
        /*const int lines_top{UNDER_PIXELS-current_pos}
        Mat frame_top = Mat::zeros(FRAME_LINES, UNDER_WIDTH, CV_32FC1);
        Mat frame_bot = Mat::zeros(FRAME_LINES, UNDER_WIDTH, CV_32FC1);*/
        frame.data = (uchar*)&(buffer[current_pos-UNDER_PIXELS]);
      } else
        frame.data = (uchar*)&(buffer[current_pos]);
      if (h_mode == H_BLANK_OFF) {
        #if SET_TITLE
        h_blank[0] = h_blank[1];
        #endif //SET_TITLE
        h_blank[1] = 0;
      } else {
        //Preview-based horizontal blanking
        reduce(frame, avg_line, 0, REDUCE_AVG);
        minMaxIdx(avg_line, NULL, NULL, h_blank, NULL);
        #if SET_TITLE
        h_blank[0] = h_blank_prev;
        #endif //SET_TITLE
        h_blank_prev = h_blank[1];
      }

      im_min = buffer_min();
      im_max = buffer_max();
      frame = (frame-im_min)/(im_max-im_min);
      centered(
        Rect(         0,0, UNDER_WIDTH-h_blank[1],FRAME_LINES)) =
        1.0*frame(
        Rect(h_blank[1],0, UNDER_WIDTH-h_blank[1],FRAME_LINES));
      if (h_blank[1] > 0)
        centered(
          Rect(UNDER_WIDTH-h_blank[1],0, h_blank[1],FRAME_LINES-1)) =
          1.0*frame(
          Rect(                       0,1, h_blank[1],FRAME_LINES-1));

      previous_pos = current_pos;
      //Output
      imshow(window, centered);
      const char key = waitKey(1);
      if (key >= 0) {
        if (key == 'p') previous_pos = (previous_pos*OVER_STRETCH+OVER_WIDTH)/OVER_STRETCH;
        if (key == 'm') previous_pos = (previous_pos*OVER_STRETCH-OVER_WIDTH)/OVER_STRETCH;
        if (key == 'j') h_blank[1] = (h_blank[1]+3)%UNDER_WIDTH;
        if (key == 'k') h_blank[1] = (h_blank[1]+UNDER_WIDTH-1)%UNDER_WIDTH;
        if (key == 27)  break;
      }
    }
  } while (is_opencv_running);

  opencv_thread_running = 0;
  destroyAllWindows();

  return NULL;
}

static void stop_opencv_thread(void){
  is_opencv_running=false;
  pthread_join(opencv_thread, NULL);
}
#endif

int main (int argc, char *argv[]){
  //get_free_mem();
  //mainpid=getpid();
  g_thread_type = MAIN_THREAD;

  char **org_argv = argv;

  // remove exe name from argument list.
  argv = &argv[1];
  argc = argc-1;

  // get arguments both from command line and config file (config file is read first, so that command line can override)
  int c_argc;
  char **c_argv = read_config(&c_argc,500);

  append_argv(c_argv,(const char**)argv,c_argc,argc,500);

  init_arguments(c_argc+argc,c_argv);

  init_various();

  pthread_create(&opencv_thread, NULL, video_direct_thread, NULL); //OLIVIER

  wait_until_recording_finished();

  stop_recording_and_cleanup();

  return 0;
}
