#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <AprilTags/TagDetector.h>
#include <AprilTags/Tag36h11.h>

namespace py = pybind11;

py::list detect(const py::array_t<uint8_t> &image_nparray) {
  // Form Image - np.array to cv::Mat
  py::buffer_info buf = image_nparray.request();
  const cv::Mat image(buf.shape[0],
                      buf.shape[1],
                      CV_8UC1,
                      (unsigned char *) buf.ptr);

  // Extract tags
  AprilTags::AprilGridDetector detector;
  std::vector<AprilTags::TagDetection> tags = detector.extractTags(image);

  // Sort by tag_id (inorder)
  std::sort(tags.begin(),
            tags.end(),
            [](const AprilTags::TagDetection &a,
               const AprilTags::TagDetection &b) { return (a.id < b.id); });

  // Setup data
  const double min_border_dist = 4.0;
  const int img_rows = image.rows;
  const int img_cols = image.cols;
  py::list detections;

  for (const auto &tag : tags) {
    if (!tag.good) {
      continue;
    }

    for (int corner_idx = 0; corner_idx < 4; corner_idx++) {
      bool keep = false;
      const auto kp_x = tag.p[corner_idx].first;
      const auto kp_y = tag.p[corner_idx].second;
      keep |= kp_x < min_border_dist;
      keep |= kp_x > img_cols - min_border_dist;
      keep |= kp_y < min_border_dist;
      keep |= kp_y > img_rows - min_border_dist;
      if (keep) {
        continue;
      }

      py::list tag_data;
      tag_data.append(tag.id);
      tag_data.append(corner_idx);
      tag_data.append(kp_x);
      tag_data.append(kp_y);

      detections.append(tag_data);
    }
  }

  return detections;
}

PYBIND11_MODULE(apriltag_pybind, m) {
  m.doc() = "AprilTag Python Bindings";
  m.def("detect", &detect);
}
