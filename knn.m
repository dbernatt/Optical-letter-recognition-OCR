function [accuracy] = knn(traindata, testdata, k)
  [m, ~] = size(traindata);
  [n, ~] = size(testdata);
  hit = 0;
  for x = 1:n
    d = [];
    for i = 1:m
        d(i, :) = [ eucdist(traindata(i, 1:end-1), testdata(x, 1:end-1)), traindata(i, end) ];
    end
    d = sortrows(d, [1]);
    neighbors = d(1:k,:);
    votes = [0:9;zeros(1,10)]';
    testlabel = testdata(x, end);
    [numOfNeighbours, ~] = size(neighbors);
    for y = 1: numOfNeighbours
        trainlabel = neighbors(y, end) + 1;
        votes(trainlabel, 2) = votes(trainlabel, 2) + 1;    
    end
    
    votes = sortrows(votes, [-2]);

    if eq(votes(1), testlabel)
      hit = hit + 1; 
    end
  end
  accuracy = (hit / n) * 100;
end