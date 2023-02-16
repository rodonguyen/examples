/**
 * An example of using Convolutional Neural Network (CNN) for
 * solving Digit Recognizer problem from Kaggle website.
 *
 * The full description of a problem as well as datasets for training
 * and testing are available here https://www.kaggle.com/c/digit-recognizer
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 *
 * @author Daivik Nema
 */

// #define MLPACK_ENABLE_ANN_SERIALIZATION   // For model saving
#include <mlpack.hpp>
#include <sys/resource.h>     // For memory measurement
#include <fstream>            // For file write/read
#include <chrono>             // For time measurement
#include <sstream>            // For string formatting

#if ((ENS_VERSION_MAJOR < 2) || ((ENS_VERSION_MAJOR == 2) && (ENS_VERSION_MINOR < 13)))
  #error "need ensmallen version 2.13.0 or later"
#endif

using namespace arma;
using namespace mlpack;
using namespace std;


long getMemUsage() {
  struct rusage myusage;

  // Get usage and assign result to myusage
  getrusage(RUSAGE_SELF, &myusage);
  // getrusage(RUSAGE_CHILDREN, &myusage);

  return myusage.ru_maxrss;
}

void addRecord(string line) {
   // Create and open a text file
   ofstream myrecord("record.csv", std::ios_base::app);

   // Write to the file
   myrecord << line;

   // Close the file
   myrecord.close();
}

void addRecord(std::chrono::_V2::system_clock::time_point timeNow, 
               long memory, 
               string description) {
    // Create and open a text file
    ofstream myrecord("record.csv", std::ios_base::app);

    stringstream line;
    line << std::chrono::time_point_cast<std::chrono::milliseconds>(timeNow).time_since_epoch().count() 
          << ", " << std::to_string(memory) << ", " << description << "\n";
    //  line << std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(timeNow-timeStart).count()) << ", " << to_string(memory) << ", " << description << "\n";

    // Write to the file
    myrecord << line.str();

    // Close the file
    myrecord.close();
}

void addRecordToFile02(stringstream& line) {
    // Create and open a text file
    ofstream myrecord("record_summary.csv", std::ios_base::app);

    // Write to the file
    myrecord << line.str();

    // Close the file
    myrecord.close();
}


Row<size_t> getLabels(const mat& predOut)
{
  Row<size_t> predLabels(predOut.n_cols);
  for (uword i = 0; i < predOut.n_cols; ++i)
  {
    predLabels(i) = predOut.col(i).index_max();
  }
  return predLabels;
}

