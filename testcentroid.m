function testcentroid()
  
  traindata = dlmread('optdigits.tra', ',', 0, 0);
  testdata = dlmread('optdigits.tes', ',', 0, 0);
  train_accuracy = centroid(traindata, traindata)
  test_accuracy = centroid(traindata, testdata)
end