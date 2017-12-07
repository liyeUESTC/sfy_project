clear;
clc;
data=cell2mat(struct2cell(load('data_programming_1.mat')));
x = data.X;
y= data.Y;
[row,col]=size(x);

%h(w) = w0 + w1*x1 + w2*x2 + w3*x3 + w4*x4 + w5*x5 + w6*x6
x = [ones(row,1),x];

%
x(:,1) = x(:,1)/max(x(:,1));
x(:,2) = x(:,2)/max(x(:,2));
x(:,3) = x(:,3)/max(x(:,3));
x(:,4) = x(:,4)/max(x(:,4));
x(:,5) = x(:,5)/max(x(:,5));
x(:,6) = x(:,6)/max(x(:,6));
x(:,7) = x(:,7)/max(x(:,7));

w_result = zeros(7,1);
for k = 1:5
%
    p = randperm(9000);
    row_train = row*2/3;
    row_test = row - row_train;
    i=1;
    x_train = zeros(row_train,col+1);
    y_train = zeros(row_train,1);
    x_test = zeros(row-row_train,col+1);
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
    w = rand(col+1,1);
    w_new = zeros(col+1,1);
    num_start = 10000;
    num = num_start;
    w_record = zeros(num,col+1);
    while(num)
        for i=1:7
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
    scatter(z,w_record(:,7));
    w_result = (w_result + w)/2;
end
%
%     correct_num = 0;
%     for i = 1:row_test
%         x_test_i = x_test(i,:);
%         y_test_i = y_test(i,:);
%         prediction_result = 1 / (1+exp(-w_result'*x_test_i'));
%         if prediction_result > 0.5 && y_test_i == 1
%             correct_num = correct_num + 1;
%         end
%         if prediction_result <= 0.5 && y_test_i == 0
%             correct_num = correct_num +1;
%         end
%     end
    
    correct_num = 0;
    for i = 1:row_train
        x_test_i = x_train(i,:);
        y_test_i = y_train(i,:);
        prediction_result = 1 / (1+exp(-w_result'*x_test_i'));
        if prediction_result > 0.5 && y_test_i == 1
            correct_num = correct_num + 1;
        end
        if prediction_result <= 0.5 && y_test_i == 0
            correct_num = correct_num +1;
        end
    end   
rate = correct_num / row_train