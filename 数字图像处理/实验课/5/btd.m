%巴特沃斯低通频域滤波
I=imread('D:\教学\数字图像处理\实验\2019实验安排\实验五\lena.jpg');
subplot(2,3,1),imshow(I),title('原始图像');
J1=imnoise(I,'gaussian',0,0.02);
      %对图像数据添加均值为0，方差为0.02的高斯噪声。
J2=imnoise(I,'salt & pepper',0.02);
      %对图像数据添加椒盐噪声。
subplot(2,3,2);
imshow(J1);
title('加入高斯白噪声所得图象');
subplot(2,3,3);
imshow(J2);
title('加入椒盐白噪声所得图象');
%F=double(I);                % 数据类型转换，MATLAB不支持图像的无符号整型的计算
G1=fft2(J1);                    % 傅立叶变换
G2=fft2(J2);
G1=fftshift(G1);                 % 转换数据矩阵
G2=fftshift(G2);
[M,N]=size(G1);
nn=2;                       % 二阶巴特沃斯(Butterworth)低通滤波器
d0=30;                      %截止频率为30
m=fix(M/2); n=fix(N/2);
for i=1:M
       for j=1:N
           d=sqrt((i-m)^2+(j-n)^2);
           h=1/(1+1*(d/d0)^(2*nn));         % 计算低通滤波器传递函数
           result1(i,j)=h*G1(i,j);
           result2(i,j)=h*G2(i,j);
       end
end
result1=ifftshift(result1);
result2=ifftshift(result2);
Y1=ifft2(result1);
Y2=ifft2(result2);
Y3=uint8(Y1);
Y4=uint8(Y2);
subplot(2,3,4),imshow(Y3),title('巴特沃斯低通滤波高斯噪声图像');
subplot(2,3,5),imshow(Y4),title('巴特沃斯低通滤波椒盐噪声图像');