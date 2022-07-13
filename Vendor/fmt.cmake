include(FetchContent)

FetchContent_Declare(
  fmt
  URL https://github.com/fmtlib/fmt/releases/download/9.0.0/fmt-9.0.0.zip
  URL_HASH SHA256=fc96dd2d2fdf2bded630787adba892c23cb9e35c6fd3273c136b0c57d4651ad6
  EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(fmt)
