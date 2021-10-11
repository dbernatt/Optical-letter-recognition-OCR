function crossvalidation(val)
  
  traindata = dlmread('optdigits.tra', ',', 0, 0);
  %traindata= dlmread('optdigits.tes', ',', 0, 0);
  testdata = dlmread('optdigits.tra', ',', 0, 0);
  errors = [];
  n = rows(traindata);
  m = rows(testdata);
  
  traindata_slice = [];
  testdata_slice = [];
  
  jump = floor(n / val);

  k_avg_err = [];
  
  for k = 1 : 10
  
    for i = 0 : jump : n - jump
        aux = traindata;
        traindata_slice = aux(i+1:i+jump, :);
        aux(i+1:i+jump, :) = [];
        testdata_slice = aux;
        errors = [errors;knn(traindata_slice, testdata_slice, k)];
    end
    
    avg_error = sum(errors) / rows(errors);
    k_avg_err = [k_avg_err; floor(k), avg_error];
  end
   k_avg_err = sortrows(k_avg_err, [-2])
   opt_k = k_avg_err(1)
end
   
  
  
  
  
  
 
  