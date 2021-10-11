function [accuracy] = centroid(traindata, testdata)
  [n, m] = size(testdata);
  
  % Centroids on traindata
  c = zeros([10, m-1]);
  for i = 0 : 9
    idx = (traindata(:,end) == i);
    classi = traindata(idx,1:end-1);
    [numOfClassi, ~] = size(classi);
    
    c(i+1,:) = floor(sum(classi) / numOfClassi);
  end
  [clength, ~] = size(c);

  % Accuracy on testdata
  hit = 0;
  dist = zeros([clength, 1]);
  for i = 1 : n
    for j = 1 : clength
       dist(j, :) = eucdist(c(j,:),testdata(i,1:end-1));
    end
    [~, row] = min(min(dist,[],2));
    if eq(row-1,testdata(i, end))
      hit = hit + 1;  
    end
  end
  accuracy = (hit / n) * 100;
end
 