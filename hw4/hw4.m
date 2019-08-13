b = 2;
index = zeros(1, 28);
b2 = zeros(1, 28);
for i=1:28
    index(i) = i;
    b2(i) = b;
    b = b * 2;
    b = mod(b, 29);
end

% a = 7;
% for i = 1:100
%     a = a*7;
%     disp(mod(a, 1000));
% end