function combMat = allcombs(varargin)
  sizeVec = cellfun('prodofsize', varargin);
  indices = fliplr(arrayfun(@(n) {1:n}, sizeVec));
  [indices{:}] = ndgrid(indices{:});
  combMat = cellfun(@(c,i) {reshape(c(i(:)), [], 1)}, ...
                    varargin, fliplr(indices));
  combMat = [combMat{:}];
end