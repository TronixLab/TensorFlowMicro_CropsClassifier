#include <MicroTFLite.h>
#include "NeuralNetworkClassifier.h"
#include "MinMaxScaler.h"

// Create scaler instance
MinMaxScaler scaler;

// Array to hold scaled features
float features_scaled[MinMaxScaler::n_features];

// Define an array for class labels
const char* CROPS[] = { "apple", "banana", "blackgram", "chickpea", "coconut",
                        "coffee", "cotton", "grapes", "jute", "kidneybeans",
                        "lentil", "maize", "mango", "mothbeans", "mungbean",
                        "muskmelon", "orange", "papaya", "pigeonpeas", "pomegranate",
                        "rice", "watermelon" };

// Calculate the number of classes
#define NUM_CLASSES (sizeof(CROPS) / sizeof(CROPS[0]))

// Define the tensor arena size and create a tensor arena buffer
constexpr int kTensorArenaSize = 50 * 1024;
alignas(16) uint8_t tensor_arena[kTensorArenaSize];

void setup() {
  Serial.begin(9600);

  // Initialize the model
  if (!ModelInit(NeuralNetworkClassifier_quant, tensor_arena, kTensorArenaSize)) {
    Serial.println("Model initialization failed!");
    while (true)
      ;
  }
  Serial.println("Model initialization done.");

  // Print model metadata
  ModelPrintMetadata();

  // Print input and output tensor dimensions
  ModelPrintInputTensorDimensions();
  ModelPrintOutputTensorDimensions();
}

void loop() {
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    float features[MinMaxScaler::n_features];
    int featureIndex = 0;
    int lastIndex = 0;
    line.trim();

    while (featureIndex < MinMaxScaler::n_features) {
      int commaIndex = line.indexOf(',', lastIndex);
      String value;
      if (commaIndex == -1) {
        value = line.substring(lastIndex);
      } else {
        value = line.substring(lastIndex, commaIndex);
      }
      features[featureIndex] = value.toFloat();
      featureIndex++;
      if (commaIndex == -1) break;
      lastIndex = commaIndex + 1;
    }

    // Scale features
    scaler.transform(features, features_scaled);

    // Set the scaled features as input to the model
    ModelSetInput(features_scaled[0], 0);
    ModelSetInput(features_scaled[1], 1);
    ModelSetInput(features_scaled[2], 2);
    ModelSetInput(features_scaled[3], 3);
    ModelSetInput(features_scaled[4], 4);
    ModelSetInput(features_scaled[5], 5);
    ModelSetInput(features_scaled[6], 6);

    // Run inference
    if (!ModelRunInference()) {
      Serial.println("RunInference Failed!");
      return;
    }

    // Get the output and print the results
    for (int i = 0; i < NUM_CLASSES; i++) {
      Serial.print(CROPS[i]);
      Serial.print(": ");
      Serial.print(ModelGetOutput(i) * 100, 2);
      Serial.println("%");
    }
    Serial.println();
  }
  delay(100);
}