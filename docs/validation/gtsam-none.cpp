#include <gtsam_points/util/gtsam_migration.hpp>

bool absent_matrices(gtsam_points::OptionalMatrixType matrix = gtsam_points::NoneValue,
                     gtsam_points::OptionalMatrixVecType matrices = gtsam_points::NoneValue) {
  return !matrix && !matrices;
}

int main() {
#if GTSAM_VERSION_NUMERIC < 40300
  gtsam_points::optional<int> value = gtsam_points::NoneValue;
#else
  gtsam_points::optional<int> value = std::nullopt;
#endif
  if (value || !absent_matrices()) return 1;
  value = 42;
  if (!value || *value != 42) return 2;
  // Reset using the corresponding Boost/std sentinel.
#if GTSAM_VERSION_NUMERIC < 40300
  value = gtsam_points::NoneValue;
#else
  value = std::nullopt;
#endif
  if (value) return 3;
  gtsam::Matrix matrix(1, 1);
  std::vector<gtsam::Matrix> matrices;
#if GTSAM_VERSION_NUMERIC < 40300
  return absent_matrices(matrix, matrices) ? 4 : 0;
#else
  return absent_matrices(&matrix, &matrices) ? 4 : 0;
#endif
}
