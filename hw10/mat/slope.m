function m = slope(x1, x2, y1, y2, b)
if x1==x2
    m = (3*x1^2+b)/(2*y1);
else
    m = (y2-y1)/(x2-x1);
end
end