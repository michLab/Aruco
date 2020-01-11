/**
  @file aruco.h
  @brief A declarations used with Aruco class
  @author Michal Labowski
  @date 06-01-2020
  @version 1.0
 */

#ifndef ARUCO_H
#define ARUCO_H

#include <cstdint>
#include <memory>
//#include <opencv4/opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/aruco.hpp>

/**
 * @namespace aruco_ns
 * @brief a namespace to encapsulate Aruco class environment
 */
namespace aruco_ns
{
    typedef float SizeMeters;
    typedef uint16_t SizePixels;
    typedef uint16_t SizeBits;
    typedef cv::Mat Image;
    typedef cv::Mat CameraMatrix;
    typedef cv::Mat DistCoefs;
    typedef uint16_t MarkerID;
    /**
     * @brief The Aruco class
     */
    class Aruco
    {
    public:
        Aruco();
        void generate_marker(MarkerID marker_id);
        void draw_detected(Image& image);
        void draw_axis(Image& image);
        void estimate_pose_single_markers();
        bool detect(Image& arg_image);

        void set_marker_dictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME arg_dict_name);
        void set_marker_axis_size_meters(SizeMeters arg_s);
        bool set_marker_size_pix(SizePixels arg_size);
        bool set_marker_size_meters(SizeMeters arg_size);
        bool set_marker_border_bits(SizeBits arg_border_bits);
        bool set_camera_matrix(CameraMatrix arg_m);
        bool set_dist_coefs(DistCoefs arg_m);

        SizePixels get_marker_size_pix() const;
        SizeBits get_marker_border_bits() const;
        SizeMeters get_marker_size_meters() const;
        SizeMeters get_axis_size() const;

    private:
        SizePixels marker_size_pix;
        SizeBits marker_border_bits;
        std::vector<int> marker_ids;
        std::vector<std::vector<cv::Point2f>> marker_corners;
        std::vector<std::vector<cv::Point2f>> rejected_candidates;
        std::vector<cv::Vec3d> rvecs; /// Rotation vectors to detected markers
        std::vector<cv::Vec3d> tvecs; /// Translation vectors to detected markers
        cv::aruco::PREDEFINED_DICTIONARY_NAME aruco_dictionary_name;
        cv::Ptr<cv::aruco::Dictionary> aruco_dictionary;
        cv::Ptr<cv::aruco::DetectorParameters> aruco_parameters;
        Image copied_image;
        CameraMatrix camera_matrix;
        DistCoefs dist_coefs;
        SizeMeters marker_size_meters;
        SizeMeters axis_size;

        void initialize_marker_dictionary();


    };

}

#endif // ARUCO_H
