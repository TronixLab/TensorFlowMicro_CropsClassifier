# Crop Recommendation on a Microcontroller

This project demonstrates how a small machine-learning model can recommend a
crop from soil and weather measurements. The model runs on an Arduino-compatible
microcontroller and receives its measurements as text over the USB serial
connection.

**This is a tabular-data project.** Its recommendation is a prediction from the data
used to train the model, not a guarantee that a crop will grow well in a
particular field.

## What the project does

The supplied dataset contains 2,200 examples. Each example has seven input
measurements and a crop label. A Keras neural network is trained to choose
among 22 crop labels. The training notebook also converts the model to a
smaller TensorFlow Lite format for microcontroller use.

On the microcontroller, the program:

1. Starts the model.
2. Reads seven comma-separated numbers from the serial connection.
3. Scales the numbers in the same way as the training data.
4. Runs the model and prints a score for each crop.

## Project map

| File or folder | What it is for |
| --- | --- |
| `CropsRecommendation_TFLite_Classification.ipynb` | Main, step-by-step notebook for exploring the data, training and evaluating the model, and preparing it for the board. |
| `CropsRecommendation_TFLite_Classification.html` | Browser-friendly, read-only rendering of the notebook. |
| `crop_recommendation.csv` | The example data used to train the model. |
| `models/` | Saved Keras and TensorFlow Lite models, plus C/C++ model data generated for embedding. |
| `TFLite_Arduino_Keras_CropReco/TFLite_Arduino_Keras_CropReco.ino` | Arduino program that starts the model and handles serial input and output. |
| `TFLite_Arduino_Keras_CropReco/MinMaxScaler.h` | Feature-scaling values used by the Arduino program. |
| `TFLite_Arduino_Keras_CropReco/NeuralNetworkClassifier.h` | Quantized model embedded as a C array for the Arduino program. |
| `TFLite_Arduino_Keras_CropReco/build/` | Previously generated Arduino build files; these are not needed to read the project. |

## Try the notebook

The notebook is the best place to begin if you want to understand how the
recommendation model was made. It reads `crop_recommendation.csv` from the
repository's top-level folder, explores and prepares the data, trains and
evaluates a neural network, and shows how to export the model.

To run it, use a Python environment with Jupyter, TensorFlow/Keras, pandas,
NumPy, scikit-learn, Matplotlib, Seaborn, and emlearn installed. Then open
`CropsRecommendation_TFLite_Classification.ipynb` in Jupyter and run its cells
in order. The repository does not include a pinned Python dependency list, so
the exact setup may depend on your Python version.

The notebook saves model files under `models/`. Re-running its export steps may
replace those files.

## Run the Arduino example

The checked-in Arduino build files were produced for an **Arduino Nano 33 BLE**.
The sketch uses the `MicroTFLite` Arduino library; other boards may require
changes and are not confirmed by the included build files.

1. Open `TFLite_Arduino_Keras_CropReco/TFLite_Arduino_Keras_CropReco.ino` in
   the Arduino IDE.
2. Select and configure an Arduino Nano 33 BLE board, and make sure the
   `MicroTFLite` library is available to the IDE.
3. Upload the sketch to the board.
4. Open the IDE's Serial Monitor at **9600 baud** and send one line containing
   seven comma-separated numbers.

The values must be in this order:

| Position | Measurement |
| --- | --- |
| 1 | Nitrogen (`N`) |
| 2 | Phosphorus (`P`) |
| 3 | Potassium (`K`) |
| 4 | Temperature |
| 5 | Humidity |
| 6 | Soil pH |
| 7 | Rainfall |

For example, the following line is an example row from the supplied dataset:

```text
90,42,43,20.87974371,82.00274423,6.502985292000001,202.9355362
```

Send values in the same units and order as the training data. The sketch prints
a percentage-style score for each crop; a larger score means the model favors
that crop more for the supplied measurements. The program prints all crop
scores rather than selecting only one. It expects exactly seven numeric values
per line; it does not check whether the measurements are valid or realistic.

## Suggested reading order

1. Read this page for the project overview and how to try it.
2. Open the notebook to follow the data preparation, training, and conversion
   steps. Use the HTML file if you only want to read it.
3. Look at `crop_recommendation.csv` to see the training data and feature names.
4. Read the Arduino sketch to see how measurements are received and predictions
   are printed.
5. Read `MinMaxScaler.h` and the model header to see the pieces the sketch uses
   for scaling and inference.
