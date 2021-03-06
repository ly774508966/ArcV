#pragma once

#ifndef ARCV_MATRIX_HPP
#define ARCV_MATRIX_HPP

#include <cmath>
#include <vector>
#include <cstdint>

enum Colorspace { ARCV_COLORSPACE_GRAY = 0,
                  ARCV_COLORSPACE_GRAY_ALPHA,
                  ARCV_COLORSPACE_RGB,
                  ARCV_COLORSPACE_RGBA,
                  ARCV_COLORSPACE_HSV };

namespace Arcv {

template <typename T = float>
class Matrix {
public:
  Matrix(unsigned int width,
         unsigned int height)
    : width{ width }, height{ height }, data(width * height) {}

  Matrix(unsigned int width,
         unsigned int height,
         uint8_t channels,
         uint8_t bitDepth,
         Colorspace colorspace)
    : width{ width },
      height{ height },
      channels{ channels },
      imgBitDepth{ bitDepth },
      colorspace{ colorspace },
      data(width * height * channels) {}

  template <typename TI> Matrix(const Matrix<TI>& mat);

  Matrix(const std::initializer_list<std::initializer_list<T>>& list);

  const unsigned int getWidth() const { return width; }
  const unsigned int getHeight() const { return height; }
  const uint8_t getImgBitDepth() const { return imgBitDepth; }
  const uint8_t getChannels() const { return channels; }
  const Colorspace getColorspace() const { return colorspace; }
  const std::vector<T>& getData() const { return data; }
  std::vector<T>& getData() { return data; }

  void setColorspace(Colorspace colorspace) { this->colorspace = colorspace; }

  void convolve(const Matrix<float>& convMat);

  Matrix& operator+(const Matrix& mat) { return *this += mat; }
  Matrix& operator+(float val) { return *this += val; }
  Matrix& operator-(const Matrix& mat) { return *this -= mat; }
  Matrix& operator-(float val) { return *this -= val; }
  Matrix& operator*(const Matrix& mat) { return *this *= mat; }
  Matrix& operator*(float val) { return *this *= val; }
  Matrix& operator/(const Matrix& mat) { return *this /= mat; }
  Matrix& operator/(float val) { return *this /= val; }
  Matrix& operator+=(const Matrix& mat);
  Matrix& operator+=(float val);
  Matrix& operator-=(const Matrix& mat);
  Matrix& operator-=(float val);
  Matrix& operator*=(const Matrix& mat);
  Matrix& operator*=(float val);
  Matrix& operator/=(const Matrix& mat);
  Matrix& operator/=(float val);
  template <typename TI> Matrix operator=(const Matrix<TI>& mat) { return Matrix<T>(mat); }
  T& operator()(unsigned int widthIndex, unsigned int heightIndex) { return data[heightIndex * width + widthIndex]; }
  const T& operator[](unsigned int index) const { return data[index]; }
  T& operator[](unsigned int index) { return data[index]; } // Implement Pixel class to return an instance?

private:
  unsigned int width, height;
  uint8_t channels, imgBitDepth;    // TODO: channels, depth & colorspace have nothing to do with general matrices
  Colorspace colorspace;
  std::vector<T> data;
};

template <> void Matrix<>::convolve(const Matrix<float>& convMat);

using Mat = Matrix<>;

} // namespace Arcv

#include "ArcV/Math/Matrix.inl"

#endif // ARCV_MATRIX_HPP
