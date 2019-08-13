src = "stripe/img_63.png";
img = imread(src);

% for 1-16
% [~, cols] = size(img);
% img = img(:, 2:cols-7);

% manually set division
cut = 1:41:2078;
cut(2:50) = cut(2:50) + 1;
cut(7:50) = cut(7:50) + 1;
cut(9:50) = cut(9:50) + 1;
cut(13:50) = cut(13:50) + 1;
cut(14:50) = cut(14:50) + 1;
cut(17:50) = cut(17:50) + 1;
cut(19:50) = cut(19:50) + 1;
cut(21:50) = cut(21:50) + 1;
cut(25:50) = cut(25:50) + 1;
cut(29:50) = cut(29:50) + 1;
cut(30:50) = cut(30:50) + 1;
cut(33:50) = cut(33:50) + 1;
cut(39:50) = cut(39:50) + 1;
cut(41:50) = cut(41:50) + 1;
cut(42:50) = cut(42:50) + 1;
cut(45:50) = cut(45:50) + 1;
cut(51) = cols;

% store path
org_path = "stripe/img_";
path = "img/";

% imshow(img);
% hold on;
% for i = 1:50
%     t = cut(i); 
%     line([t, t], [1, 80], 'Color', 'r', 'LineWidth', 1);
% end

% tmp = img(:, cut(1):cut(1+1));  
% imshow(tmp);

for num = 17:63
    src = org_path + int2str(num) + ".png";
    img = imread(src);
    % for 17-63
    img = img(:, 232:2301);
    [rows, cols] = size(img);   
    unit = cols/50;
    for i = 1:50
        t = cut(i); % line([t, t], [1, 80], 'Color', 'r', 'LineWidth', 1);
        tmp = img(:, cut(i):cut(i+1));  % imshow(tmp);
        filename = path + int2str(num) + "_" + int2str(i) + ".png";
        imwrite(tmp, filename);
    end

end

