/**
  @file aruco.cpp
  @brief The definitions used with Aruco class
  @author Michal Labowski
  @date 06-01-2020
  @version 1.0
 */

#include "aruco.h"
#include <opencv2/opencv.hpp>

using namespace aruco_ns;
/**
 * @brief: Default constructor
 */
Aruco::Aruco()
{
    set_marker_dictionary(cv::aruco::DICT_6X6_250);
    aruco_parameters = cv::aruco::DetectorParameters::create();
    set_marker_size_pix(200);
    set_marker_border_bits(1);
    set_marker_size_meters(0.05f);
    set_marker_axis_size_meters(0.1f);
    camera_matrix = cv::Mat::zeros(0, 0, CV_64F);
    dist_coefs = cv::Mat::zeros(0, 0, CV_64F);
}

/**
 * @brief: Sets Aruco marker dictionary
 * @param: arg_dict_name A openCV aruco dictionary name (enum)
 */
void Aruco::set_marker_dictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME arg_dict_name)
{
    aruco_dictionary_name = arg_dict_name;
    initialize_marker_dictionary();
}

/**
 * @brief aruco_ns::Aruco::set_marker_axis_size_meters
 * @param arg_s Marker axis size [m]
 */
void Aruco::set_marker_axis_size_meters(SizeMeters arg_s)
{
    axis_size = arg_s;
}

/**
 * @brief: Sets Aruco marker side size (pixel)
 * @param: arg_size Side size in pixels
 */
bool Aruco::set_marker_size_pix(SizePixels arg_size)
{
    marker_size_pix = arg_size;
    return true;
}

/**
 * @brief aruco_ns::Aruco::set_marker_size_meters
 * @param arg_size Marker side size [m]
 * @return true when succesfull
 */
bool Aruco::set_marker_size_meters(SizeMeters arg_size)
{
    marker_size_meters = arg_size;
    return true;
}

/**
 * @brief: Sets Aruco marker border bits
 * @param: arg_border_bits Marker border bits
 */
bool Aruco::set_marker_border_bits(SizeBits arg_border_bits)
{
    marker_border_bits = arg_border_bits;
    return true;
}

/**
 * @brief aruco_ns::Aruco::set_camera_matrix
 * @param arg_m Camera Matrix
 * @return true when successfull
 */
bool Aruco::set_camera_matrix(CameraMatrix arg_m)
{
    camera_matrix = arg_m;
    return true;
}

/**
 * @brief aruco_ns::Aruco::set_dist_coefs
 * @param arg_m A dist coefs matriix
 * @return true when successfull
 */
bool Aruco::set_dist_coefs(DistCoefs arg_m)
{
    dist_coefs = arg_m;
    return true;
}

/**
 * @brief: Returns Aruco marker border size
 * @return: Border size in bits
 */
SizeBits Aruco::get_marker_border_bits() const
{
    return marker_border_bits;
}

/**
 * @brief aruco_ns::Aruco::get_marker_size_meters
 * @return Marker side size [m]
 */
SizeMeters Aruco::get_marker_size_meters() const
{
    return marker_size_meters;
}

/**
 * @brief aruco_ns::Aruco::get_axis_size
 * @return Marker axis size [m]
 */
SizeMeters Aruco::get_axis_size() const
{
    return axis_size;
}

/**
 * @brief: Returns Aruco marker side size (pixel)
 * @return: Side size in pixels
 */
SizePixels Aruco::get_marker_size_pix() const
{
    return marker_size_pix;
}

/**
 * @brief: Initialize Aruco marker dictionary
 */
void Aruco::initialize_marker_dictionary()
{
    aruco_dictionary = cv::aruco::getPredefinedDictionary(aruco_dictionary_name);
}

/**
 * @brief: Generate Aruco marker with given ID from Aruco Dictionary
 * @param: arg_dict_name A openCV aruco dictionary name (enum)
 */
void Aruco::generate_marker(MarkerID marker_id)
{
    cv::Mat marker_image;
    cv::aruco::drawMarker(aruco_dictionary, marker_id, marker_size_pix,
                          marker_image, marker_border_bits);
    std::string file_name = "marker" + std::to_string(marker_id) + ".png";
    cv::imwrite(file_name, marker_image);
}

/**
 * @brief aruco_ns::Aruco::detect
 * @param arg_image A shared_ptr to cv::Mat
 * @return true when aruco markers were detected
 */
bool Aruco::detect(Image& arg_image)
{

    cv::aruco::detectMarkers(arg_image, aruco_dictionary, marker_corners,
                             marker_ids, aruco_parameters, rejected_candidates);

    if (marker_ids.size() > 0) {
        return true;
    } else {
        return false;
    }
}

/**
 * @brief aruco_ns::Aruco::draw_detected
 * @param image a reference to image, on which the aruco
 * markers will be drawn
 */
void Aruco::draw_detected(Image& image)
{
    cv::aruco::drawDetectedMarkers(image, marker_corners, marker_ids);
}

/**
 * @brief Aruco::draw_axis
 * @param image An image to draw marker's axes
 */
void Aruco::draw_axis(Image &image)
{
    for (std::size_t i =0; i < marker_ids.size(); ++i) {
        cv::aruco::drawAxis(image, camera_matrix, dist_coefs,
                            rvecs[i], tvecs[i], axis_size);
    }
}

/**
 * @brief Aruco::draw_pose_info
 * @param image An image to write markers info
 */
void Aruco::draw_pose_info(Image &image)
{
    const int line_initial_offset = 20;
    const int line_separation = 20;
    for (std::size_t i =0; i < marker_ids.size(); ++i) {
        std::string tmp_str = "ID: " + std::to_string(marker_ids[i]);
        tmp_str += " x: " + std::to_string(tvecs[i][0]);
        tmp_str += " y: " + std::to_string(tvecs[i][1]);
        tmp_str += " z: " + std::to_string(tvecs[i][2]);
        putText(image, tmp_str, cvPoint(30, line_initial_offset
                                        + i*line_separation),
            cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,0,200), 1, CV_AA);
    }
}

/**
 * @brief Aruco::estimate_pose_single_markers
 */
void Aruco::estimate_pose_single_markers()
{
    if (camera_matrix.rows > 0 and camera_matrix.cols > 0
            and dist_coefs.rows > 0 and dist_coefs.cols > 0) {
        cv::aruco::estimatePoseSingleMarkers(marker_corners, marker_size_meters,
                                             camera_matrix, dist_coefs,
                                             rvecs, tvecs);
    } else {
        ;
    }
}


