function [r, m] = div(a, b)
r = floor(a/b);
m = mod(a, b);
disp([r m])
end