src = 'img.png';
img = imread(src);
img = rgb2gray(img);
img = img(4:1363, 1:2085);

% cut as stripes
[rows, ~, c] = size(img);
rstep = rows / 17;
i = 1;
for row = 1 : rstep : rows
    tmp = img(row:row+rstep - 1, 1:2085);
    filename = "pic/src/img_" + int2str(i) + ".png";
    if mod(i, 2) == 1
        imwrite(tmp, filename);
    end
    i = i + 1;
end

% cut as individuals
columns = 2085;
cstep = 2085/50;
cut = 1 : cstep : columns;
cut(11:50) = cut(11:50) - 1;
cut(27:50) = cut(27:50) - 2;
cut(31:50) = cut(31:50) - 1;
cut(33:50) = cut(33:50) - 1;
cut(42:50) = cut(42:50) - 1;
[~, len] = size(cut);
cut(51) = 2086;  % add an ending

count = 1;
for num = 1:2:17
    src = "img_" + int2str(num) + ".png";
    img = imread(src);
    for i = 1:len
        s = round(cut(i));
        t = round(cut(i+1)) - 1;
        %line([t, t], [1, 80], 'Color', 'r', 'LineWidth', 1);
        tmp = img(1:80, s:t);
        filename = "pic/p" + int2str(count) + ".png";
        imwrite(tmp, filename);
        count = count + 1;
    end
end





