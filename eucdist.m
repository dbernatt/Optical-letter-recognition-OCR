function [res] = eucdist(x,z)
  res = sum((x - z) .^ 2, 2);
end