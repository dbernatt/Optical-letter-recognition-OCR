function [accuracy] = linearregression_gradient(traindata, testdata, x, y)
  lambda = rand();
  fprintf('lambda = %f\n', lambda);
  hit = 0;
  
  idx =(traindata(:,end) == x | traindata(:,end) == y);
  X = traindata(idx,1:end-1);
  Y = traindata(idx,end);
  Y(Y == x) = -1;
  Y(Y == y) = 1;
  X = [X ones(size(X,1), 1)];
  [~, colsX] = size(X);
  I = eye(colsX);
  w = (X'*X + lambda*I)\(X'*Y)
  [row, col] = size(w)
  [rowX, colX] = size(X)
  %b = w(end,:);
  w*X
  return
  learning_rate = 1;
  w_next = -2*learning_rate*w'*X*(w'*X - Y)
  return
  for i = 1 : 10
     
      w_next = w_next - -2*learning_rate*w'*X*(w'*X - Y);
      
  end
  
  idx = (testdata(:,end) == x | testdata(:,end) == y);
  XTest = testdata(idx, 1:end-1);
  XTestLabel = testdata(idx, end);
  XTest = [XTest ones(size(XTest,1), 1)];
  [rowsXTest, ~] = size(XTest);

  
  for i = 1 : rowsXTest
    
    
      if eq(sign(dot(w',XTest(i,:))), 1)
        szam = y;
      else
        szam = x;
      end
      
      if eq(szam, XTestLabel(i,1))
        hit = hit + 1;
      end
        
      %if eq(sign(dot(w',XTest(i,:))), Y(i,1))
      %  ++hit;
      %end
  end
  accuracy =  hit / rowsXTest;
end