int main()
{
  // For Recording purpose
  addRecord("time(ms), memory(kB), description\n");
  auto time_00 = std::chrono::high_resolution_clock::now();
  long mem_usage_00 = getMemUsage();
  stringstream line;

  // Record
  auto t = std::chrono::time_point_cast<std::chrono::milliseconds>(time_00).time_since_epoch();
  line << t.count() << "\n";
  addRecord(line.str());
  addRecord(time_00, mem_usage_00, "Start..");

  // Dataset is randomly split into validation
  // and training parts with following ratio.
  constexpr double RATIO = 0.1;

  // Allow 60 passes over the training data, unless we are stopped early by
  // EarlyStopAtMinLoss.
  // const int EPOCHS = 60;
  const int EPOCHS = 10;

  // Number of data points in each iteration of SGD.
  const int BATCH_SIZE = 50;

  // Step size of the optimizer.
  const double STEP_SIZE = 1.2e-3;

  const int trainImagesPerLoad = 65;  // 1000 per file, minus 10% for testing 


  // Specify the NN model. NegativeLogLikelihood is the output layer that
  // is used for classification problem. RandomInitialization means that
  // initial weights are generated randomly in the interval from -1 to 1.
  FFN<NegativeLogLikelihood, RandomInitialization> model;

  // Specify the model architecture.
  // In this example, the CNN architecture is chosen similar to LeNet-5.
  // The architecture follows a Conv-ReLU-Pool-Conv-ReLU-Pool-Dense schema. We
  // have used leaky ReLU activation instead of vanilla ReLU. Standard
  // max-pooling has been used for pooling. The first convolution uses 6 filters
  // of size 5x5 (and a stride of 1). The second convolution uses 16 filters of
  // size 5x5 (stride = 1). The final dense layer is connected to a softmax to
  // ensure that we get a valid probability distribution over the output classes

  // Layers schema.
  // 28x28x1 --- conv (6 filters of size 5x5. stride = 1) ---> 24x24x6
  // 24x24x6 --------------- Leaky ReLU ---------------------> 24x24x6
  // 24x24x6 --- max pooling (over 2x2 fields. stride = 2) --> 12x12x6
  // 12x12x6 --- conv (16 filters of size 5x5. stride = 1) --> 8x8x16
  // 8x8x16  --------------- Leaky ReLU ---------------------> 8x8x16
  // 8x8x16  --- max pooling (over 2x2 fields. stride = 2) --> 4x4x16
  // 4x4x16  ------------------- Dense ----------------------> 10

  // Add the first convolution layer.
  model.Add<Convolution>(6,  // Number of output activation maps.
                         5,  // Filter width.
                         5,  // Filter height.
                         1,  // Stride along width.
                         1,  // Stride along height.
                         0,  // Padding width.
                         0   // Padding height.
  );

  // Add first ReLU.
  model.Add<LeakyReLU>();

  // Add first pooling layer. Pools over 2x2 fields in the input.
  model.Add<MaxPooling>(2, // Width of field.
                        2, // Height of field.
                        2, // Stride along width.
                        2, // Stride along height.
                        true);

  // Add the second convolution layer.
  model.Add<Convolution>(16, // Number of output activation maps.
                         5,  // Filter width.
                         5,  // Filter height.
                         1,  // Stride along width.
                         1,  // Stride along height.
                         0,  // Padding width.
                         0   // Padding height.
  );

  // Add the second ReLU.
  model.Add<LeakyReLU>();

  // Add the second pooling layer.
  model.Add<MaxPooling>(2, 2, 2, 2, true);

  // Add the final dense layer.
  model.Add<Linear>(10);
  model.Add<LogSoftMax>();

  model.InputDimensions() = vector<size_t>({ 28, 28 });


  cout << "Start training ..." << endl;

  // Set parameters for the Adam optimizer.
  ens::Adam optimizer(
      STEP_SIZE,  // Step size of the optimizer.
      BATCH_SIZE, // Batch size. Number of data points that are used in each
                  // iteration.
      0.9,        // Exponential decay rate for the first moment estimates.
      0.999, // Exponential decay rate for the weighted infinity norm estimates.
      1e-8,  // Value used to initialise the mean squared gradient parameter.
      EPOCHS * trainImagesPerLoad, // Max number of iterations.
      1e-8,           // Tolerance.
      true);

  // Record
  auto time_01 = std::chrono::high_resolution_clock::now();
  long mem_usage_01 = getMemUsage();
  addRecord(time_01, mem_usage_01, "Defined model");


  // Labeled dataset that contains data for training is loaded from CSV file.
  // Rows represent features, columns represent data points.
  mat dataset;



  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  int totalLoadNum = 28;
  for (int loadNum = 1; loadNum <= totalLoadNum; loadNum++) {
    


    // Modified from https://www.techiedelight.com/add-leading-zeros-to-string-in-cpp/
    size_t n = 3;
    string loadNumStr = to_string(loadNum);
    int precision = n - min(n, loadNumStr.size());
    loadNumStr.insert(0, precision, '0');

    string dataset_filename = "../data/mnist_train_split/mnist_train_2000_" + to_string(totalLoadNum) + '_' + loadNumStr + ".csv";
    cout << "Reading data from '" + dataset_filename + "'" << endl;

    // The original file can be downloaded from
    // https://www.kaggle.com/c/digit-recognizer/data
    data::Load(dataset_filename, dataset, true);

    // Record
    time_01 = std::chrono::high_resolution_clock::now();
    mem_usage_01 = getMemUsage();
    addRecord(time_01, mem_usage_01, "Loaded train data");

    // Split the dataset into training and validation sets.
    mat train, valid;
    data::Split(dataset, train, valid, RATIO, false);

    // The train and valid datasets contain both - the features as well as the
    // class labels. Split these into separate mats.
    const mat trainX = train.submat(1, 0, train.n_rows - 1, train.n_cols - 1) /
        256.0;
    const mat validX = valid.submat(1, 0, valid.n_rows - 1, valid.n_cols - 1) /
        256.0;

    // Labels should specify the class of a data point and be in the interval [0,
    // numClasses).

    // Create labels for training and validatiion datasets.
    const mat trainY = train.row(0);
    const mat validY = valid.row(0);

    // Record
    time_01 = std::chrono::high_resolution_clock::now();
    mem_usage_01 = getMemUsage();
    addRecord(time_01, mem_usage_01, "Formatted data");



    // Train the CNN model. If this is the first iteration, weights are
    // randomly initialized between -1 and 1. Otherwise, the values of weights
    // from the previous iteration are used.
    model.Train(trainX,
                trainY,
                optimizer,
                ens::PrintLoss(),
                ens::ProgressBar(),
                // Stop the training using Early Stop at min loss.
                ens::EarlyStopAtMinLoss(
                    [&](const arma::mat& /* param */)
                    {
                      double validationLoss = model.Evaluate(validX, validY);
                      cout << "Validation loss: " << validationLoss << "."
                          << endl;
                      return validationLoss;
                    }));
  }
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////
  
  // Record
  time_01 = std::chrono::high_resolution_clock::now();
  long mem_usage_finished_training = getMemUsage();
  addRecord(time_01, mem_usage_finished_training, "Finished training");

  cout << "Predicting on test set..." << endl;

  // Get predictions on test data points.
  // The original file could be download from
  // https://www.kaggle.com/c/digit-recognizer/data
  data::Load("../data/mnist_test_1000.csv", dataset, true);
  const mat testX = dataset.submat(1, 0, dataset.n_rows - 1, dataset.n_cols - 1)
      / 256.0;
  const mat testY = dataset.row(0);

    // Record
  time_01 = std::chrono::high_resolution_clock::now();
  long mem_usage_02 = getMemUsage();
  addRecord(time_01, mem_usage_02, "Loaded and formatted test data");


  mat predOut;
  model.Predict(testX, predOut);
  // Calculate accuracy on test data points.
  Row<size_t> predLabels = getLabels(predOut);
  double testAccuracy =
      accu(predLabels == testY) / (double) testY.n_elem * 100;

  // Record
  time_01 = std::chrono::high_resolution_clock::now();
  mem_usage_01 = getMemUsage();
  addRecord(time_01, mem_usage_01, "Predicted test data");
  addRecord("\n\n");

  cout << "Accuracy: test = " << testAccuracy << "%" << endl;

  // cout << "Saving predicted labels to \"results.csv.\"..." << endl;
  // Saving results into Kaggle compatible CSV file.
  // predLabels.save("results.csv", arma::csv_ascii);


  cout << "Finished" << endl;
  line.str(std::string());
  line  << totalLoadNum << ", " 
        << to_string(std::chrono::duration_cast<std::chrono::milliseconds>(time_01-time_00).count() / 1000) << ", " 
        << to_string(mem_usage_finished_training) << ", " 
        << to_string(mem_usage_01) << ", " 
        << testAccuracy << "%\n" ;
  addRecordToFile02(line);

}
