clear;
clc;
data=cell2mat(struct2cell(load('data_programming_1.mat')));
x = data.X;
y= data.Y;
[row,col]=size(x);

%h(w) = w0 + w1*x1 + w2*x2 + w3*x3 + w4*x4 + w5*x5 + w6*x6
%       w7*x1*x1 + w8*x1*x2 + w9*x1*x3 + w10*x1*x4 +w11*x1*x5 + w12*x1*x6
%       w13*x2*x2 + w14*x2*x3 + w15*x2*x4 + w16*x2*x5 +w17*x2*x6
%       w18*x3*x3 + w19*x3*x4 + w20*x3*x5 + w21*x3*x6
%       w22*x4*x4 + w23*x4*x5 + w24*x4*x6
%       w25*x5*x5 + w26*x5*x6
%       w27*x6*x6 

feature_num = 28;

x = [ones(row,1),x];
for i = 2:7
    for j = i:7
        x = [x,x(:,i).* x(:,j)];
    end
end

%
for i = 1:feature_num
    x(:,i) = x(:,i)/max(x(:,i));
end

% %
% add_col = 6;
w_result = zeros(feature_num,1);
for k = 1:5
%
    p = randperm(9000);
    row_train = row*2/3;
    row_test = row - row_train;
    i=1;
    x_train = zeros(row_train,feature_num);
    y_train = zeros(row_train,1);
    x_test = zeros(row-row_train,feature_num);
    y_test = zeros(row-row_train,1);

    while(i <= row_train)
    x_train(i,:) = x(p(1,i),:);
    y_train(i,:) = y(p(1,i),:);
    i = i+1;
    end
    while(i <= row)
        x_test(i-row_train,:) = x(p(1,i),:);
        y_test(i-row_train,:) = y(p(1,i),:);
        i = i+1;
    end

%
    delta = 0.001;
    w = rand(feature_num,1);
    w_new = zeros(feature_num,1);
    num_start = 12000;
    num = num_start;
    w_record = zeros(num,feature_num);
    while(num)
        for i=1:feature_num
            g = x_train * w;
            h = 1 ./(1+exp(-g));
            xj = x_train(:,i);
            xj = xj';
            w_new(i,1) = w(i,1) - delta/row_train* xj * (h-y_train);
        end
    
        w = w_new;
        num = num -1;
        w_record(num_start-num,:) = w;
    end

    z = [1:num_start];
    scatter(z,w_record(:,10));
    w_result = (w_result + w)/2;
end
%
correct_num = 0;
for i = 1:row_test
    x_test_i = x_test(i,:);
    y_test_i = y_test(i,:);
    prediction_result = 1 / (1+exp(-w_result'*x_test_i'));
    if prediction_result > 0.5 && y_test_i == 1
        correct_num = correct_num + 1;
    end
    if prediction_result <= 0.5 && y_test_i == 0
        correct_num = correct_num +1;
    end
end
rate = correct_num / row_test 

%     
%     correct_num = 0;
%     for i = 1:row_train
%         x_test_i = x_train(i,:);
%         y_test_i = y_train(i,:);
%         prediction_result = 1 / (1+exp(-w_result'*x_test_i'));
%         if prediction_result > 0.5 && y_test_i == 1
%             correct_num = correct_num + 1;
%         end
%         if prediction_result <= 0.5 && y_test_i == 0
%             correct_num = correct_num +1;
%         end
%     end   
% rate = correct_num / row_train