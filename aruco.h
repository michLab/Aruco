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
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/aruco.hpp>

/**
 * @namespace aruco_ns
 * @brief a namespace to encapsulate Aruco class environment
 */
namespace aruco_ns
{
    /**
     * @brief The Aruco class
     */
    class Aruco
    {
    public:
        Aruco();
        void generate_marker(uint16_t marker_id);
        bool detect(cv::Mat& arg_image);

        void set_marker_dictionary(cv::aruco::PREDEFINED_DICTIONARY_NAME arg_dict_name);
        bool set_marker_size_pix(uint16_t arg_size);
        bool set_marker_border_bits(uint16_t arg_border_bits);

        uint16_t get_marker_size_pix() const;
        uint16_t get_marker_border_bits() const;

    private:
        uint16_t marker_size_pix;
        uint16_t marker_border_bits;
        std::vector<int> marker_ids;
        std::vector<std::vector<cv::Point2f>> marker_corners;
        cv::aruco::PREDEFINED_DICTIONARY_NAME aruco_dictionary_name;
        cv::Ptr<cv::aruco::Dictionary> aruco_dictionary;

        void initialize_marker_dictionary();


    };

}

#endif // ARUCO_H
