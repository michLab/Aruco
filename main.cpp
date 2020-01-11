#include <iostream>
#include <aruco.h>
#include <camera/camera.h>

//#define CAM_CALIBRATE

using namespace std;
constexpr aruco_ns::SizeMeters marker_size_m = 0.05178f;

int main()
{
    aruco_ns::Aruco aruco;
    aruco.set_marker_size_meters(marker_size_m);
    /// Create camera object and get calibration data:
    camera_ns::Camera cam;
    cam.set_video_source(0);
    cam.set_camera_calibration_results_file_name("cam_calib.txt");
#ifdef CAM_CALIBRATE
    cam.set_chessboard_dimensions(6,9);
    cam.set_chessboard_square_dimension(0.0268f);
    cam.set_number_of_images_to_calibrate(20);
    try {
        cam.calibrate();
    } catch (camera_ns::ExceptionMessage ex) {
        std::cout << ex.msg << std::endl;
    }
#endif
    if(cam.get_calibrated() == false) {
        try {
            cam.load_camera_calibration_data();
            aruco.set_camera_matrix(cam.get_camera_matrix());
            aruco.set_dist_coefs(cam.get_dist_coefs());
        } catch (camera_ns::ExceptionMessage ex) {
            std::cout << ex.msg << std::endl;
        }
    }

    /// Create window for showing frame with aruco markers:
    cv::namedWindow("Aruco");//, CV_WINDOW_AUTOSIZE);

    while (true) {
        try {
            cam.read();
            //cam.show_frame_raw();
            cam.compensate_distortions(camera_ns::CorrectionType::undistort);
            //cam.show_frame_compensated();
        } catch (camera_ns::ExceptionMessage ex) {
            std::cout << ex.msg << std::endl;
        }
        /// Aruco will work on copied frame:
        cv::Mat& frame_for_aruco = cam.get_reference_to_frame_calibrated();
        if (aruco.detect(frame_for_aruco)) {
            aruco.draw_detected(frame_for_aruco);
            aruco.estimate_pose_single_markers();
            aruco.draw_axis(frame_for_aruco);
            aruco.draw_pose_info(frame_for_aruco);
        }
        cv::imshow("Aruco", frame_for_aruco);
        cv::waitKey(10);
    }

    return 0;
}
