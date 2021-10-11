function testknn(k)

  traindata = dlmread('optdigits.tra', ',', 0, 0);
  testdata = dlmread('optdigits.tes', ',', 0, 0);
  train_accuracy = knn(traindata, traindata, k)
  test_accuracy = knn(traindata, testdata, k)
end
 