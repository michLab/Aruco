#include <iostream>
#include <aruco.h>
#include <camera/camera.h>

using namespace std;

int main()
{
    aruco_ns::Aruco aruco;
    /// Create camera object and get calibration data:
    camera_ns::Camera cam;
    cam.set_video_source(0);
    cam.set_camera_calibration_results_file_name("cam_calib.txt");
    if(cam.get_calibrated() == false) {
        try {
            cam.load_camera_calibration_data();
        } catch (camera_ns::ExceptionMessage ex) {
            std::cout << ex.msg << std::endl;
        }
    }

    /// Create window for showing frame with aruco markers:
    cv::namedWindow("Aruco", CV_WINDOW_AUTOSIZE);

    while (true) {
        try {
            cam.read();
            //cam.show_frame_raw();
            cam.compensate_distortions(camera_ns::CorrectionType::undistort);
            cam.show_frame_compensated();
        } catch (camera_ns::ExceptionMessage ex) {
            std::cout << ex.msg << std::endl;
        }
        /// Aruco will work on copied frame:
        cv::Mat frame_for_aruco = cam.get_frame_raw();
        if (aruco.detect(frame_for_aruco)) {
            aruco.draw_detected(frame_for_aruco);
        }
        cv::imshow("Aruco", frame_for_aruco);
        cv::waitKey(10);
    }

    return 0;
}
