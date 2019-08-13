% src = '0.jpg';
% img = imread(src);
% img = rgb2gray(img);

% % cut as stripes
% [rows, cols] = size(img);
% line = 19;                          % 0 has 16 rows and 1-3 has 19 rows
% space = (rows-80*line)/(line-1);    % empty spaces in between

% src 1-3 needs cut off head and tail
src = '3.jpg';
img = imread(src);
img = rgb2gray(img);
img = img(205:3182, :);

% cut as stripes
[rows, cols] = size(img);
line = 19;                          % 0 has 16 rows and 1-3 has 19 rows
space = 81;                         % empty spaces in between

row = 1;
i = 55;                             % change according to pic
for num = 1 : line
    tmp = img(row:row+79, 1:cols);
    filename = "stripe/img_" + int2str(i) + ".png";
    imwrite(tmp, filename);
    row = row + 80 + 81;
    i = i + 1;
end
