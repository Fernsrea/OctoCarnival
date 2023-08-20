#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

cv::Mat bilinearInterpolation(const cv::Mat& inputImage, float scale)
{
    // Calculate the new dimensions
    int newWidth = static_cast<int>(inputImage.cols * scale);
    int newHeight = static_cast<int>(inputImage.rows * scale);

    // Create 8-bit placeholder RGB image
    cv::Mat outputImage(newHeight, newWidth, CV_8UC3);

    // Apply to each pixel
    for (int y = 0; y < newHeight; ++y) {
        for (int x = 0; x < newWidth; ++x) {
            // Find the equivalent pixel in original image
            float orgX = static_cast<float>(x) / scale;
            float orgY = static_cast<float>(y) / scale;
            
            int x0 = static_cast<int>(orgX);
            int y0 = static_cast<int>(orgY);
            // To avoid pixel access error
            int x1 = std::min(x0 + 1, inputImage.cols - 1);
            int y1 = std::min(y0 + 1, inputImage.rows - 1);

            // Calculate the offset value of pixel distance between original image and scaled image
            float xWeight = orgX - x0;
            float yWeight = orgY - y0;

            // typedef Vec< uchar, 3 > for RGB
            cv::Vec3b p; // interpolated value p

            // For each channel c, calculate p
            for (int c = 0; c < 3; ++c) {
                p[c] = static_cast<uchar>(
                    // Bilinear interpolation formula
                    (1 - xWeight) * (1 - yWeight) * inputImage.at<cv::Vec3b>(y0, x0)[c] + // Top left neighbour
                    xWeight * (1 - yWeight) * inputImage.at<cv::Vec3b>(y0, x1)[c] + // Top right neighbour
                    (1 - xWeight) * yWeight * inputImage.at<cv::Vec3b>(y1, x0)[c] + // Bottom left neighbour
                    xWeight * yWeight * inputImage.at<cv::Vec3b>(y1, x1)[c] // Bottom right neighbour
                );
            }

            // Copy to the pixel in output image
            outputImage.at<cv::Vec3b>(y, x) = p;
        }
    }

    return outputImage;
}

int display(const std::string& outputFile, const cv::Mat& outputImage, const cv::Mat& inputImage)
{
    // Write the processed image to the output file
    if (!cv::imwrite(outputFile, outputImage)) {
        std::cout << "Could not write the image: " << outputFile << std::endl;
        return 3;
    }

    std::cout << "New dimensions: " << outputImage.cols << " x " << outputImage.rows << std::endl;

    // Open the processed image
    cv::imshow("Output Image", outputImage);
    cv::imshow("Input Image", inputImage);
    cv::waitKey(0); // Wait for a key press

    return 0;
}

int main(int argc, char* argv[]) {
    // Check the command line input
    if (argc != 4) {
        std::cout << "Usage: " << argv[0] << " <input_image> <output_image> <scale>" << std::endl;
        return 1;
    }

    std::string inputFile = argv[1];
    std::string outputFile = argv[2];

    // Read the input image
    cv::Mat inputImage = cv::imread(inputFile);
    if (inputImage.empty()) {
        std::cout << "Could not open or read the image: " << inputFile << std::endl;
        return 2;
    }

    std::cout << "Old dimensions: " << inputImage.cols << " x " << inputImage.rows << std::endl;

    // Amount of scaling to be applied on the image
    float scale = std::stof(argv[3]);

    // Apply image processing
    cv::Mat outputImage = bilinearInterpolation(inputImage, scale);

    // Write the output file and display it
    display(outputFile, outputImage, inputImage);
    
    std::cout << "Image processing completed successfully." << std::endl;

    return 0;
}
