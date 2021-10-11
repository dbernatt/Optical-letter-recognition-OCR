function testlinearregression()
  
  traindata = dlmread('optdigits.tra', ',', 0, 0);
  testdata = dlmread('optdigits.tes', ',', 0, 0);
  
  train_accuracy = linearregression(traindata, traindata, 8, 3)
  test_accruacy = linearregression(traindata, testdata, 8, 3)
  
end