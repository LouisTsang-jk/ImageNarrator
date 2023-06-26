# ImageNarrator

![screen-recording](./assets/screen-recording.gif)
## Description

ImageNarrator is a versatile tool for image processing and descriptive analysis. This application leverages OpenCV and LibRaw for efficient conversion of raw images to JPEG format, and utilizes CLIP for generating meaningful textual descriptions of images. It is ideal for rapid and high-quality image interpretation.

## Installation

This project requires Python 3.7 or later. We recommend installing the necessary dependencies in a virtual environment to avoid conflicting with your system Python.

To install the dependencies, navigate to the root of the project directory and run:

```bash
python3 -m venv env  # create a virtual environment
source env/bin/activate  # activate the virtual environment
pip install -r requirements.txt  # install the dependencies
```

## Usage

1. Place your RAW format image files into the 'images' directory.

2. Update the 'custom.json' file to specify the categories you are interested in. Please note, categories should be described in English.

3. Run the main program using the command `build sh`.

The processed images will be saved in the 'output' directory, along with a text file containing their descriptions.

## License

This project is licensed under the terms of the MIT License.

## Acknowledgement

[OpenCLIP](https://github.com/mlfoundations/open_clip)  
[OpenCV](https://github.com/opencv/opencv)   
[LibRaw](https://github.com/LibRaw/LibRaw)   
