/**
  @file aruco.cpp
  @brief The definitions used with Aruco class
  @author Michal Labowski
  @date 06-01-2020
  @version 1.0
 */

#include "aruco.h"
#include <opencv2/opencv.hpp>

/**
 * @brief: Default constructor
 */
aruco_ns::Aruco::Aruco()
{
    set_marker_dictionary(cv::aruco::DICT_6X6_250);
    set_marker_size_pix(200);
    set_marker_border_bits(1);
}

/**
 * @brief: Sets Aruco marker dictionary
 * @param: arg_dict_name A openCV aruco dictionary name (enum)
 */
void aruco_ns::Aruco::set_marker_dictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME arg_dict_name)
{
    aruco_dictionary_name = arg_dict_name;
    initialize_marker_dictionary();
}

/**
 * @brief: Sets Aruco marker side size (pixel)
 * @param: arg_size Side size in pixels
 */
bool aruco_ns::Aruco::set_marker_size_pix(uint16_t arg_size)
{
    marker_size_pix = arg_size;
    return true;
}

/**
 * @brief: Sets Aruco marker border bits
 * @param: arg_border_bits Marker border bits
 */
bool aruco_ns::Aruco::set_marker_border_bits(uint16_t arg_border_bits)
{
    marker_border_bits = arg_border_bits;
    return true;
}

/**
 * @brief: Returns Aruco marker border size
 * @return: Border size in bits
 */
uint16_t aruco_ns::Aruco::get_marker_border_bits() const
{
    return marker_border_bits;
}

/**
 * @brief: Returns Aruco marker side size (pixel)
 * @return: Side size in pixels
 */
uint16_t aruco_ns::Aruco::get_marker_size_pix() const
{
    return marker_size_pix;
}

/**
 * @brief: Initialize Aruco marker dictionary
 */
void aruco_ns::Aruco::initialize_marker_dictionary()
{
    aruco_dictionary = cv::aruco::getPredefinedDictionary(aruco_dictionary_name);
}

/**
 * @brief: Generate Aruco marker with given ID from Aruco Dictionary
 * @param: arg_dict_name A openCV aruco dictionary name (enum)
 */
void aruco_ns::Aruco::generate_marker(uint16_t marker_id)
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
//bool aruco_ns::Aruco::detect(std::shared_ptr<cv::Mat> arg_image)
bool aruco_ns::Aruco::detect(cv::Mat& arg_image)
{
    cv::Mat frame;
    cv::Ptr<cv::aruco::DetectorParameters> parameters = cv::aruco::DetectorParameters::create();
    cv::aruco::detectMarkers(frame, aruco_dictionary, marker_corners,
                             marker_ids, parameters, rejected_candidates);


    if (marker_ids.size() > 0) {
        return true;
    } else {
        return false;
    }
}

