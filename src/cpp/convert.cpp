#include <iostream>
#include <opencv2/opencv.hpp>
#include <libraw/libraw.h>
#include <filesystem>
namespace fs = std::filesystem;

int processFile(const fs::path &input_path, const fs::path &output_dir)
{
  LibRaw RawProcessor;
  cv::Mat image;

  // 读取文件路径
  std::string filePath = input_path.string();
  if (RawProcessor.open_file(filePath.c_str()) != LIBRAW_SUCCESS)
  {
    std::cerr << "Could not open file: " << filePath << std::endl;
    return EXIT_FAILURE;
  }

  if (RawProcessor.unpack() != LIBRAW_SUCCESS)
  {
    std::cerr << "Could not unpack file: " << filePath << std::endl;
    return EXIT_FAILURE;
  }

  RawProcessor.imgdata.params.no_auto_bright = 1; // disable automatic brightness adjustment

  if (RawProcessor.dcraw_process() != LIBRAW_SUCCESS)
  {
    std::cerr << "Could not process file: " << filePath << std::endl;
    return EXIT_FAILURE;
  }

  libraw_processed_image_t *image_ptr = RawProcessor.dcraw_make_mem_image();

  if (image_ptr != nullptr)
  {
    // The image is stored in bgr format by LibRaw, not rgb
    cv::Mat temp(image_ptr->height, image_ptr->width, CV_8UC3, image_ptr->data);
    cv::cvtColor(temp, image, cv::COLOR_BGR2RGB);

    // 构造输出路径
    fs::path output_path = output_dir / (input_path.stem().string() + ".jpg");

    // 将图像保存为JPG格式
    std::vector<int> params;
    params.push_back(cv::IMWRITE_JPEG_QUALITY);
    params.push_back(95); // you may need to adjust this value to achieve your size limit
    if (cv::imwrite(output_path.string(), image, params))
    {
      std::cout << "Successfully saved image: " << output_path << std::endl;
    }
    else
    {
      std::cerr << "Could not save image: " << output_path << std::endl;
      return EXIT_FAILURE;
    }

    // 记得释放内存
    LibRaw::dcraw_clear_mem(image_ptr);
  }
  else
  {
    std::cerr << "Could not make memory image from file: " << filePath << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int main()
{
  fs::path input_dir = "images";
  fs::path output_dir = "output";

  // 创建输出目录
  fs::create_directories(output_dir);

  for (const auto &entry : fs::directory_iterator(input_dir))
  {
    processFile(entry.path(), output_dir);
  }

  return EXIT_SUCCESS;
}
