% Load image and prepare grayscale
img = imread('nada.jpg');

if size(img, 3) == 3
    img_gray = rgb2gray(img);
else
    img_gray = img;
end
% Figure 1: Original + Grayscale + Contrast Stretching + Gamma Correction
stretched_img = imadjust(img_gray, [0.2, 0.6], [0.0, 1.0]);
gamma_value = 0.5;
gamma_corrected = imadjust(img_gray, [], [], gamma_value);

figure;
subplot(4,2,1); imshow(img); title('Original Image');
subplot(4,2,2); imhist(rgb2gray(img)); title('Histogram - Original');

subplot(4,2,3); imshow(img_gray); title('Grayscale Image');
subplot(4,2,4); imhist(img_gray); title('Histogram - Grayscale');

subplot(4,2,5); imshow(stretched_img); title('Contrast Stretched');
subplot(4,2,6); imhist(stretched_img); title('Histogram - Stretched');

subplot(4,2,7); imshow(gamma_corrected); title(['Gamma Correction (\gamma = ' num2str(gamma_value) ')']);
subplot(4,2,8); imhist(gamma_corrected); title('Histogram - Gamma');

% Figure 2: Noise + Average Filters
inputImage = imnoise(img_gray, 'salt & pepper', 0.03);
filterSize = 3;

averagedImage = imfilter(inputImage, fspecial('average', [filterSize, filterSize]));

weightFilter = [1, 2, 1; 2, 4, 2; 1, 2, 1];
weightFilter = weightFilter / sum(weightFilter(:));
weightedAveragedImage = imfilter(inputImage, weightFilter);

figure;
subplot(3,2,1); imshow(inputImage); title('Noisy Image');
subplot(3,2,2); imhist(inputImage); title('Histogram - Noisy');

subplot(3,2,3); imshow(averagedImage); title('Average"mean" Filter');
subplot(3,2,4); imhist(averagedImage); title('Histogram - Average"mean"');

subplot(3,2,5); imshow(weightedAveragedImage); title('Weighted Average');
subplot(3,2,6); imhist(weightedAveragedImage); title('Histogram - Weighted');

% Figure 3: Min, Max, Median
minFilteredImage = ordfilt2(inputImage, 1, ones(filterSize));
maxFilteredImage = ordfilt2(inputImage, filterSize^2, ones(filterSize));
medianFilteredImage = medfilt2(inputImage, [filterSize, filterSize]);

figure;
subplot(3,2,1); imshow(minFilteredImage); title('Minimum Filter');
subplot(3,2,2); imhist(minFilteredImage); title('Histogram - Minimum');

subplot(3,2,3); imshow(maxFilteredImage); title('Maximum Filter');
subplot(3,2,4); imhist(maxFilteredImage); title('Histogram - Maximum');

subplot(3,2,5); imshow(medianFilteredImage); title('Median Filter');
subplot(3,2,6); imhist(medianFilteredImage); title('Histogram - Median');

% Figure 4: Log, Negative, Threshold
img_double = im2double(img_gray);
log_transformed = uint8(255 * mat2gray(log(1 + img_double)));

negative_img = imcomplement(img_gray);

threshold_value = 100;
binary_img = img_gray > threshold_value;

figure;
subplot(3,2,1); imshow(log_transformed); title('Log Transformed');
subplot(3,2,2); imhist(log_transformed); title('Histogram - Log');

subplot(3,2,3); imshow(negative_img); title('Negative Image');
subplot(3,2,4); imhist(negative_img); title('Histogram - Negative');

subplot(3,2,5); imshow(binary_img); title(['Threshold > ' num2str(threshold_value)]);
subplot(3,2,6); imhist(uint8(binary_img)*255); title('Histogram - Threshold');
