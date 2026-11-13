#ifndef MINMAXSCALER_H
#define MINMAXSCALER_H

class MinMaxScaler {
public:
	static constexpr int n_features = 7;

	// Min and max values for each feature (pre-computed from training data)
	const float scaler_min[7] = { 0.000000f, 5.000000f, 5.000000f, 8.825675f, 14.258040f, 3.504752f, 20.211267f };
	const float scaler_max[7] = { 140.000000f, 145.000000f, 205.000000f, 43.675493f, 99.981876f, 9.935091f, 298.560117f };

	// Scale input array in-place
	void transform(float* X, float* X_scaled) const {
		for (int i = 0; i < n_features; ++i) {
			X_scaled[i] = (X[i] - scaler_min[i]) / (scaler_max[i] - scaler_min[i]);
		}
	}

	// Inverse scale input array in-place
	void inverse_transform(float* X_scaled, float* X) const {
		for (int i = 0; i < n_features; ++i) {
			X[i] = X_scaled[i] * (scaler_max[i] - scaler_min[i]) + scaler_min[i];
		}
	}
};

#endif  // MINMAXSCALER_H